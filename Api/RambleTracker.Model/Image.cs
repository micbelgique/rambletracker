using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RambleTracker.Model
{
    public class Image
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public byte[] Bytes { get; set; }
        public DateTime Date { get; set; }

        public int TrackId { get; set; }

        public virtual Track Track { get; set; }
    }
}
