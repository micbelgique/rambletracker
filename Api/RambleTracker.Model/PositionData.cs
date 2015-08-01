using System;
using System.Runtime.Serialization;

namespace RambleTracker.Model
{
    public class PositionData
    {
        public int Id { get; set; }
        public DateTime DateTime { get; set; }
        public double Longitude { get; set; }
        public double Latitude { get; set; }
        public int TrackId { get; set; }
        [IgnoreDataMember]
        public virtual Track Track { get; set; }
    }
}
