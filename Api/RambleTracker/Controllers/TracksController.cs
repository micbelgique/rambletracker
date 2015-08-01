using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Net;
using System.Web.Http;
using System.Web.Http.Cors;
using System.Web.Http.Description;
using RambleTracker.DAL;
using RambleTracker.Model;
using RambleTracker.ViewModels;

namespace RambleTracker.Controllers
{
    [EnableCors(origins: "http://micdevcamp.github.io", headers: "*", methods: "*")]
    public class TracksController : ApiController
    {
        private readonly RambleTrackerContext _db = new RambleTrackerContext();

        // GET: api/Tracks
        public IQueryable<TrackViewModel> GetTracks()
        {
            return _db.Tracks.Select(x => new TrackViewModel
            {
                Id = x.Id,
                Date = x.Date
            });
        }

        // GET: api/Tracks/5
        [ResponseType(typeof(TrackViewModel))]
        public IHttpActionResult GetTrack(int id)
        {
            var track = _db.Tracks.Where(x => x.Id == id).Select(x => new TrackViewModel
            {
                Id = x.Id,
                Date = x.Date,
                Positions = x.Positions.Select(z => new PositionDataViewModel
                {
                    Id = z.Id,
                    Latitude = z.Latitude,
                    Longitude = z.Longitude,
                    DateTime = z.DateTime,
                    TrackId = z.TrackId
                }).ToList()

            }).FirstOrDefault();

            if (track == null)
            {
                return NotFound();
            }

            return Ok(track);
        }

        // PUT: api/Tracks/5
        [ResponseType(typeof(void))]
        public IHttpActionResult PutTrack(int id, Track track)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            if (id != track.Id)
            {
                return BadRequest();
            }

            var firstPosition = track.Positions.FirstOrDefault();
            if (firstPosition != null)
                track.Date = firstPosition.DateTime;

            _db.Entry(track).State = EntityState.Modified;

            try
            {
                _db.SaveChanges();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!TrackExists(id))
                {
                    return NotFound();
                }
                throw;
            }

            return StatusCode(HttpStatusCode.NoContent);
        }

        // POST: api/Tracks
        [ResponseType(typeof(Track))]
        public IHttpActionResult PostTrack(Track track)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            _db.Tracks.Add(track);
            _db.SaveChanges();

            return CreatedAtRoute("DefaultApi", new { id = track.Id }, track);
        }

        // DELETE: api/Tracks/5
        [ResponseType(typeof(Track))]
        public IHttpActionResult DeleteTrack(int id)
        {
            Track track = _db.Tracks.Find(id);
            if (track == null)
            {
                return NotFound();
            }

            _db.Tracks.Remove(track);
            _db.SaveChanges();

            return Ok(track);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                _db.Dispose();
            }
            base.Dispose(disposing);
        }

        private bool TrackExists(int id)
        {
            return _db.Tracks.Count(e => e.Id == id) > 0;
        }
    }
}