using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using System.Web.Http;
using System.Web.Http.Description;
using RambleTracker.DAL;
using RambleTracker.Model;

namespace RambleTracker.Controllers
{
    public class PositionDatasController : ApiController
    {
        private readonly RambleTrackerContext _db = new RambleTrackerContext();

        // GET: api/PositionDatas
        public IQueryable<PositionData> GetPositionDatas()
        {
            return _db.PositionDatas;
        }

        // GET: api/PositionDatas/5
        [ResponseType(typeof(PositionData))]
        public async Task<IHttpActionResult> GetPositionData(int id)
        {
            PositionData positionData = await _db.PositionDatas.FindAsync(id);
            if (positionData == null)
            {
                return NotFound();
            }

            return Ok(positionData);
        }

        // PUT: api/PositionDatas/5
        [ResponseType(typeof(void))]
        public async Task<IHttpActionResult> PutPositionData(int id, PositionData positionData)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            if (id != positionData.Id)
            {
                return BadRequest();
            }

            _db.Entry(positionData).State = EntityState.Modified;

            try
            {
                await _db.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!PositionDataExists(id))
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

        // POST: api/PositionDatas
        [ResponseType(typeof(PositionData))]
        public async Task<IHttpActionResult> PostPositionData(PositionData positionData)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            _db.PositionDatas.Add(positionData);
            await _db.SaveChangesAsync();

            return CreatedAtRoute("DefaultApi", new { id = positionData.Id }, positionData);
        }

        // DELETE: api/PositionDatas/5
        [ResponseType(typeof(PositionData))]
        public async Task<IHttpActionResult> DeletePositionData(int id)
        {
            PositionData positionData = await _db.PositionDatas.FindAsync(id);
            if (positionData == null)
            {
                return NotFound();
            }

            _db.PositionDatas.Remove(positionData);
            await _db.SaveChangesAsync();

            return Ok(positionData);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                _db.Dispose();
            }
            base.Dispose(disposing);
        }

        private bool PositionDataExists(int id)
        {
            return _db.PositionDatas.Count(e => e.Id == id) > 0;
        }
    }
}