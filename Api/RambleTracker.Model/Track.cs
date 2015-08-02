using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace RambleTracker.Model
{
    public class Track
    {
        private ICollection<PositionData> _positions;
        private ICollection<Image> _images;
        public int Id { get; set; }
        public DateTime Date { get; set; }

        public virtual ICollection<PositionData> Positions
        {
            get { return _positions; }
            set { _positions = value; }
        }

        public virtual ICollection<Image> Images
        {
            get { return _images; }
            set { _images = value; }
        }

        public Track()
        {
            _positions = new Collection<PositionData>();
            _images = new Collection<Image>();
        }
    }
}
