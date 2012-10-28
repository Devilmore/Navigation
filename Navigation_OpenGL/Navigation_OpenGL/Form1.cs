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


namespace Navigation_OpenGL
{
    public partial class Form1 : Form
    {
        // OpenGLSimpleControl size for drawing
        int width = 800;
        int height = 600;

        // Loads the map
        Bitmap image = new Bitmap("C:\\Users\\Andreas\\Documents\\Visual Studio 2010\\Projects\\Navigation\\Map.png");
        
        
        public Form1()
        {
            // Initializes the window
            InitializeComponent();


            this.textBox1.Text = Variables.genome.getLength().ToString();

            // Initializes the OpenGL components
            this.simpleOpenGlControl1.InitializeContexts();
            Gl.glClearColor(1, 0, 0, 0);
            Gl.glMatrixMode(Gl.GL_PROJECTION);
            Gl.glLoadIdentity();
            Gl.glOrtho(0, width, height, 0, 0, 1);
            Gl.glMatrixMode(Gl.GL_MODELVIEW);
            Gl.glDisable(Gl.GL_DEPTH_TEST);

        }

        private void timer_load_Tick(object sender, EventArgs e)
        {
            ////Drawing of Image using the Image/Bitmap class instead of OpenGL
            //Bitmap map = CreateNonIndexedImage(image);
            //picture_map.Image = map;

            ////Drawing of Image using OpenGL every x ms. Use instead of Button clikc for animations.
            //this.simpleOpenGlControl1.Invalidate();

        }

        private void simpleOpenGlControl1_Paint(object sender, PaintEventArgs e)
        {
            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT);
            Gl.glColor3d(1, 1, 1);
            Gl.glPointSize(1);

            // Shows the color of 20,20 in the debug box. Remove later
            // textBox1.Text = image.GetPixel(20, 20).ToKnownColor().ToString();

            // Draws the map
            Drawings.draw_map(image);

            //Shows current start/end in their boxes
            text_start.Text = (Variables.start.x + "," + Variables.start.y);
            text_end.Text = (Variables.end.x + "," + Variables.end.y);

            // Draws the path
            Gl.glColor3d(1, 0, 0);
            Gl.glDisable(Gl.GL_LINE_SMOOTH);
            Gl.glLineWidth(1);

            foreach (var item in Variables.path)
            {
                item.draw();
            }

            if (Variables.simulation != null)
                Variables.simulation.draw();

            //Draws start and end
            Gl.glPointSize(5);

            Gl.glBegin(Gl.GL_POINTS);
            Gl.glColor3d(1, 0, 0);
            Gl.glVertex2d(Variables.start.x, Variables.start.y);
            Gl.glEnd();

            Gl.glBegin(Gl.GL_POINTS);
            Gl.glColor3d(0, 0, 1);
            Gl.glVertex2d(Variables.end.x, Variables.end.y);
            Gl.glEnd();

            Drawings.draw_measure(20, 580);
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
                this.simpleOpenGlControl1.Invalidate();
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
                this.simpleOpenGlControl1.Invalidate();
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
            for (int i = 0; i <= 0; i++)
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
            this.simpleOpenGlControl1.Refresh();
            this.textBox1.Text = Variables.genome.write();
            //this.simpleOpenGlControl1.Invalidate();
        }

        private void driveButton_Click(object sender, EventArgs e)
        {
            Variables.simulation = new Simulation(Variables.vehicle, Variables.path);
            Variables.simulation.run();
            this.simpleOpenGlControl1.Refresh();
        }
    }
}
