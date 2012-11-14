using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Navigation_OpenGL
{
    public class configuration
    {
        public int length = 5;
        // X,Y positions of every axle i
        public double[] X { get; set; }
        public double[] Y { get; set; }
        // angle of every axle i
        public int[] Theta { get; set; }
        // x,y positions of the end point of M of every axle. This describes the end of axle i as well as
        // the start of the next axle i+1. Because of that there is no point L except for the first axle
        // (M[i] = L[i+1] for all other axles)
        public double[] Mx { get; set; }
        public double[] My { get; set; }
        // Point L for axle 0
        public double Lx { get; set; }
        public double Ly { get; set; }

        public configuration()
        {
            X = new double[length];
            Y = new double[length];
            Theta = new int[length];
            Mx = new double[length];
            My = new double[length];
            Lx = 0;
            Ly = 0;

            Random random = new Random();

            for (int i = 1; i < length; i++)
            {
                Theta[i] = random.Next(360);
            }
            Theta[0] = Theta[1];
        }

        public configuration(double[] x, double[] y, int[] theta, double[] mx, double[] my, double lx, double ly)
        {
            X = x;
            Y = y;
            Theta = theta;
            Mx = mx;
            My = my;
            Lx = lx;
            Ly = ly;
        }

        public EZPathFollowing.Point2D getPoint(int i)
        {
            return new EZPathFollowing.Point2D(X[i],Y[i]);
        }

        // Calculates an entire configuration from a given startpoint and orientation
        public static configuration getConfig(EZPathFollowing.Point2D start, double[] orientation)
        {
            // New config
            configuration configuration = new configuration();

            // Current X (first axle point) is the given start
            EZPathFollowing.Point2D X = start;

            EZPathFollowing.Point2D M;
            EZPathFollowing.Point2D L;

            // Iterates over all pathparts
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                // Writes the axle point to the configuration
                configuration.X[i] = X.x;
                configuration.Y[i] = X.y;

                // Writes the angle to the configuration
                configuration.Theta[i] = Convert.ToInt32(orientation[i]);

                // M is a new point to the left of X, distance M[i]
                M = new EZPathFollowing.Point2D(X.x - Variables.vehicle.M[i], X.y);

                // Rotates M around X by Theta (clockwise, starting at 9 o'clock)
                M = EZPathFollowing.Point2D.rotateAround(M, X, configuration.Theta[i]);

                // Writes M to the configuration
                configuration.Mx[i] = M.x;
                configuration.My[i] = M.y;

                // L only has to be calculated for the first Vehicle Part since otherwise it is the same as M[i-1]
                if (i == 0)
                {
                    // L is a new point to the right of X, distance L[i]
                    L = new EZPathFollowing.Point2D(X.x + Variables.vehicle.L[i], X.y);

                    // Rotates L around X by Theta (clockwise, starting at 3 o'clock)
                    L = EZPathFollowing.Point2D.rotateAround(L, X, configuration.Theta[i]);

                    configuration.Lx = L.x;
                    configuration.Ly = L.y;
                }

                // If there is a new Vehicle Part, calculate the next X
                if (i < Variables.vehicle_size - 1)
                {
                    // X[i+1] is a point to the left of the current M with the distance L[i+1]
                    X = new EZPathFollowing.Point2D(M.x - Variables.vehicle.L[i + 1], M.y);

                    // Rotates X around M by Theta[i+1] (clockwise, starting at 9 o'clock)
                    X = EZPathFollowing.Point2D.rotateAround(X, M, configuration.Theta[i + 1]);
                }
            }

            return configuration;
        }
    }
}
