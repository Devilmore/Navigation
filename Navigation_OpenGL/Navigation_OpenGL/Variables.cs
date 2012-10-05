using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Navigation_OpenGL
{
    class Variables
    {
        public static configuration configuration_start = new configuration();
        public static vehicle vehicle = new vehicle();
        public static int vehicle_size = 1;
        public static TextBox[] axles = new System.Windows.Forms.TextBox[10];
        public static TrackBar[] trackbars = new System.Windows.Forms.TrackBar[10];
    }
}
