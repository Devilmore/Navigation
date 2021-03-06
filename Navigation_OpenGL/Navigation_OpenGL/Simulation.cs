﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpenTK.Graphics.OpenGL;
using System.Drawing;
using System.Windows.Forms;

namespace Navigation_OpenGL
{
    class Simulation
    {
        Vehicle vehicle;
        LinkedList<EZPathFollowing.PathPart> path;
        private int numsteps=1000;

        private double stepwith=0.1;

        public double Stepwith
        {
            get { return stepwith; }
            set { stepwith = value; }
        }

        public int Numsteps
        {
            get { return numsteps; }
            set { numsteps = value; }
        }


        private List<EZPathFollowing.Point2D> traj = new List<EZPathFollowing.Point2D>();


        public Simulation(Vehicle _vehicle, LinkedList<EZPathFollowing.PathPart> _path)
        {
            vehicle = _vehicle;
            path = new LinkedList<EZPathFollowing.PathPart>(_path);
        }

        public void run()
        {
            int numParts = 2;
            double[] L = new double[numParts];
            double[] M = new double[numParts - 1];

            for (int i = 0; i < numParts; ++i)
            {
                L[i] = 20.0;
                if (i < numParts - 1)
                    M[i] = 0.2;
            }

            double[] ausrichtung = new double[numParts];
            double[] ausrichtung_Punkt = new double[numParts];
            ausrichtung[0] = (360 - Variables.configuration_start.Theta[0]) * Math.PI / 180;

            double[] x = new double[numParts];
            double[] x_Punkt = new double[numParts];

            double[] y = new double[numParts];
            double[] y_Punkt = new double[numParts];
            
            double[] v = new double[numParts];

            // Startpoint
            x[0] = Variables.start.x / 27;
            y[0] = Variables.start.y / 27;

            for (int i = 1; i < numParts; i++)
            {
                x[i] = x[i - 1] + Math.Cos(ausrichtung[i - 1]) * M[i - 1] - Math.Cos(ausrichtung[i]) * L[i];
                y[i] = y[i - 1] + Math.Sin(ausrichtung[i - 1]) * M[i - 1] - Math.Sin(ausrichtung[i]) * L[i];
            }

            double alpha = -10.0*Math.PI/180.0;
            v[0]=1.0;

            for (int step = 0; step < numsteps; ++step)
            {
                if (path.Count == 0)
                    break;
                for (int i = 0; i < numParts; ++i)
                {
                    if (i == 0)
                    {
                        // first part
                        alpha = getAlpha(x[0], y[0], ausrichtung[0], L[0]);
                        ausrichtung_Punkt[i] = v[i] * Math.Tan(alpha) / L[i];
                        v[i] = 1.0;
                        

                        //alpha = 0.0;//getAlpha()//alpha + 90*Math.PI/180/1000;
                    }
                    else
                    {
                        ausrichtung_Punkt[i] = (v[i - 1] * Math.Sin(ausrichtung[i - 1] - ausrichtung[i]) - M[i - 1] * ausrichtung_Punkt[i - 1] * Math.Cos(ausrichtung[i - 1] - ausrichtung[i])) / L[i];
                        v[i] = v[i - 1] * Math.Cos(ausrichtung[i - 1] - ausrichtung[i]) + M[i - 1] * Math.Sin(ausrichtung[i - 1] - ausrichtung[i]) * ausrichtung_Punkt[i - 1];
                    }

                    x_Punkt[i] = v[i] * Math.Cos(ausrichtung[i]);
                    y_Punkt[i] = v[i] * Math.Sin(ausrichtung[i]);

                    x[i] += x_Punkt[i] * stepwith;
                    y[i] += y_Punkt[i] * stepwith;
                    ausrichtung[i] += ausrichtung_Punkt[i] * stepwith;
                    // Check for collisions and finish
                }
                traj.Add(new EZPathFollowing.Point2D(x[0]*27, y[0]*27));
            }

            // Saves the position of the first vehicle part and the orientation at the end of the path for Variables for use in the fitness function
            Variables.x = x[0];
            Variables.y = y[0];
            Variables.orientation = ausrichtung;
            //System.Windows.Forms.MessageBox.Show(traj[500].x.ToString()+", "+traj[500].y.ToString());
        }

        private double getAlpha(double x, double y, double orientation,double L0)
        {
            x *= 27;
            y *= 27;
            L0 *= 27;

            double KV = 27;

            double test = path.First.Value.pathlength();
            double test2 = path.First.Value.referencePositionDefinitionValue(new EZPathFollowing.Point2D(x, y));
            // remove old path parts
            while (path.Count>0 && path.First.Value.referencePositionDefinitionValue(new EZPathFollowing.Point2D(x, y))>path.First.Value.pathlength())
                path.RemoveFirst();

            if (path.Count > 0)
            {
                // there are parts left
                // berechne Treffpunkt
                double distanceleft = KV + path.First.Value.referencePositionDefinitionValue(new EZPathFollowing.Point2D(x, y));
                EZPathFollowing.PathPart thisPart=path.ElementAt(0);

                for (int i = 0; i < path.Count-1; i++)
                {
                    
                    double thislength = thisPart.pathlength();
                    if (distanceleft > thislength)
                    {
                        distanceleft -= thislength;
                        thisPart = path.ElementAt(i + 1);
                    }
                    else break;
                }
                EZPathFollowing.Point2D hitpoint = thisPart.position(distanceleft);
                //System.Windows.Forms.MessageBox.Show(distanceleft.ToString()+"   "+hitpoint.x.ToString() + ", " + hitpoint.y.ToString());

                if (Math.Sin(orientation) * (x - hitpoint.x) == Math.Cos(orientation) * (y - hitpoint.y))
                    return 0.0;
                else
                {
                    double radius = ((x - hitpoint.x) * (x - hitpoint.x) + (y - hitpoint.y) * (y - hitpoint.y)) / 2 / (-Math.Sin(orientation) * (x - hitpoint.x) + Math.Cos(orientation) * (y - hitpoint.y));
                    return -Math.Atan2(L0,radius);
                }
            }
            return 40.0*Math.PI/180.0;
        }

        public void draw()
        {
            GL.Color3(Color.SkyBlue);
            GL.Begin(BeginMode.LineStrip);
            foreach (EZPathFollowing.Point2D point in traj)
                {
                GL.Vertex2(point.x, point.y);
                }
            GL.End();
        }

        // The following 3 functions return a representation of the path, this can be matched against the array representing the map
        
        // Simplest case, just the path
        public List<EZPathFollowing.Point2D> getPath()
        {
            return traj;
        }

        // Returns a the path, but wider by a fixed factor (since the vehicle isn't a line)
        public bool[,] getPath(int width)
        {
            bool[,] path = new bool[1024, 512];
            // Do Stuff
            return path;
        }

        // Returns the path with the actual width instead of a fixed one, taking vehicle width and veering into account
        public bool[,] getActualPath()
        {
            bool[,] path = new bool[1024, 512];
            // Do Stuff
            return path;
        }

        // Resets the path
        public void reset()
        {
            traj = new List<EZPathFollowing.Point2D>();
        }
    }
}
