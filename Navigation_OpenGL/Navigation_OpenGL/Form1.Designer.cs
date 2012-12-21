namespace Navigation_OpenGL
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.timer_load = new System.Windows.Forms.Timer(this.components);
            this.button_load = new System.Windows.Forms.Button();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.text_axle0 = new System.Windows.Forms.TextBox();
            this.button_add_axle = new System.Windows.Forms.Button();
            this.button_add_box = new System.Windows.Forms.Button();
            this.button_save_vehicle = new System.Windows.Forms.Button();
            this.button_load_vehicle = new System.Windows.Forms.Button();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.button_genomeToPath = new System.Windows.Forms.Button();
            this.checkBox_readOnly = new System.Windows.Forms.CheckBox();
            this.bar_algorithm_progress = new System.Windows.Forms.ProgressBar();
            this.button_cancel = new System.Windows.Forms.Button();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.button_start = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.driveButton = new System.Windows.Forms.Button();
            this.button_path = new System.Windows.Forms.Button();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.button_reset = new System.Windows.Forms.Button();
            this.text_explanation = new System.Windows.Forms.TextBox();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.button_set_end = new System.Windows.Forms.Button();
            this.button_set_start = new System.Windows.Forms.Button();
            this.text_end = new System.Windows.Forms.TextBox();
            this.text_start = new System.Windows.Forms.TextBox();
            this.counter_axle = new System.Windows.Forms.NumericUpDown();
            this.trackBar0 = new System.Windows.Forms.TrackBar();
            this.button_reset_config = new System.Windows.Forms.Button();
            this.button_load_config = new System.Windows.Forms.Button();
            this.button_save_config = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.glControl1 = new OpenTK.GLControl();
            this.save_vehicle = new System.Windows.Forms.SaveFileDialog();
            this.open_vehicle = new System.Windows.Forms.OpenFileDialog();
            this.open_config = new System.Windows.Forms.OpenFileDialog();
            this.save_config = new System.Windows.Forms.SaveFileDialog();
            this.geneticalgorithm = new System.ComponentModel.BackgroundWorker();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.counter_axle)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar0)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer_load
            // 
            this.timer_load.Interval = 10;
            this.timer_load.Tick += new System.EventHandler(this.timer_load_Tick);
            // 
            // button_load
            // 
            this.button_load.Location = new System.Drawing.Point(6, 6);
            this.button_load.Name = "button_load";
            this.button_load.Size = new System.Drawing.Size(75, 23);
            this.button_load.TabIndex = 2;
            this.button_load.Text = "Load Map";
            this.toolTip1.SetToolTip(this.button_load, "Load a new Map (Bitmap, max. 800x600)");
            this.button_load.UseVisualStyleBackColor = true;
            this.button_load.Click += new System.EventHandler(this.button_load_Click);
            // 
            // toolTip1
            // 
            this.toolTip1.IsBalloon = true;
            this.toolTip1.ToolTipTitle = "Help";
            this.toolTip1.Popup += new System.Windows.Forms.PopupEventHandler(this.toolTip1_Popup);
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox1.Location = new System.Drawing.Point(6, 64);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(80, 415);
            this.textBox1.TabIndex = 3;
            this.toolTip1.SetToolTip(this.textBox1, "Send debuging output here.");
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // text_axle0
            // 
            this.text_axle0.Location = new System.Drawing.Point(110, 5);
            this.text_axle0.Multiline = true;
            this.text_axle0.Name = "text_axle0";
            this.text_axle0.ReadOnly = true;
            this.text_axle0.Size = new System.Drawing.Size(40, 40);
            this.text_axle0.TabIndex = 16;
            this.toolTip1.SetToolTip(this.text_axle0, "First axle can only be defined in the default constructor");
            // 
            // button_add_axle
            // 
            this.button_add_axle.Location = new System.Drawing.Point(87, 51);
            this.button_add_axle.Name = "button_add_axle";
            this.button_add_axle.Size = new System.Drawing.Size(75, 23);
            this.button_add_axle.TabIndex = 17;
            this.button_add_axle.Text = "Add Axle";
            this.toolTip1.SetToolTip(this.button_add_axle, "Adds the latest box to the vehicle");
            this.button_add_axle.UseVisualStyleBackColor = true;
            this.button_add_axle.Click += new System.EventHandler(this.button_add_axle_Click);
            // 
            // button_add_box
            // 
            this.button_add_box.Location = new System.Drawing.Point(6, 51);
            this.button_add_box.Name = "button_add_box";
            this.button_add_box.Size = new System.Drawing.Size(75, 23);
            this.button_add_box.TabIndex = 18;
            this.button_add_box.Text = "Add Box";
            this.toolTip1.SetToolTip(this.button_add_box, "Adds an additional box for the next axle");
            this.button_add_box.UseVisualStyleBackColor = true;
            this.button_add_box.Click += new System.EventHandler(this.button_add_box_Click);
            // 
            // button_save_vehicle
            // 
            this.button_save_vehicle.Location = new System.Drawing.Point(6, 80);
            this.button_save_vehicle.Name = "button_save_vehicle";
            this.button_save_vehicle.Size = new System.Drawing.Size(75, 23);
            this.button_save_vehicle.TabIndex = 19;
            this.button_save_vehicle.Text = "Save";
            this.toolTip1.SetToolTip(this.button_save_vehicle, "Saves the current starting configuration");
            this.button_save_vehicle.UseVisualStyleBackColor = true;
            this.button_save_vehicle.Click += new System.EventHandler(this.button_save_vehicle_Click);
            // 
            // button_load_vehicle
            // 
            this.button_load_vehicle.Location = new System.Drawing.Point(87, 80);
            this.button_load_vehicle.Name = "button_load_vehicle";
            this.button_load_vehicle.Size = new System.Drawing.Size(75, 23);
            this.button_load_vehicle.TabIndex = 20;
            this.button_load_vehicle.Text = "Load";
            this.toolTip1.SetToolTip(this.button_load_vehicle, "Loads a starting configuration");
            this.button_load_vehicle.UseVisualStyleBackColor = true;
            this.button_load_vehicle.Click += new System.EventHandler(this.button_load_vehicle_Click);
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage1.Controls.Add(this.button_genomeToPath);
            this.tabPage1.Controls.Add(this.checkBox_readOnly);
            this.tabPage1.Controls.Add(this.bar_algorithm_progress);
            this.tabPage1.Controls.Add(this.button_cancel);
            this.tabPage1.Controls.Add(this.textBox3);
            this.tabPage1.Controls.Add(this.button_start);
            this.tabPage1.Controls.Add(this.textBox2);
            this.tabPage1.Controls.Add(this.button_load);
            this.tabPage1.Controls.Add(this.textBox1);
            this.tabPage1.Controls.Add(this.driveButton);
            this.tabPage1.Controls.Add(this.button_path);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(255, 485);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Main";
            this.toolTip1.SetToolTip(this.tabPage1, "General Settings and Information");
            // 
            // button_genomeToPath
            // 
            this.button_genomeToPath.Enabled = false;
            this.button_genomeToPath.Location = new System.Drawing.Point(93, 145);
            this.button_genomeToPath.Name = "button_genomeToPath";
            this.button_genomeToPath.Size = new System.Drawing.Size(100, 23);
            this.button_genomeToPath.TabIndex = 19;
            this.button_genomeToPath.Text = "Genome to Path";
            this.button_genomeToPath.UseVisualStyleBackColor = true;
            this.button_genomeToPath.Click += new System.EventHandler(this.button_genomeToPath_Click);
            // 
            // checkBox_readOnly
            // 
            this.checkBox_readOnly.AutoSize = true;
            this.checkBox_readOnly.Checked = true;
            this.checkBox_readOnly.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox_readOnly.Location = new System.Drawing.Point(93, 121);
            this.checkBox_readOnly.Name = "checkBox_readOnly";
            this.checkBox_readOnly.Size = new System.Drawing.Size(119, 17);
            this.checkBox_readOnly.TabIndex = 18;
            this.checkBox_readOnly.Text = "Genome Read Only";
            this.checkBox_readOnly.UseVisualStyleBackColor = true;
            this.checkBox_readOnly.CheckedChanged += new System.EventHandler(this.checkBox_readOnly_CheckedChanged);
            // 
            // bar_algorithm_progress
            // 
            this.bar_algorithm_progress.Location = new System.Drawing.Point(93, 91);
            this.bar_algorithm_progress.Name = "bar_algorithm_progress";
            this.bar_algorithm_progress.Size = new System.Drawing.Size(151, 23);
            this.bar_algorithm_progress.TabIndex = 17;
            // 
            // button_cancel
            // 
            this.button_cancel.Enabled = false;
            this.button_cancel.Location = new System.Drawing.Point(169, 7);
            this.button_cancel.Name = "button_cancel";
            this.button_cancel.Size = new System.Drawing.Size(75, 23);
            this.button_cancel.TabIndex = 16;
            this.button_cancel.Text = "Cancel";
            this.button_cancel.UseVisualStyleBackColor = true;
            this.button_cancel.Click += new System.EventHandler(this.button_cancel_Click);
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(169, 35);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(39, 20);
            this.textBox3.TabIndex = 15;
            // 
            // button_start
            // 
            this.button_start.Location = new System.Drawing.Point(88, 7);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(75, 23);
            this.button_start.TabIndex = 14;
            this.button_start.Text = "Start";
            this.button_start.UseVisualStyleBackColor = true;
            this.button_start.Click += new System.EventHandler(this.button_start_Click);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(93, 64);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 20);
            this.textBox2.TabIndex = 13;
            // 
            // driveButton
            // 
            this.driveButton.Location = new System.Drawing.Point(87, 35);
            this.driveButton.Name = "driveButton";
            this.driveButton.Size = new System.Drawing.Size(75, 23);
            this.driveButton.TabIndex = 12;
            this.driveButton.Text = "Drive";
            this.driveButton.UseVisualStyleBackColor = true;
            this.driveButton.Click += new System.EventHandler(this.driveButton_Click);
            // 
            // button_path
            // 
            this.button_path.Cursor = System.Windows.Forms.Cursors.Help;
            this.button_path.Location = new System.Drawing.Point(6, 35);
            this.button_path.Name = "button_path";
            this.button_path.Size = new System.Drawing.Size(75, 23);
            this.button_path.TabIndex = 11;
            this.button_path.Text = "Start Path";
            this.button_path.UseVisualStyleBackColor = true;
            this.button_path.Click += new System.EventHandler(this.button_path_Click);
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage2.Controls.Add(this.button_reset);
            this.tabPage2.Controls.Add(this.button_load_vehicle);
            this.tabPage2.Controls.Add(this.button_save_vehicle);
            this.tabPage2.Controls.Add(this.button_add_box);
            this.tabPage2.Controls.Add(this.button_add_axle);
            this.tabPage2.Controls.Add(this.text_axle0);
            this.tabPage2.Controls.Add(this.text_explanation);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(255, 485);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Vehicle";
            this.toolTip1.SetToolTip(this.tabPage2, "Allows editing/saving/loading of vehicle data");
            // 
            // button_reset
            // 
            this.button_reset.Location = new System.Drawing.Point(6, 109);
            this.button_reset.Name = "button_reset";
            this.button_reset.Size = new System.Drawing.Size(75, 23);
            this.button_reset.TabIndex = 21;
            this.button_reset.Text = "Reset";
            this.toolTip1.SetToolTip(this.button_reset, "Resets the vehicle to the default one");
            this.button_reset.UseVisualStyleBackColor = true;
            this.button_reset.Click += new System.EventHandler(this.button_reset_Click);
            // 
            // text_explanation
            // 
            this.text_explanation.Location = new System.Drawing.Point(5, 5);
            this.text_explanation.Multiline = true;
            this.text_explanation.Name = "text_explanation";
            this.text_explanation.ReadOnly = true;
            this.text_explanation.Size = new System.Drawing.Size(100, 40);
            this.text_explanation.TabIndex = 15;
            // 
            // tabPage3
            // 
            this.tabPage3.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage3.Controls.Add(this.radioButton2);
            this.tabPage3.Controls.Add(this.radioButton1);
            this.tabPage3.Controls.Add(this.button_set_end);
            this.tabPage3.Controls.Add(this.button_set_start);
            this.tabPage3.Controls.Add(this.text_end);
            this.tabPage3.Controls.Add(this.text_start);
            this.tabPage3.Controls.Add(this.counter_axle);
            this.tabPage3.Controls.Add(this.trackBar0);
            this.tabPage3.Controls.Add(this.button_reset_config);
            this.tabPage3.Controls.Add(this.button_load_config);
            this.tabPage3.Controls.Add(this.button_save_config);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(255, 485);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Configuration";
            this.toolTip1.SetToolTip(this.tabPage3, "Allows editing/loading/saving of Start/End Configuration data");
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(175, 109);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(69, 17);
            this.radioButton2.TabIndex = 15;
            this.radioButton2.Text = "End Conf";
            this.radioButton2.UseVisualStyleBackColor = true;
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.Location = new System.Drawing.Point(175, 83);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(72, 17);
            this.radioButton1.TabIndex = 14;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "Start Conf";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // button_set_end
            // 
            this.button_set_end.Location = new System.Drawing.Point(112, 109);
            this.button_set_end.Name = "button_set_end";
            this.button_set_end.Size = new System.Drawing.Size(56, 23);
            this.button_set_end.TabIndex = 13;
            this.button_set_end.Text = "Set End";
            this.toolTip1.SetToolTip(this.button_set_end, "Sets a new ending point (x<800, y<600)");
            this.button_set_end.UseVisualStyleBackColor = true;
            this.button_set_end.Click += new System.EventHandler(this.button_set_end_Click);
            // 
            // button_set_start
            // 
            this.button_set_start.Location = new System.Drawing.Point(112, 83);
            this.button_set_start.Name = "button_set_start";
            this.button_set_start.Size = new System.Drawing.Size(56, 23);
            this.button_set_start.TabIndex = 12;
            this.button_set_start.Text = "Set Start";
            this.toolTip1.SetToolTip(this.button_set_start, "Sets a new starting point (x<800, y<600)");
            this.button_set_start.UseVisualStyleBackColor = true;
            this.button_set_start.Click += new System.EventHandler(this.button_set_start_Click);
            // 
            // text_end
            // 
            this.text_end.BackColor = System.Drawing.Color.RoyalBlue;
            this.text_end.Location = new System.Drawing.Point(6, 112);
            this.text_end.Name = "text_end";
            this.text_end.Size = new System.Drawing.Size(100, 20);
            this.text_end.TabIndex = 11;
            this.toolTip1.SetToolTip(this.text_end, "Ending point (x<800, y<600)");
            // 
            // text_start
            // 
            this.text_start.BackColor = System.Drawing.Color.Red;
            this.text_start.Location = new System.Drawing.Point(6, 86);
            this.text_start.Name = "text_start";
            this.text_start.Size = new System.Drawing.Size(100, 20);
            this.text_start.TabIndex = 10;
            this.toolTip1.SetToolTip(this.text_start, "Starting point (x<800, y<600)");
            // 
            // counter_axle
            // 
            this.counter_axle.Location = new System.Drawing.Point(205, 31);
            this.counter_axle.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.counter_axle.Name = "counter_axle";
            this.counter_axle.Size = new System.Drawing.Size(38, 20);
            this.counter_axle.TabIndex = 9;
            this.toolTip1.SetToolTip(this.counter_axle, "Current axle.");
            this.counter_axle.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.counter_axle.ValueChanged += new System.EventHandler(this.counter_axle_ValueChanged);
            // 
            // trackBar0
            // 
            this.trackBar0.Location = new System.Drawing.Point(6, 6);
            this.trackBar0.Maximum = 360;
            this.trackBar0.Name = "trackBar0";
            this.trackBar0.Size = new System.Drawing.Size(243, 45);
            this.trackBar0.TabIndex = 8;
            this.trackBar0.Value = 1;
            this.trackBar0.ValueChanged += new System.EventHandler(this.trackBar0_ValueChanged);
            // 
            // button_reset_config
            // 
            this.button_reset_config.Location = new System.Drawing.Point(168, 57);
            this.button_reset_config.Name = "button_reset_config";
            this.button_reset_config.Size = new System.Drawing.Size(75, 23);
            this.button_reset_config.TabIndex = 7;
            this.button_reset_config.Text = "Reset";
            this.toolTip1.SetToolTip(this.button_reset_config, "Resets to default (random) configuration.");
            this.button_reset_config.UseVisualStyleBackColor = true;
            this.button_reset_config.Click += new System.EventHandler(this.button_reset_config_Click);
            // 
            // button_load_config
            // 
            this.button_load_config.Location = new System.Drawing.Point(87, 57);
            this.button_load_config.Name = "button_load_config";
            this.button_load_config.Size = new System.Drawing.Size(75, 23);
            this.button_load_config.TabIndex = 6;
            this.button_load_config.Text = "Load";
            this.toolTip1.SetToolTip(this.button_load_config, "Loads a configuration. Must fit current vehicle.");
            this.button_load_config.UseVisualStyleBackColor = true;
            this.button_load_config.Click += new System.EventHandler(this.button_load_config_Click);
            // 
            // button_save_config
            // 
            this.button_save_config.Location = new System.Drawing.Point(6, 57);
            this.button_save_config.Name = "button_save_config";
            this.button_save_config.Size = new System.Drawing.Size(75, 23);
            this.button_save_config.TabIndex = 5;
            this.button_save_config.Text = "Save";
            this.toolTip1.SetToolTip(this.button_save_config, "Saves the current configuration.");
            this.button_save_config.UseVisualStyleBackColor = true;
            this.button_save_config.Click += new System.EventHandler(this.button_save_config_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(1043, 13);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(263, 511);
            this.tabControl1.TabIndex = 13;
            // 
            // glControl1
            // 
            this.glControl1.BackColor = System.Drawing.Color.Black;
            this.glControl1.Location = new System.Drawing.Point(12, 12);
            this.glControl1.Name = "glControl1";
            this.glControl1.Size = new System.Drawing.Size(1024, 512);
            this.glControl1.TabIndex = 14;
            this.glControl1.VSync = false;
            this.glControl1.Load += new System.EventHandler(this.glControl1_Load);
            this.glControl1.Paint += new System.Windows.Forms.PaintEventHandler(this.glControl1_Paint);
            // 
            // save_vehicle
            // 
            this.save_vehicle.DefaultExt = "txt";
            this.save_vehicle.FileName = "vehicle";
            this.save_vehicle.InitialDirectory = "C:";
            this.save_vehicle.Title = "Save Vehicle";
            this.save_vehicle.FileOk += new System.ComponentModel.CancelEventHandler(this.save_vehicle_FileOk);
            // 
            // open_vehicle
            // 
            this.open_vehicle.DefaultExt = "txt";
            this.open_vehicle.FileName = "vehicle";
            this.open_vehicle.InitialDirectory = "C:";
            this.open_vehicle.Title = "Open Vehicle";
            this.open_vehicle.FileOk += new System.ComponentModel.CancelEventHandler(this.open_vehicle_FileOk);
            // 
            // open_config
            // 
            this.open_config.FileName = "openFileDialog1";
            this.open_config.FileOk += new System.ComponentModel.CancelEventHandler(this.open_config_FileOk);
            // 
            // save_config
            // 
            this.save_config.DefaultExt = "txt";
            this.save_config.FileName = "configuration";
            this.save_config.InitialDirectory = "C:";
            this.save_config.Title = "Save Configuration";
            this.save_config.FileOk += new System.ComponentModel.CancelEventHandler(this.save_config_FileOk);
            // 
            // geneticalgorithm
            // 
            this.geneticalgorithm.DoWork += new System.ComponentModel.DoWorkEventHandler(this.geneticalgorithm_DoWork);
            this.geneticalgorithm.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.geneticalgorithm_ProgressChanged);
            this.geneticalgorithm.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.geneticalgorithm_RunWorkerCompleted);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1318, 529);
            this.Controls.Add(this.glControl1);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "Navigation";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.counter_axle)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar0)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timer_load;
        private System.Windows.Forms.Button button_load;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.Button button_path;
        private System.Windows.Forms.Button driveButton;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TextBox text_explanation;
        private System.Windows.Forms.TextBox text_axle0;
        private System.Windows.Forms.Button button_add_axle;
        private System.Windows.Forms.Button button_add_box;
        private System.Windows.Forms.Button button_save_vehicle;
        private System.Windows.Forms.Button button_load_vehicle;
        private System.Windows.Forms.SaveFileDialog save_vehicle;
        private System.Windows.Forms.OpenFileDialog open_vehicle;
        private System.Windows.Forms.Button button_reset;
        private System.Windows.Forms.Button button_save_config;
        private System.Windows.Forms.Button button_load_config;
        private System.Windows.Forms.Button button_reset_config;
        private System.Windows.Forms.TrackBar trackBar0;
        private System.Windows.Forms.NumericUpDown counter_axle;
        private System.Windows.Forms.OpenFileDialog open_config;
        private System.Windows.Forms.SaveFileDialog save_config;
        private System.Windows.Forms.Button button_set_end;
        private System.Windows.Forms.Button button_set_start;
        private System.Windows.Forms.TextBox text_end;
        private System.Windows.Forms.TextBox text_start;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button button_start;
        public OpenTK.GLControl glControl1;
        public System.Windows.Forms.TextBox textBox1;
        public System.Windows.Forms.TextBox textBox3;
        private System.ComponentModel.BackgroundWorker geneticalgorithm;
        private System.Windows.Forms.Button button_cancel;
        private System.Windows.Forms.CheckBox checkBox_readOnly;
        private System.Windows.Forms.Button button_genomeToPath;
        public System.Windows.Forms.ProgressBar bar_algorithm_progress;
    }
}

