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
            var track = context.Tracks.Add(new Track
            {
                Date = DateTime.Now
            });
            
            context.PositionDatas.AddOrUpdate(new PositionData
            {
                DateTime = DateTime.Now,
                Latitude = 50.357933,
                Longitude = 5.496082,
                Track = track
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.359631,
                Longitude = 5.495116,
                Track = track
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.362040,
                Longitude = 5.497241,
                Track = track
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.365366,
                Longitude = 5.499923,
                Track = track
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.374686,
                Longitude = 5.515609,
                Track = track
            }, new PositionData
            {
                DateTime = DateTime.Now.AddMinutes(15),
                Latitude = 50.372086,
                Longitude = 5.512926,
                Track = track
            });
        }
    }
}
