using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace RambleTracker.Model
{
    public class Track
    {
        private ICollection<PositionData> _positions;
        public int Id { get; set; }
        public DateTime Date { get; set; }

        public virtual ICollection<PositionData> Positions
        {
            get { return _positions; }
            set { _positions = value; }
        }

        public Track()
        {
            _positions = new Collection<PositionData>();
        }
    }
}
