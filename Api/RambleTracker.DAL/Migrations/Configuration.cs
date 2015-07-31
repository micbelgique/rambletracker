using System;
using System.Data.Entity.Migrations;
using RambleTracker.Model;

namespace RambleTracker.DAL.Migrations
{
    internal sealed class Configuration : DbMigrationsConfiguration<RambleTrackerContext>
    {
        public Configuration()
        {
            AutomaticMigrationsEnabled = false;
        }

        protected override void Seed(RambleTrackerContext context)
        {
            context.PositionDatas.AddOrUpdate(new PositionData
            {
                DateTime = DateTime.Now,
                Latitude = 50.24055772,
                Longitude = 5.51131907
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.40326015,
                Longitude = 5.49163883
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.47194713,
                Longitude = 5.35971892
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.429069,
                Longitude = 5.44576527
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.45571327,
                Longitude = 5.44148866
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.24213014,
                Longitude = 5.53786159
            });
        }
    }
}
