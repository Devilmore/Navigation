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
        public static configuration configuration_end = new configuration();
        public static Vehicle vehicle = new Vehicle();
        public static Simulation simulation = null;
        public static int vehicle_size = 1;
        public static TextBox[] axles = new System.Windows.Forms.TextBox[10];
        public static TrackBar[] trackbars = new System.Windows.Forms.TrackBar[10];
        private static Random random = new Random();

        // Initializes a new LinkedList of type PathPart, which stores the Path.
        public static LinkedList<EZPathFollowing.PathPart> path = new LinkedList<EZPathFollowing.PathPart>();
        public static int pathlength = 0;

        // Initializes a genome which stores the Path Genome
        public static Genome genome = new Genome();

        // Start, end and direction of the vehicle
        public static EZPathFollowing.Point2D start = new EZPathFollowing.Point2D(225, 350);
        public static EZPathFollowing.Point2D end = new EZPathFollowing.Point2D(750, 50);
        public static double direction = 0;

        public static void resetPath()
        {
            pathlength = 0;
            path = new LinkedList<EZPathFollowing.PathPart>();
        }

        public static void resetGenome()
        {
           genome = new Genome();
        }

        // Function for getting random numbers in a given interval
        public static double getRandomNumber(double minimum, double maximum)
        {
            //Random random = new Random();
            // Give System a chance to be random
            System.Threading.Thread.Sleep(5);
            return minimum + random.NextDouble() * (maximum - minimum);
        }

        // Returns a random boolean. 
        public static bool getRandomBoolean()
        {
            // Give System a chance to be random
            //System.Threading.Thread.Sleep(5);
            return random.Next(100) % 2 == 0;
        }
    }
}
