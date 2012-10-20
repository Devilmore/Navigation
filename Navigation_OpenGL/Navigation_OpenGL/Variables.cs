using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Navigation_OpenGL
{
    // This class contains global variables
    class Variables
    {
        public static configuration configuration_start = new configuration();
        public static vehicle vehicle = new vehicle();
        public static int vehicle_size = 1;
        public static TextBox[] axles = new System.Windows.Forms.TextBox[10];
        public static TrackBar[] trackbars = new System.Windows.Forms.TrackBar[10];
        // Initializes a new LinkedList of type PathPart, which stores the Path.
        public static LinkedList<EZPathFollowing.PathPart> path = new LinkedList<EZPathFollowing.PathPart>();
        public static int pathlength = 0;

        // Function for getting random numbers in a given interval
        public static double getRandomNumber(double minimum, double maximum)
        {
            Random random = new Random();
            // Give System a chance to be random
            System.Threading.Thread.Sleep(5);
            return minimum + random.NextDouble() * (maximum - minimum);
        }

        // Returns a random boolean. 
        public static bool getRandomBoolean()
        {
            // Give System a chance to be random
            System.Threading.Thread.Sleep(5);
            return new Random().Next(100) % 2 == 0;
        }
    }
}
