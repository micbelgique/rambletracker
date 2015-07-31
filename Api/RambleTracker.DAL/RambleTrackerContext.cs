using System.Data.Entity;
using RambleTracker.Model;

namespace RambleTracker.DAL
{
    public class RambleTrackerContext : DbContext
    {
        public DbSet<PositionData> PositionDatas { get; set; }
        public DbSet<Track> Tracks { get; set; }

        public RambleTrackerContext() : base("RambleTrackerConnection")
        {
            
        }
    }
}
