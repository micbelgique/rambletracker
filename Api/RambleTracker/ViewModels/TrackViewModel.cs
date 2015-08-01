using System;
using System.Collections.Generic;

namespace RambleTracker.ViewModels
{
    public class TrackViewModel
    {
        public int Id { get; set; }
        public DateTime Date { get; set; }
        public List<PositionDataViewModel> Positions { get; set; }
    }
}
