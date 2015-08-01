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

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Entity<PositionData>()
                .HasRequired(x => x.Track)
                .WithMany(x => x.Positions)
                .HasForeignKey(x => x.TrackId)
                .WillCascadeOnDelete(false);

            base.OnModelCreating(modelBuilder);
        }
    }
}
