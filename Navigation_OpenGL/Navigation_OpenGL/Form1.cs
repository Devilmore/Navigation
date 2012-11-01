using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Tao.OpenGl;
using Tao.Platform.Windows;
using OpenTK.Graphics.OpenGL;


namespace Navigation_OpenGL
{
    public partial class Form1 : Form
    {
        // Loads the map
        Bitmap image = new Bitmap("C:\\Users\\Andreas\\Dropbox\\Uni Projects\\BachelorThesis\\Navigation\\Navigation_OpenGL\\Navigation_OpenGL\\Resources\\Map_512.bmp");
        
        
        public Form1()
        {
            // Initializes the window
            InitializeComponent();


            // Initializes the OpenGL components
            //this.simpleOpenGlControl1.InitializeContexts();
            //Gl.glClearColor(1, 1, 1, 0);
            //Gl.glMatrixMode(Gl.GL_PROJECTION);
            //Gl.glLoadIdentity();
            //Gl.glOrtho(0, width, height, 0, 0, 1);
            //Gl.glMatrixMode(Gl.GL_MODELVIEW);
            //Gl.glDisable(Gl.GL_DEPTH_TEST);

        }

        private void timer_load_Tick(object sender, EventArgs e)
        {
            ////Drawing of Image using the Image/Bitmap class instead of OpenGL
            //Bitmap map = CreateNonIndexedImage(image);
            //picture_map.Image = map;

            ////Drawing of Image using OpenGL every x ms. Use instead of Button clikc for animations.
            //this.simpleOpenGlControl1.Invalidate();

        }

        private void simpleOpenGlControl1_Load(object sender, EventArgs e)
        {
          
        }

        private void picture_map_Click(object sender, EventArgs e)
        {

        }

        private void button_load_Click(object sender, EventArgs e)
        {
            OpenFileDialog omd = new OpenFileDialog();
            if (omd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                Image load_map = Image.FromFile(omd.FileName);
                image = new Bitmap(load_map);
            }

        }

        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {

        }

        public Bitmap CreateNonIndexedImage(Image src)
        {
            Bitmap newBmp = new Bitmap(src.Width, src.Height, System.Drawing.Imaging.PixelFormat.Format32bppArgb);

            using (Graphics gfx = Graphics.FromImage(newBmp))
            {
                gfx.DrawImage(src, 0, 0);
            }

            return newBmp;
        }

        public bool[,] createMap(Bitmap image)
        {
            bool[,] map = new bool[800, 600];
            for (int x = 0; x < 800; x++)
            {
                for (int y = 0; y < 600; y++)
                {
                    map[x,y] = (image.GetPixel(x,y) == Color.Black) ? false : true;
                }
            }
            return map;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button_set_start_Click(object sender, EventArgs e)
        {
            string[] sentry = text_start.Text.Split(',');
            if (validateEntry(sentry))
            {
                Variables.start.x = Convert.ToInt32(sentry[0]);
                Variables.start.y = Convert.ToInt32(sentry[1]);
                this.glControl1.Refresh();
            }
        }

        private void button_set_end_Click(object sender, EventArgs e)
        {
            //Add Exception handling here
            string[] eentry = text_end.Text.Split(',');
            if (validateEntry(eentry))
            {
                Variables.end.x = Convert.ToInt32(eentry[0]);
                Variables.end.y = Convert.ToInt32(eentry[1]);
                this.glControl1.Refresh();
            }
        }

        private void text_start_TextChanged(object sender, EventArgs e)
        {
            string[] sentry = text_start.Text.Split(',');
            validateEntry(sentry);
        }

        private void text_end_TextChanged(object sender, EventArgs e)
        {
            string[] eentry = text_end.Text.Split(',');
            validateEntry(eentry);
        }

        private bool validateEntry(string[] entry)
        {
            if (entry.Length != 2)
            {
                MessageBox.Show("The field must contain 2 numbers, seperated by \",\"");
                return false;
            }
            int ex = Convert.ToInt32(entry[0]);
            int ey = Convert.ToInt32(entry[1]);
            if (ex < 0 || ex > 800 || ey < 0 || ey > 600)
            {
                MessageBox.Show("The first value must be between 0 and 800 and the second between 0 and 600.");
                return false;
            }
            return true;
        }

        private void button_vehicle_Click(object sender, EventArgs e)
        {
            Form2 frm = new Form2();
            frm.Show();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button_configuration_Click(object sender, EventArgs e)
        {
            Form3 frm = new Form3();
            frm.Show();
        }

        // Adds a random PathPart, limitations set in PathPrimitives
        private void button_path_Click(object sender, EventArgs e)
        {
            // Resets the Path, Genome and Simulation before calculating the new ones
            Variables.resetGenome();
            Variables.resetPath();
            if (Variables.simulation != null)
                Variables.simulation.reset();

            // Creates a new Path with 20 Pathparts as well as it's genome and simulation
            for (int i = 0; i < 20; i++)
            {
                EZPathFollowing.PathPart temp;
                //temp = EZPathFollowing.PathPrimitives.line(1, 0, start);
                if (Variables.pathlength == 0)
                    temp = EZPathFollowing.PathPrimitives.getRandomPathPart(Variables.start, Variables.direction);
                else
                    temp = EZPathFollowing.PathPrimitives.getRandomPathPart();

                Variables.path.AddLast(temp);
                Variables.pathlength++;
            }

            // Draws everything
            this.glControl1.Refresh();

            // Writes the genome to the textbox
            this.textBox1.Text = Variables.genome.write();
        }

        private void driveButton_Click(object sender, EventArgs e)
        {
            Variables.simulation = new Simulation(Variables.vehicle, Variables.path);
            Variables.simulation.run();
            this.glControl1.Refresh();
        }

        private void glControl1_Load(object sender, EventArgs e)
        {
            GL.ClearColor(Color.SkyBlue);
            int w = glControl1.Width;
            int h = glControl1.Height;
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.Ortho(0, w, 0, h, -1, 1); // Bottom-left corner pixel has coordinate (0, 0)
            GL.Viewport(0, 0, w, h); // Use all of the glControl painting area
        }

        private void glControl1_Paint(object sender, PaintEventArgs e)
        {
            // Clears
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            // Draws the map
            Drawings.draw_map(image);

            //Shows current start/end in their boxes
            text_start.Text = (Variables.start.x + "," + Variables.start.y);
            text_end.Text = (Variables.end.x + "," + Variables.end.y);

            // Draws the path
            GL.Color3(Color.Red);
            GL.LineWidth(1);
            GL.Disable(EnableCap.LineSmooth);

            foreach (var item in Variables.path)
            {
                item.draw();
            }

            if (Variables.simulation != null)
                Variables.simulation.draw();

            //Draws start and end
            GL.PointSize(5);

            GL.Begin(BeginMode.Points);
            GL.Color3(Color.Red);
            GL.Vertex2(Variables.start.x, Variables.start.y);
            GL.End();

            GL.Begin(BeginMode.Points);
            GL.Color3(Color.Blue);
            GL.Vertex2(Variables.end.x, Variables.end.y);
            GL.End();

            Drawings.draw_measure(20, 580);

            // Draws everything
            glControl1.SwapBuffers();
        }
    }
}
