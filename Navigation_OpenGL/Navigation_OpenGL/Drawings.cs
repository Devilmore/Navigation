using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tao.OpenGl;
using System.Drawing;
using OpenTK.Graphics.OpenGL;
using System.Drawing.Imaging;

namespace Navigation_OpenGL
{
    // This class contains most drawing functions
    class Drawings
    {
        // Draws a measurement of length 100 pixels, equalling 3.75 meters, to the lower left corner.
        // That's ~27 pixels / meter (26.6666...)
        public static void draw_measure(double x, double y)
        {
            GL.Color3(Color.White);
            GL.LineWidth(1);
            GL.Disable(EnableCap.LineSmooth);

            GL.Begin(BeginMode.Lines);
            GL.Vertex2(x, y + 5);
            GL.Vertex2(x, y - 5);
            GL.End();

            GL.Begin(BeginMode.Lines);
            GL.Vertex2(x, y);
            GL.Vertex2(x + 100, y);
            GL.End();

            GL.Begin(BeginMode.Lines);
            GL.Vertex2(x + 100, y + 5);
            GL.Vertex2(x + 100, y - 5);
            GL.End();
        }

        //Draws the map // TODO: Replace with proper texture drawing
        public static void draw_map(Bitmap image)
        {
            GL.Enable(EnableCap.Texture2D);

            int id = GL.GenTexture();
            GL.BindTexture(TextureTarget.Texture2D, id);
            BitmapData bmp_data = image.LockBits(new Rectangle(0, 0, image.Width, image.Height), ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, bmp_data.Width, bmp_data.Height, 0, OpenTK.Graphics.OpenGL.PixelFormat.Bgra, PixelType.UnsignedByte, bmp_data.Scan0);
            image.UnlockBits(bmp_data);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);

            GL.Color3((byte)255, (byte)255, (byte)255);
            GL.DepthMask(false);
            GL.Begin(BeginMode.Quads);
            GL.TexCoord2(0, 0);
            GL.Vertex2(0, 512);

            GL.TexCoord2(1, 0);
            GL.Vertex2(1024, 512);

            GL.TexCoord2(1, 1);
            GL.Vertex2(1024, 0);

            GL.TexCoord2(0, 1);
            GL.Vertex2(0, 0);
            GL.End();

            GL.Disable(EnableCap.Texture2D);
        }

        // Marked for Removal
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

        // Marked for Removal
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

            GL.Color3(Color.Black);
            GL.Begin(BeginMode.Lines);
            GL.Vertex2(x, y);
            GL.Vertex2(Variables.configuration_start.X[i], Variables.configuration_start.Y[i]);
            GL.End();
        }

        // Draws and saves the point X
        public static void drawL(double x, double y, int i)
        {
            Variables.configuration_start.X[i] = x;
            Variables.configuration_start.Y[i] = y;

            GL.Color3(Color.Black);
            GL.Begin(BeginMode.Lines);
            GL.Vertex2(x, y);
            // For i=0 the line has to be drawn from the fixed starting point since there is no previous M
            if (i==0)
                GL.Vertex2(Variables.start.x,Variables.start.y);
            else
                GL.Vertex2(Variables.configuration_start.Mx[i - 1], Variables.configuration_start.My[i - 1]);
            GL.End();
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
