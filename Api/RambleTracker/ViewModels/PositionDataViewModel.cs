using System;

namespace RambleTracker.ViewModels
{
    public class PositionDataViewModel
    {
        public int Id { get; set; }
        public double Latitude { get; set; }
        public double Longitude { get; set; }
        public DateTime DateTime { get; set; }
        public int TrackId { get; set; }
    }
}
