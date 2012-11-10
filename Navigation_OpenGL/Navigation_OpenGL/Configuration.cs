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

        /**
        public configuration next_conf(configuration prev_conf, double delta_angle)
        {
            // v is constant at the moment
            double[] v = new double[] {5};

            configuration next_conf = new configuration();
            for (int i = 0; i <= prev_conf.X.Length; i++)
            {
                next_conf.Theta[i] = ((1 / ((prev_conf.L[i]) + 1)) * (v[0] * Math.Sin(delta_angle) - prev_conf.M[i] * Math.Cos(delta_angle) * prev_conf.Theta[i]));
                next_conf.X[i] = v[0] * Math.Cos(next_conf.Theta[i]);
                next_conf.Y[i] = v[0] * Math.Sin(next_conf.Theta[i]);
                next_conf.M[i] = prev_conf.M[i];
                next_conf.L[i] = prev_conf.L[i];
                // v?
            }
            return next_conf;
        }
       **/
    }
}
