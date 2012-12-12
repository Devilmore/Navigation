using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using OpenTK.Graphics.OpenGL;
using System.IO;
using System.Diagnostics;


namespace Navigation_OpenGL
{
    public partial class Form1 : Form
    {
        // Loads the map
        Bitmap image = new Bitmap(Application.StartupPath + "\\Map_512.bmp");

        // Stopwatch
        Stopwatch stopWatch = new Stopwatch();

        public Form1()
        {
            InitializeComponent();

            // Turn of CorssThread warnings because we can
            CheckForIllegalCrossThreadCalls = false;

            // Adds the default box for the default axle to the array
            Variables.axles[0] = text_axle0;

            // Creates the map for the Fitness function
            Variables.map = createMap(image);

            // Draws and fills all the boxes
            to_boxes();

            // Fills the explanation box
            text_explanation.Text = "M of axle" + System.Environment.NewLine +
                "L of axle" + System.Environment.NewLine;

            // Initializes the trackbar
            trackBar0.Value = Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)];
            counter_axle.Maximum = Variables.vehicle_size - 1;
        }

        // Use for animations
        private void timer_load_Tick(object sender, EventArgs e)
        {
        }

        // Loads a new map
        private void button_load_Click(object sender, EventArgs e)
        {
            OpenFileDialog omd = new OpenFileDialog();
            if (omd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                Image load_map = Image.FromFile(omd.FileName);
                image = new Bitmap(load_map);
            }

        }
        
        // Tooltip
        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {
        }

        // Creates a boolean array from the given map. This is needed for the fitness function. Move to Fitness Class later
        public bool[,] createMap(Bitmap image)
        {
            bool[,] map = new bool[image.Width, image.Height];

            // Convert to ARGB since otherwise black on the image isn't euqal to Color.black
            int black = Color.Black.ToArgb();
            for (int x = 0; x < image.Width; x++)
            {
                for (int y = 0; y < image.Height; y++)
                {
                    // Sets a field to false if it is black on the map ( if it's a wall)
                    map[x,y] = (image.GetPixel(x,y).ToArgb() == black) ? false : true;
                }
            }
            return map;
        }

        // Stub
        private void Form1_Load(object sender, EventArgs e)
        {
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
        }

        // Creates a Simulation for Path and draws it
        private void driveButton_Click(object sender, EventArgs e)
        {
            Variables.simulation = new Simulation(Variables.vehicle, Variables.path);
            Variables.simulation.run();
            this.glControl1.Refresh();

            // Writes the Collision count to the textbox. Actually do something here later.
            //textBox2.Text = FitnessFunction.getCollisions(Variables.simulation.getPath(), createMap(image)).ToString();
        }

        // Initial OpenGL function called on startup
        private void glControl1_Load(object sender, EventArgs e)
        {
            // Initialize OpenGL Components
            GL.ClearColor(Color.White);
            int w = glControl1.Width;
            int h = glControl1.Height;
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();

            // Bottom-left corner pixel has coordinate (0, 0)
            GL.Ortho(0, w, 0, h, -1, 1);

            // Use all of the glControl painting area
            GL.Viewport(0, 0, w, h);
        }

        public static void draw()
        {
        }

        // Drawing function, called by Refresh()
        public void glControl1_Paint(object sender, PaintEventArgs e)
        {
            // Writes the genome to the textbox
            this.textBox1.Text = Variables.genome.write();

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

            // Draws the vehicle
            // Paints all axles from the starting configuration when called
            
            // Initializing
            GL.PointSize(2);
            GL.Enable(EnableCap.LineSmooth);
            GL.Hint(HintTarget.LineSmoothHint, HintMode.Nicest);
            GL.LineWidth(1);

            Variables.configuration_start.X[0] = Variables.start.x;
            Variables.configuration_start.Y[0] = Variables.start.y;

            // Draws the axles with the static starting point of L[0] (start of first axle)
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                // Draws the Line from L to X, whereas L is equal to M[i-1], except for i=1 where L[0] is fixed
                Drawings.draw(getL, getLstart, Drawings.drawL, i);
                // Draws the Line from X to M
                Drawings.draw(getM, getMstart, Drawings.drawM, i);
            }

            // Draws the points last so they are visible. Red for axle points
            GL.Color3(Color.Red);
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                GL.Begin(BeginMode.Points);
                if (Variables.config_start)
                    GL.Vertex2(Variables.configuration_start.X[i], Variables.configuration_start.Y[i]);
                else
                    GL.Vertex2(Variables.configuration_end.X[i], Variables.configuration_end.Y[i]);
                GL.End();
            }
            
            // Blue for start/end points
            GL.Color3(Color.Blue);
            GL.Begin(BeginMode.Points);
            if (Variables.config_start)
                GL.Vertex2(Variables.start.x, Variables.start.y);
            else
                GL.Vertex2(Variables.end.x, Variables.end.y);
            GL.End();
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                GL.Begin(BeginMode.Points);
                if (Variables.config_start)
                    GL.Vertex2(Variables.configuration_start.Mx[i], Variables.configuration_start.My[i]);
                else
                    GL.Vertex2(Variables.configuration_end.Mx[i], Variables.configuration_end.My[i]);
                GL.End();
            }
            // End Vehicle

            // Draws the ending configuration of the latest simulated path
            if (Variables.simulation != null)
            {
                Drawings.drawConfiguration(configuration.getConfig(new EZPathFollowing.Point2D(Variables.x*27, Variables.y*27), Variables.orientation));
            }
            
            // Draws start and end
            GL.PointSize(5);

            GL.Begin(BeginMode.Points);
            GL.Color3(Color.Red);
            GL.Vertex2(Variables.start.x, Variables.start.y);
            GL.End();

            GL.Begin(BeginMode.Points);
            GL.Color3(Color.Blue);
            GL.Vertex2(Variables.end.x, Variables.end.y);
            GL.End();

            Drawings.draw_measure(20, 20);

            // Draws everything
            glControl1.SwapBuffers();
        }


        // <--------------------------------------------------->
        // Start/End Textbox handling from here

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
            if (ex < 0 || ex > 1024 || ey < 0 || ey > 512)
            {
                MessageBox.Show("The first value must be between 0 and 1024 and the second between 0 and 512.");
                return false;
            }
            return true;
        }

        // <--------------------------------------------------->
        // Vehicle editing from here (formerly From 2)

        // Adds the last box to the vehicle
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
                    this.glControl1.Refresh();
                    counter_axle.Maximum = Variables.vehicle_size - 1;
                }
            }
        }


        // Adds the axle i (i = variables.vehicle_size) to the starting configuration at i
        public void add_axle(string[] entries, int i)
        {
            Variables.vehicle.L[i] = Convert.ToDouble(entries[0]);
            Variables.vehicle.M[i] = Convert.ToDouble(entries[1]);
        }

        // Checks a given entry
        public bool validate_axle(string[] entries)
        {
            if (entries.Length != 2)
            {
                MessageBox.Show("Please enter 2 numbers seperated by ';'");
                return false;
            }
            return true;
        }

        // Adds a new box to the GUI
        public void add_box()
        {
            // Checks if there is another non-added box
            if (Variables.axles[Variables.vehicle_size] != null)
                MessageBox.Show("Please add the current box to the vehicle before adding another one");
            else
            {
                // Adds a new box to the GUI
                Variables.axles[Variables.vehicle_size] = new TextBox();
                this.tabPage2.Controls.Add(Variables.axles[Variables.vehicle_size]);
                Variables.axles[Variables.vehicle_size].Location = new System.Drawing.Point(110 + Variables.vehicle_size * 45, 5);
                Variables.axles[Variables.vehicle_size].Multiline = true;
                Variables.axles[Variables.vehicle_size].Size = new System.Drawing.Size(40, 40);
                Variables.axles[Variables.vehicle_size].Name = "text_axle" + Variables.vehicle_size;
                Variables.axles[Variables.vehicle_size].TabIndex = Variables.vehicle_size;
                Variables.axles[Variables.vehicle_size].Visible = true;
            }
        }

        // Same as above but adds at a given parameter i instead of using the global variable vehicle size to add at the end
        public void add_box(int i)
        {
            Variables.axles[i] = new TextBox();
            this.tabPage2.Controls.Add(Variables.axles[i]);
            Variables.axles[i].Location = new System.Drawing.Point(110 + i * 45, 5);
            Variables.axles[i].Multiline = true;
            Variables.axles[i].Size = new System.Drawing.Size(40, 40);
            Variables.axles[i].Name = "text_axle" + i;
            Variables.axles[i].TabIndex = i;
            Variables.axles[i].Visible = true;
        }


        // Defines some parameters of the save function and opens the dialog
        private void button_save_vehicle_Click(object sender, EventArgs e)
        {
            save_vehicle.Filter = "Text Files|*.txt";
            save_vehicle.ShowDialog();
        }

        // Saves the vehicle to a file
        private void save_vehicle_FileOk(object sender, CancelEventArgs e)
        {
            // Initializes the output string
            string output = "";
            // Iterates over the vehicle, seperating values by , and axles by ;
            for (int i = 0; i < Variables.vehicle_size; i++)
            {
                output = output + Variables.vehicle.L[i].ToString() + ";"
                + Variables.vehicle.M[i].ToString();
                if (i < Variables.vehicle_size - 1)
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

        // Loads a vehicle from file
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
            this.glControl1.Refresh();
            counter_axle.Maximum = Variables.vehicle_size - 1;
            counter_axle.Minimum = 1;
        }

        // Writes the current vehicle to the boxes
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
            this.glControl1.Refresh();
        }

        // <--------------------------------------------------->
        // Configuration editing from here (Formerly Form 3)

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
            // L is fixed for i == 0 since this is the starting point
            if (radioButton1.Checked)
            {
                if (i == 0)
                    return new KeyValuePair<double, double>(Variables.start.x, Variables.start.y);
                else
                    return new KeyValuePair<double, double>(Variables.configuration_start.Mx[i - 1], Variables.configuration_start.My[i - 1]);
            }
            else
            {
                if (i == 0)
                    return new KeyValuePair<double, double>(Variables.end.x, Variables.end.y);
                else
                    return new KeyValuePair<double, double>(Variables.configuration_end.Mx[i - 1], Variables.configuration_end.My[i - 1]);
            }
        }

        // Returns the values X and Y, the starting point for the calculation for M from X
        public KeyValuePair<double, double> getMstart(int i)
        {
            if (radioButton1.Checked)
                return new KeyValuePair<double, double>(Variables.configuration_start.X[i], Variables.configuration_start.Y[i]);
            else
                return new KeyValuePair<double, double>(Variables.configuration_end.X[i], Variables.configuration_end.Y[i]);
        }

        private void trackBar0_ValueChanged(object sender, EventArgs e)
        {
            if (radioButton1.Checked)
            {
                Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)] = trackBar0.Value;
                if (counter_axle.Value == 1)
                    Variables.configuration_start.Theta[0] = Variables.configuration_start.Theta[1];
                this.glControl1.Refresh();
                toolTip1.SetToolTip(trackBar0, trackBar0.Value.ToString());
            }
            else
            {
                Variables.configuration_end.Theta[Convert.ToInt32(counter_axle.Value)] = trackBar0.Value;
                if (counter_axle.Value == 1)
                    Variables.configuration_end.Theta[0] = Variables.configuration_end.Theta[1];
                this.glControl1.Refresh();
                toolTip1.SetToolTip(trackBar0, trackBar0.Value.ToString());
            }
        }

        private void counter_axle_ValueChanged(object sender, EventArgs e)
        {
            if (radioButton1.Checked)
                trackBar0.Value = Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)];
            else
                trackBar0.Value = Variables.configuration_end.Theta[Convert.ToInt32(counter_axle.Value)];
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
                if (radioButton1.Checked)
                    output = output + Variables.configuration_start.Theta[i].ToString();
                else
                    output = output + Variables.configuration_end.Theta[i].ToString();

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
                    if (radioButton1.Checked)
                        Variables.configuration_start.Theta[i] = Convert.ToInt32(input_conf[i]);
                    else
                        Variables.configuration_end.Theta[i] = Convert.ToInt32(input_conf[i]);
                }
                if (radioButton1.Checked)
                    trackBar0.Value = Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)];
                else
                    trackBar0.Value = Variables.configuration_end.Theta[Convert.ToInt32(counter_axle.Value)];
                // Draws the vehicle
                this.glControl1.Refresh();
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
            Variables.configuration_end = new configuration();
            if (radioButton1.Checked)
                trackBar0.Value = Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)];
            else
                trackBar0.Value = Variables.configuration_end.Theta[Convert.ToInt32(counter_axle.Value)];
            this.glControl1.Refresh();
        }

        // Copies the stat of radioButton1 to Variables.config_start for use in other classes
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton1.Checked)
            {
                trackBar0.Value = Variables.configuration_start.Theta[Convert.ToInt32(counter_axle.Value)];
                Variables.config_start = true;
                this.glControl1.Refresh();
            }
            else
            {
                trackBar0.Value = Variables.configuration_end.Theta[Convert.ToInt32(counter_axle.Value)];
                Variables.config_start = false;
                this.glControl1.Refresh();
            }
        }

        private void geneticalgorithm_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;

            stopWatch.Start();
            GeneticAlgorithm ga = new GeneticAlgorithm();
            e.Result = ga.gaMain(worker, e);
        }

        private void geneticalgorithm_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            bar_algorithm_progress.Value = e.ProgressPercentage;
        }

        private void geneticalgorithm_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
                // An Error occured
            if (e.Error != null)
            {
                MessageBox.Show(e.Error.Message);
            }
                // The Algorithm was canceled
            else if (e.Cancelled)
            {
                MessageBox.Show("Canceled");
            }
                // The Algorithm finished but not properly (no idea whether or not this can happen without an error)
            else if (!Convert.ToBoolean(e.Result))
            {
                MessageBox.Show("The Algorithm ended...strangely");
            }
            else
            {
                stopWatch.Stop();
                TimeSpan ts = stopWatch.Elapsed;
                MessageBox.Show("Success! Computation took " + ts.ToString() + " Seconds");
            }

            // Disables the cancel button
            this.button_cancel.Enabled = false;

            // Enables the start button again
            this.button_start.Enabled = true;

            // Enables tab control again
            this.tabControl1.Enabled = true;
        }

        private void button_start_Click(object sender, EventArgs e)
        {
            // Disables the Start button until the GA is done
            this.button_start.Enabled = false;

            // Disables the tabs until the GA is done
            this.tabControl1.Enabled = false;

            // Enables the Cancel Button until GA is done
            this.button_cancel.Enabled = true;

            // Runs the DoWork function
            this.geneticalgorithm.RunWorkerAsync();
        }

        private void button_cancel_Click(object sender, EventArgs e)
        {
            // Cancels the DoWork task
            this.geneticalgorithm.CancelAsync();

            // Disables the cancel button
            this.button_cancel.Enabled = false;

            // Enables the start button again
            this.button_start.Enabled = true;

            // Enables tab control again
            this.tabControl1.Enabled = true;
        }

        private void checkBox_readOnly_CheckedChanged(object sender, EventArgs e)
        {
            this.textBox1.ReadOnly = this.checkBox_readOnly.Checked;
            this.button_genomeToPath.Enabled = !this.checkBox_readOnly.Checked;
        }

        private void button_genomeToPath_Click(object sender, EventArgs e)
        {
            Genome genome = new Genome();
            char[] text = this.textBox1.Text.ToCharArray();

            for (int i = 0; i < 160; i++)
            {
                if (text[i] == '1')
                    genome.Genome1.Set(i, true);   
            }

            Genome.genomeToPath(genome);
            this.glControl1.Refresh();
        }
    }
}
