using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Navigation_OpenGL
{
    public class Vehicle
    {
        public int length = 5;
        public double[] M { get; set; }
        public double[] L { get; set; }

        public Vehicle()
        {
            M = new double[length];
            L = new double[length];
            // Fills the default constructor fields with random values so you can actually draw something
            Random random = new Random();

            for (int i = 0; i < length; i++)
            {
                M[i] = 50 * Math.Round(random.NextDouble(), 3);
                L[i] = 50 * Math.Round(random.NextDouble(), 3);
            }
        }

        public Vehicle(double[] x, double[] y, double[] theta, double[] m, double[] l)
        {
            M = m;
            L = l;
        }
    }
}
