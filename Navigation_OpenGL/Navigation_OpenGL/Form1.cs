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
        // Start and End default values. 
        EZPathFollowing.Point2D start = new EZPathFollowing.Point2D(225, 350);
        EZPathFollowing.Point2D end = new EZPathFollowing.Point2D(750, 50);
        // Loads the map
        Bitmap image = new Bitmap("C:\\Users\\Andreas\\Documents\\Visual Studio 2010\\Projects\\Navigation\\Map.png");
        
        
        public Form1()
        {
            // Initializes the window
            InitializeComponent();

            // Initializes the path with a LinePathPart of length 0 so the endpoint can be used later.
            // Remove if this causes problems
            Variables.path.AddLast(new EZPathFollowing.LinePathPart(start, start, false, 0.0));

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
            text_start.Text = (start.x + "," + start.y);
            text_end.Text = (end.x + "," + end.y);

            // Draws the path
            Gl.glColor3d(1, 0, 0);
            Gl.glDisable(Gl.GL_LINE_SMOOTH);
            Gl.glLineWidth(1);

            foreach (var item in Variables.path)
            {
                item.draw();
            }

            //Draws start and end
            Gl.glPointSize(5);

            Gl.glBegin(Gl.GL_POINTS);
            Gl.glColor3d(1, 0, 0);
            Gl.glVertex2d(start.x, start.y);
            Gl.glEnd();

            Gl.glBegin(Gl.GL_POINTS);
            Gl.glColor3d(0, 0, 1);
            Gl.glVertex2d(end.x, end.y);
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
                start.x = Convert.ToInt32(sentry[0]);
                start.y = Convert.ToInt32(sentry[1]);
                this.simpleOpenGlControl1.Invalidate();
            }
        }

        private void button_set_end_Click(object sender, EventArgs e)
        {
            //Add Exception handling here
            string[] eentry = text_end.Text.Split(',');
            if (validateEntry(eentry))
            {
                end.x = Convert.ToInt32(eentry[0]);
                end.y = Convert.ToInt32(eentry[1]);
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
            textBox1.Text = Convert.ToString(entry[1]);
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

        private void button_path_Click(object sender, EventArgs e)
        {
            //Adds random pathpart between 1 and 3 meters.
            //Currently adds completely impossible turns - is that even necessary to fix?

            bool b = Variables.getRandomBoolean();
            double x = Variables.getRandomNumber(27, 81);
            if (b == false)
                Variables.path.AddLast(EZPathFollowing.PathPrimitives.CircleInMeter(x));
            else
                Variables.path.AddLast(EZPathFollowing.PathPrimitives.LineInMeter(x));
            this.simpleOpenGlControl1.Invalidate();
        }
    }
}
