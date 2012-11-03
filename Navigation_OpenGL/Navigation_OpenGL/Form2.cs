using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using Tao.OpenGl;
using Tao.Platform.Windows;

namespace Navigation_OpenGL
{
    public partial class Form2 : Form
    {

        public Form2()
        {
            InitializeComponent();
            this.simpleOpenGlControl2.InitializeContexts();
            Gl.glClearColor(0, 0, 0, 0);
            Gl.glMatrixMode(Gl.GL_PROJECTION);
            Gl.glLoadIdentity();
            Gl.glOrtho(0, 760, 85, 0, 0, 1);
            Gl.glMatrixMode(Gl.GL_MODELVIEW);
            Gl.glDisable(Gl.GL_DEPTH_TEST);

            // Adds the default box for the default axle to the array
            Variables.axles[0] = text_axle0;
            // Draws and fills all the boxes
            to_boxes();
            text_explanation.Text = "M of axle" + System.Environment.NewLine +
                "L of axle" + System.Environment.NewLine;
            }

        private void simpleOpenGlControl2_Load(object sender, EventArgs e)
        {
            
        }

        private void simpleOpenGlControl2_Paint(object sender, PaintEventArgs e)
        {
            // Paints all axles from the starting configuration when called
            Gl.glClear(Gl.GL_COLOR_BUFFER_BIT);
            Gl.glPointSize(2);


            Drawings.draw_measure(10, 75);
        }

        private void button_add_axle_Click(object sender, EventArgs e)
        {
            // Checks if box is empty
            if (Variables.axles[Variables.vehicle_size] == null)
                MessageBox.Show("Es gibt nichts hinzuzufügen");
            else
            {
                // Splits the entry of box i (i = Variables.vehicle_size) into an array
                string[] entries = Variables.axles[Variables.vehicle_size].Text.Split(';');
                // Checks if the entry was valid
                if (validate_axle(entries))
                {
                    // Adds the axle to the starting configuration at position i
                    add_axle(entries, Variables.vehicle_size);
                    // Makes the current box ReadOnly and creates a new box for axle i+1
                    Variables.axles[Variables.vehicle_size].ReadOnly = true;
                    Variables.vehicle_size++;
                }
            }
        }

        public void add_axle(string[] entries, int i)
        {
            // Adds the axle i (i = variables.vehicle_size) to the starting configuration at i
            Variables.vehicle.L[i] = Convert.ToDouble(entries[0]);
            Variables.vehicle.M[i] = Convert.ToDouble(entries[1]);
            this.simpleOpenGlControl2.Invalidate();
        }

        public bool validate_axle(string[] entries)
        {
            // Checks a given entry
            if (entries.Length != 2)
            {
                MessageBox.Show("Please enter 2 numbers seperated by ';'");
                return false;
            }
            return true;
        }

        public void add_box()
        {
            // Checks if there is another non-added box
            if (Variables.axles[Variables.vehicle_size] != null)
                MessageBox.Show("Please add the current box to the vehicle before adding another one");
            else
            {
                // Adds a new box to the GUI
                Variables.axles[Variables.vehicle_size] = new TextBox();
                this.Controls.Add(Variables.axles[Variables.vehicle_size]);
                Variables.axles[Variables.vehicle_size].Location = new System.Drawing.Point(110 + Variables.vehicle_size * 45, 90);
                Variables.axles[Variables.vehicle_size].Multiline = true;
                Variables.axles[Variables.vehicle_size].Size = new System.Drawing.Size(40, 40);
                Variables.axles[Variables.vehicle_size].Name = "text_axle" + Variables.vehicle_size;
                Variables.axles[Variables.vehicle_size].TabIndex = Variables.vehicle_size;
                Variables.axles[Variables.vehicle_size].Visible = true;
            }
        }

        public void add_box(int i)
        {
            // Same as above but adds at a given parameter i instead of using the global variable vehicle size to add at the end
            Variables.axles[i] = new TextBox();
            this.Controls.Add(Variables.axles[i]);
            Variables.axles[i].Location = new System.Drawing.Point(110 + i * 45, 90);
            Variables.axles[i].Multiline = true;
            Variables.axles[i].Size = new System.Drawing.Size(40, 40);
            Variables.axles[i].Name = "text_axle" + i;
            Variables.axles[i].TabIndex = i;
            Variables.axles[i].Visible = true;
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            
        }

        private void button_save_vehicle_Click(object sender, EventArgs e)
        {
            // Defines some parameters of the save function and opens the dialog
            save_vehicle.Filter = "Text Files|*.txt";
            save_vehicle.ShowDialog();
        }

        private void save_vehicle_FileOk(object sender, CancelEventArgs e)
        {
            // Initializes the output string
            string output = "";
            // Iterates over the vehicle, seperating values by , and axles by ;
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                output = output + Variables.vehicle.L[i].ToString() + ";"
                + Variables.vehicle.M[i].ToString();
                if (i < Variables.vehicle_size-1)
                    output = output + '|';
            }
            // Saves the vehicle
            System.IO.Stream fileStream = save_vehicle.OpenFile();
            System.IO.StreamWriter sw = new System.IO.StreamWriter(fileStream);
            sw.WriteLine(output);
            sw.Flush();
            sw.Close();
        }

        private void button_load_vehicle_Click(object sender, EventArgs e)
        {
            // Defines some parameters of the load function and opens the dialog
            open_vehicle.Filter = "Text Files|*.txt";
            open_vehicle.InitialDirectory = "C:";
            open_vehicle.DefaultExt = "txt";
            open_vehicle.FileName = "vehicle";
            open_vehicle.ShowDialog();
        }

        private void open_vehicle_FileOk(object sender, CancelEventArgs e)
        {
            // loads file to the string input
            string path = open_vehicle.FileName;
            StreamReader streamReader = new StreamReader(path);
            string input = streamReader.ReadToEnd();
            streamReader.Close();

            // Splits by ; into an array of axles
            string[] input_conf = input.Split('|');
            // Sets the vehicle size 
            Variables.vehicle_size = input_conf.Length;

            // Iterates over the array of axles and writes it to the starting configuration
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                string[] input_tmp = input_conf[i].Split(';');
                Variables.vehicle.L[i] = Convert.ToDouble(input_tmp[0]);
                Variables.vehicle.M[i] = Convert.ToDouble(input_tmp[1]);
            }
            // Creates and fills all the boxes needed
            to_boxes();
            // Draws the vehicle
            this.simpleOpenGlControl2.Invalidate();
        }

        private void to_boxes()
        {
            // to_boxes takes the current configuration_start and writes it to the GUI, creating as many boxes as needed
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                // If a box does not yet exist it is created
                if (Variables.axles[i] == null || i != 0)
                    add_box(i);
                Variables.axles[i].Text = Variables.vehicle.M[i].ToString() + ";" + System.Environment.NewLine
                + Variables.vehicle.L[i].ToString() + System.Environment.NewLine;
                Variables.axles[i].ReadOnly = true;
            }
        }

        private void button_add_box_Click(object sender, EventArgs e)
        {
            add_box();
        }

        private void button_reset_Click(object sender, EventArgs e)
        {
            // Resets back to the default configuration and clears the GUI
            for (int i = 1; i < Variables.vehicle_size; i++)
            {
                Variables.axles[i].Visible = false;
            }
            Variables.axles = new System.Windows.Forms.TextBox[10];
            Variables.vehicle = new Vehicle();
            Variables.vehicle_size = 1;
            this.simpleOpenGlControl2.Invalidate();
        }

        private void timer_invalidate_Tick(object sender, EventArgs e)
        {
            this.simpleOpenGlControl2.Invalidate();
        }
    }
}
