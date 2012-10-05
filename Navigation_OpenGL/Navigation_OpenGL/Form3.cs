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
using System.IO;

namespace Navigation_OpenGL
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
            this.simpleOpenGlControl3.InitializeContexts();
            Gl.glClearColor(0, 0, 0, 0);
            Gl.glMatrixMode(Gl.GL_PROJECTION);
            Gl.glLoadIdentity();
            Gl.glOrtho(0, 760, 400, 0, 0, 1);
            Gl.glMatrixMode(Gl.GL_MODELVIEW);
            Gl.glDisable(Gl.GL_DEPTH_TEST);
            trackBar0.Value = Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)];
            counter_axle.Maximum = Variables.vehicle_size - 1;
        }

        private void Form3_Load(object sender, EventArgs e)
        {

        }

        private void simpleOpenGlControl3_Load(object sender, EventArgs e)
        {

        }

        private void simpleOpenGlControl3_Paint(object sender, PaintEventArgs e)
        {
            // Paints all axles from the starting configuration when called
            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT);
            Gl.glPointSize(2);

            Variables.configuration_start.X[0] = 380;
            Variables.configuration_start.Y[0] = 200;

            Gl.glEnable(Gl.GL_LINE_SMOOTH);
            Gl.glHint(Gl.GL_LINE_SMOOTH_HINT, Gl.GL_NICEST);
            Gl.glLineWidth(1);

           // Draws the axles with the static starting point of L[0] (start of first axle)
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                // Draws the Line from L to X, whereas L is equal to M[i-1], except for i=1 where L[0] is fixed
                Drawings.draw(getL, getLstart, Drawings.drawL, i);
                // Draws the Line from X to M
                Drawings.draw(getM, getMstart, Drawings.drawM, i);
            }

            // Draws the points last so they are visible. Red for axle points
            Gl.glColor3d(1, 0, 0);
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                Gl.glBegin(Gl.GL_POINTS);
                Gl.glVertex2d(Variables.configuration_start.X[i], Variables.configuration_start.Y[i]);
                Gl.glEnd();
            }

            // Blue for stat/end points
            Gl.glColor3d(0, 0, 1);
            Gl.glBegin(Gl.GL_POINTS);
            Gl.glVertex2d(380, 200);
            Gl.glEnd();
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                Gl.glBegin(Gl.GL_POINTS);
                Gl.glVertex2d(Variables.configuration_start.Mx[i], Variables.configuration_start.My[i]);
                Gl.glEnd();
            }

            Drawings.draw_measure(20, 380);
        }

        /** The Following functions are only here to be passed to the drawing functions in Drawings.cs **/

        // Returns the length of M[i] so it can be passed as a function
        public double getM(int i)
        {
            return Variables.vehicle.M[i];
        }

        // Returns the length of L[i] so it can be passed as a function
        public double getL(int i)
        {
            return Variables.vehicle.L[i];
        }

        // Returns the values Mx and My, the starting point for the calculation for X from L
        public KeyValuePair<double, double> getLstart(int i)
        {
            // L is fixed for i=0 since this is the starting point
            if (i == 0)
                return new KeyValuePair<double, double>(380, 200);
            else
                return new KeyValuePair<double, double>(Variables.configuration_start.Mx[i - 1], Variables.configuration_start.My[i - 1]);
        }

        // Returns the values X and Y, the starting point for the calculation for M from X
        public KeyValuePair<double, double> getMstart(int i)
        {
            return new KeyValuePair<double, double>(Variables.configuration_start.X[i], Variables.configuration_start.Y[i]);
        }

        

        private void trackBar0_ValueChanged(object sender, EventArgs e)
        {
            Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)] = trackBar0.Value;
            if (counter_axle.Value == 1)
                Variables.configuration_start.Theta[0] = Variables.configuration_start.Theta[1];
            this.simpleOpenGlControl3.Invalidate();
            toolTip1.SetToolTip(trackBar0, trackBar0.Value.ToString());
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.simpleOpenGlControl3.Invalidate();
        }

        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {

        }

        private void counter_axle_ValueChanged(object sender, EventArgs e)
        {
            trackBar0.Value = Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)];
        }

        private void button_save_config_Click(object sender, EventArgs e)
        {
            save_config.Filter = "Text Files|*.txt";
            save_config.ShowDialog();
        }

        private void save_config_FileOk(object sender, CancelEventArgs e)
        {
            MessageBox.Show("Please remember to also save the current vehicle. You won't be able to load a configuration unless it's length fits the vehicle.");
            // Initializes the output string
            string output = "";
            // Iterates over the starting configuration, seperating values by ;
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                output = output + Variables.configuration_start.Theta[i].ToString();
                if (i < Variables.vehicle_size - 1)
                    output = output + ';';
            }
            // Saves the configuration
            System.IO.Stream fileStream = save_config.OpenFile();
            System.IO.StreamWriter sw = new System.IO.StreamWriter(fileStream);
            sw.WriteLine(output);
            sw.Flush();
            sw.Close();
        }

        private void button_load_config_Click(object sender, EventArgs e)
        {
            // Defines some parameters of the load function and opens the dialog
            open_config.Filter = "Text Files|*.txt";
            open_config.InitialDirectory = "C:";
            open_config.DefaultExt = "txt";
            open_config.FileName = "configuration";
            open_config.ShowDialog();
        }

        // TODO: Check if config fits the vehicle
        private void open_config_FileOk(object sender, CancelEventArgs e)
        {
            // loads file to the string input
            string path = open_config.FileName;
            StreamReader streamReader = new StreamReader(path);
            string input = streamReader.ReadToEnd();
            streamReader.Close();

            // Splits by ; into an array of axles
            string[] input_conf = input.Split(';');
            if (validate(input_conf))
            {
                // Iterates over the array of axles and writes it to the starting configuration
                for (int i = 0; i < Variables.vehicle_size; i++)
                {
                    Variables.configuration_start.Theta[i] = Convert.ToInt32(input_conf[i]);
                }
                trackBar0.Value = Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)];
                // Draws the vehicle
                this.simpleOpenGlControl3.Invalidate();
            }
        }

        public bool validate(string[] entries)
        {
            // Checks a given entry
            if (entries.Length != Variables.vehicle_size)
            {
                MessageBox.Show("The configurtion you are trying to load does not fit your current vehicle. Please make sure they are the same length.");
                return false;
            }
            return true;
        }

        private void button_reset_config_Click(object sender, EventArgs e)
        {
            // Resets back to the default (in this case random) configuration
            Variables.configuration_start = new configuration();
            trackBar0.Value = Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)];
            this.simpleOpenGlControl3.Invalidate();
        }
    }
}
