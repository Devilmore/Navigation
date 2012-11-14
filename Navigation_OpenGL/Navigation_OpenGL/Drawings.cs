using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

        // Draws the given configuration.
        public static void drawConfiguration(configuration config)
        {
            GL.PointSize(3);
            GL.Color3(Color.Red);

            // Iterates over the configuration
            for (int i = 0; i < Variables.vehicle_size; i++){
                // Draws the Lines
                GL.Begin(BeginMode.Lines);
                // For the first element the starting point is L since there is no previous M
                if (i == 0)
                    GL.Vertex2(config.Lx,config.Ly);
                // Otherwise it's the previous M
                else
                    GL.Vertex2(config.Mx[i-1],config.My[i-1]);
                GL.Vertex2(config.Mx[i],config.My[i]);
                GL.End();
            
                // Draws the points last so they are above the lines
                GL.Begin(BeginMode.Points);
                if (i == 0)
                    GL.Vertex2(config.Lx,config.Ly);
                GL.Vertex2(config.X[i], config.Y[i]);
                GL.Vertex2(config.Mx[i],config.My[i]);
                GL.End();
            }
        }


        //TODO: All these functions can replaced by the above function and the getConfig function in the configuration class.
        
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
            if (Variables.config_start)
            {
                Variables.configuration_start.Mx[i] = x;
                Variables.configuration_start.My[i] = y;
            }
            else
            {
                Variables.configuration_end.Mx[i] = x;
                Variables.configuration_end.My[i] = y;
            }

            GL.Color3(Color.Black);
            GL.Begin(BeginMode.Lines);
            GL.Vertex2(x, y);
            if (Variables.config_start)
                GL.Vertex2(Variables.configuration_start.X[i], Variables.configuration_start.Y[i]);
            else
                GL.Vertex2(Variables.configuration_end.X[i], Variables.configuration_end.Y[i]);
            GL.End();
        }

        // Draws and saves the point X
        public static void drawL(double x, double y, int i)
        {
            if (Variables.config_start)
            {
                Variables.configuration_start.X[i] = x;
                Variables.configuration_start.Y[i] = y;

                GL.Color3(Color.Black);
                GL.Begin(BeginMode.Lines);
                GL.Vertex2(x, y);
                // For i=0 the line has to be drawn from the fixed starting point since there is no previous M
                if (i == 0)
                    GL.Vertex2(Variables.start.x, Variables.start.y);
                else
                    GL.Vertex2(Variables.configuration_start.Mx[i - 1], Variables.configuration_start.My[i - 1]);
                GL.End();
            }
            else
            {
                Variables.configuration_end.X[i] = x;
                Variables.configuration_end.Y[i] = y;
                GL.Color3(Color.Black);
                GL.Begin(BeginMode.Lines);
                GL.Vertex2(x, y);
                // For i=0 the line has to be drawn from the fixed starting point since there is no previous M
                if (i == 0)
                    GL.Vertex2(Variables.end.x, Variables.end.y);
                else
                    GL.Vertex2(Variables.configuration_end.Mx[i - 1], Variables.configuration_end.My[i - 1]);
                GL.End();
            }

        }

        // Calculates, draws and saves the value for either M (X to M) or X (L to X), depending on the given function getL or getM
        public static void draw(Func<int, double> save_variable, Func<int, KeyValuePair<double, double>> getStart, Action<double, double, int> drawEnd, int i)
        {
            // Gets the starting values using the given function getStart and writes it to x and y

            var start = getStart(i);
            double x = start.Key;
            double y = start.Value;
            double angle = 0;

            // Gets the angle and checks how to calculate the new point
            if (Variables.config_start)
                angle = Variables.configuration_start.Theta[i];
            else
                angle = Variables.configuration_end.Theta[i];

            switch (Convert.ToInt32(angle))
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
