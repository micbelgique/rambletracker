using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Web.Http.Description;
using RambleTracker.DAL;
using RambleTracker.Model;
using System.Threading.Tasks;
using System.IO;
using System.Net.Http.Headers;
using RambleTracker.ViewModels;
using System.Web.Http.Cors;

namespace RambleTracker.Controllers
{
    public class ImagesController : ApiController
    {
        private RambleTrackerContext db = new RambleTrackerContext();

        // GET: api/Images
        public IQueryable<ImageViewModel> GetImages(int id)
        {
            Track track = db.Tracks.Find(id);
            List<ImageViewModel> vmList = new List<ImageViewModel>();
            if(track != null)
            {
                foreach (var item in track.Images)
                {
                    ImageViewModel vm = new ImageViewModel();
                    vm.Url = Url.Route("Default", new { controller = "Images", action = "Image", id = item.Id });
                    vmList.Add(vm);
                }
            }

            return vmList.AsQueryable();
        }

        // GET: api/Images/5
        public HttpResponseMessage GetImage(int id)
        {
            Image image = db.Images.Find(id);
            if (image == null)
            {
                return new HttpResponseMessage(HttpStatusCode.OK);
            }

            HttpResponseMessage httpResponseMessage = new HttpResponseMessage(HttpStatusCode.OK);
            byte[] fileData = image.Bytes;
            MemoryStream ms = new MemoryStream(fileData);
            httpResponseMessage.Content = new StreamContent(ms);
            httpResponseMessage.Content.Headers.ContentType = new MediaTypeHeaderValue("image/jpg");
            return httpResponseMessage;
        }

        // PUT: api/Images/5
        [ResponseType(typeof(void))]
        public IHttpActionResult PutImage(int id, Image image)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            if (id != image.Id)
            {
                return BadRequest();
            }

            db.Entry(image).State = EntityState.Modified;

            try
            {
                db.SaveChanges();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!ImageExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return StatusCode(HttpStatusCode.NoContent);
        }

        //// POST: api/Images
        //[ResponseType(typeof(Image))]
        //public IHttpActionResult PostImage(Image image)
        //{
        //    if (!ModelState.IsValid)
        //    {
        //        return BadRequest(ModelState);
        //    }

        //    db.Images.Add(image);
        //    db.SaveChanges();

        //    return CreatedAtRoute("DefaultApi", new { id = image.Id }, image);
        //}

        [HttpPost]
        public async Task<IHttpActionResult> PostImage(int id)
        {
            if (!Request.Content.IsMimeMultipartContent())
                throw new HttpResponseException(HttpStatusCode.UnsupportedMediaType);

            var provider = new MultipartMemoryStreamProvider();
            await Request.Content.ReadAsMultipartAsync(provider);

            foreach (var file in provider.Contents)
            {
                var fileName = file.Headers.ContentDisposition.FileName.Trim('\"');
                var date = file.Headers.ContentDisposition.CreationDate.Value.DateTime;
                var buffer = await file.ReadAsByteArrayAsync();

                Image img = new Image { Name = fileName, Bytes = buffer, Date = date, TrackId = id };

                db.Images.Add(img);
            }

            db.SaveChanges();

            return Ok();
        }

        // DELETE: api/Images/5
        [ResponseType(typeof(Image))]
        public IHttpActionResult DeleteImage(int id)
        {
            Image image = db.Images.Find(id);
            if (image == null)
            {
                return NotFound();
            }

            db.Images.Remove(image);
            db.SaveChanges();

            return Ok(image);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }

        private bool ImageExists(int id)
        {
            return db.Images.Count(e => e.Id == id) > 0;
        }
    }
}