using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tao.OpenGl;
using System.Drawing;

namespace Navigation_OpenGL
{
    // This class contains most drawing functions
    class Drawings
    {
        // Draws a measurement of length 100 pixels, equalling 3.75 meters, to the lower left corner.
        // That's ~27 pixels / meter (26.6666...)
        public static void draw_measure(double x, double y)
        {

            Gl.glColor3d(1, 1, 1);
            Gl.glDisable(Gl.GL_LINE_SMOOTH);
            Gl.glLineWidth(1);

            Gl.glBegin(Gl.GL_LINES);
            Gl.glVertex2d(x, y + 5);
            Gl.glVertex2d(x, y - 5);
            Gl.glEnd();

            Gl.glBegin(Gl.GL_LINES);
            Gl.glVertex2d(x, y);
            Gl.glVertex2d(x + 100, y);
            Gl.glEnd();

            Gl.glBegin(Gl.GL_LINES);
            Gl.glVertex2d(x + 100, y + 5);
            Gl.glVertex2d(x + 100, y - 5);
            Gl.glEnd();
        }

        //Draws the map // TODO: Replace with proper texture drawing
        public static void draw_map(Bitmap image)
        {
            // Gets the color of Pixel at 20,20 because that is black. Fix to a constant later
            Color black = image.GetPixel(20, 20);

            for (int x = 0; x < 800; x++)
            {
                for (int y = 0; y < 600; y++)
                {
                    if (image.GetPixel(x, y) == black)
                    {
                        Gl.glBegin(Gl.GL_POINTS);
                        Gl.glColor3d(0, 0, 0);
                        Gl.glVertex2d(x, y);
                        Gl.glEnd();
                    }
                    else
                    {
                        Gl.glBegin(Gl.GL_POINTS);
                        Gl.glColor3f(1, 1, 1);
                        Gl.glVertex2d(x, y);
                        Gl.glEnd();
                    }
                }
            }
        }

        // Draws the axle point X as well as start/end of the vehicle part M and L for each axle. X is red, M and L are blue. As always, L[i] = M[i-1], except for L[0]
        public static void draw_points()
        {
            double x = 30;

            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                Gl.glColor3d(1, 0, 0);
                Gl.glBegin(Gl.GL_POINTS);
                Gl.glVertex2d(x, 42);
                Gl.glEnd();

                Gl.glColor3d(0, 1, 1);
                Gl.glBegin(Gl.GL_POINTS);
                Gl.glVertex2d(x - Variables.vehicle.L[i], 42);
                Gl.glVertex2d(x + Variables.vehicle.M[i], 42);
                Gl.glEnd();
                if (i + 1 < Variables.vehicle_size)
                    x += Variables.vehicle.M[i] + Variables.vehicle.L[i + 1];
            }
        }

        // Draws the lines M and L for each axle in white
        public static void draw_lines()
        {
            double x = 30;

            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                Gl.glColor3d(1, 1, 1);
                Gl.glBegin(Gl.GL_LINES);
                Gl.glVertex2d(x - Variables.vehicle.L[i], 42);
                Gl.glVertex2d(x + Variables.vehicle.M[i], 42);
                Gl.glEnd();
                if (i + 1 < Variables.vehicle_size)
                    x += Variables.vehicle.M[i] + Variables.vehicle.L[i + 1];
            }
        }

        /**
         * The Following functions calculate and draw the axles. 
         * In this, X will refer to the axle point, described by the coordinates X(x,y),
         * as such, X[i] means the position of axle i.
         * L[i] will refer to the front point of that part of the vehicle, described by the coordinates L[x,y].
         * M[i] is analog for the point M (end of part of vehicle).
         * Since L is the start of a vehicle part and M the end of another vehicle part this means:
         * L[i] = M[i-1], meaning the start (L) of one vehicle part is equal to the end (M) of the previous one.
         * Because of that the point L is never relevant and won't be calculated. 
         * Functions with L in their name will actually calculate X, not L. They only start at L (or previous M).
         * Functions with M in their name really do calculate M (starting from X)
         * i = 0 is irregular since in this case L is fixed.
        **/

        // Draws and saves the point M
        public static void drawM(double x, double y, int i)
        {
            Variables.configuration_start.Mx[i] = x;
            Variables.configuration_start.My[i] = y;

            Gl.glColor3d(1, 1, 1);
            Gl.glBegin(Gl.GL_LINES);
            Gl.glVertex2d(x, y);
            Gl.glVertex2d(Variables.configuration_start.X[i], Variables.configuration_start.Y[i]);
            Gl.glEnd();
        }

        // Draws and saves the point X
        public static void drawL(double x, double y, int i)
        {
            Variables.configuration_start.X[i] = x;
            Variables.configuration_start.Y[i] = y;

            Gl.glColor3d(1, 1, 1);
            Gl.glBegin(Gl.GL_LINES);
            Gl.glVertex2d(x, y);
            // For i=0 the line has to be drawn from the fixed starting point since there is no previous M
            if (i == 0)
                Gl.glVertex2d(380, 200);
            else
                Gl.glVertex2d(Variables.configuration_start.Mx[i - 1], Variables.configuration_start.My[i - 1]);
            Gl.glEnd();
        }

        // Calculates, draws and saves the value for either M (X to M) or X (L to X), depending on the given function getL or getM
        public static void draw(Func<int, double> save_variable, Func<int, KeyValuePair<double, double>> getStart, Action<double, double, int> drawEnd, int i)
        {
            // Gets the starting values using the given function getStart and writes it to x and y

            var start = getStart(i);
            double x = start.Key;
            double y = start.Value;


            // Gets the angle and checks how to calculate the new point
            double angle = Variables.configuration_start.Theta[i];
            switch (Variables.configuration_start.Theta[i])
            {
                case 0:
                    x -= save_variable(i);
                    break;
                case 90:
                    y += save_variable(i);
                    break;
                case 180:
                    x += save_variable(i);
                    break;
                case 270:
                    y -= save_variable(i);
                    break;
                case 360:
                    x -= save_variable(i);
                    break;
                default:
                    break;
            }

            if (angle < 90 && angle != 0)
            // 1 Quadrant
            {
                double deltay = Math.Sin(angle * (Math.PI / 180)) * save_variable(i);
                y += deltay;
                x -= Math.Sqrt((save_variable(i) * save_variable(i)) - (deltay * deltay));
            }
            else if (angle > 90 && angle < 180)
            // 2 Quadrant, 180 - Theta
            {
                double deltay = Math.Sin((180 - angle) * (Math.PI / 180)) * save_variable(i);
                y += deltay;
                x += Math.Sqrt((save_variable(i) * save_variable(i)) - (deltay * deltay));
            }
            else if (angle > 180 && angle < 270)
            // 3 Quadrant, Theta - 180
            {
                double deltay = Math.Sin((angle - 180) * (Math.PI / 180)) * save_variable(i);
                y -= deltay;
                x += Math.Sqrt((save_variable(i) * save_variable(i)) - (deltay * deltay));
            }
            else if (angle > 270 && angle != 360)
            // 4 Quadrant, 360 - Theta
            {
                double deltay = Math.Sin((360 - angle) * (Math.PI / 180)) * save_variable(i);
                y -= deltay;
                x -= Math.Sqrt((save_variable(i) * save_variable(i)) - (deltay * deltay));
            }
            // Draws the point and saves the calculated values using the given function drawEnd
            drawEnd(x, y, i);
        }
    }
}
