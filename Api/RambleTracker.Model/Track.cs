using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RambleTracker.Model
{
    public class Track
    {
        public int Id { get; set; }

        public virtual ICollection<PositionData> Positions { get; set; }
    }
}
