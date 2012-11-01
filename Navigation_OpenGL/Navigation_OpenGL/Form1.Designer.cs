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
            this.text_start = new System.Windows.Forms.TextBox();
            this.text_end = new System.Windows.Forms.TextBox();
            this.button_set_start = new System.Windows.Forms.Button();
            this.button_set_end = new System.Windows.Forms.Button();
            this.button_vehicle = new System.Windows.Forms.Button();
            this.button_configuration = new System.Windows.Forms.Button();
            this.button_path = new System.Windows.Forms.Button();
            this.driveButton = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.glControl1 = new OpenTK.GLControl();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer_load
            // 
            this.timer_load.Interval = 1000;
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
            this.textBox1.Location = new System.Drawing.Point(6, 142);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(80, 399);
            this.textBox1.TabIndex = 3;
            this.toolTip1.SetToolTip(this.textBox1, "Send debuging output here.");
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // text_start
            // 
            this.text_start.BackColor = System.Drawing.Color.Red;
            this.text_start.Location = new System.Drawing.Point(6, 32);
            this.text_start.Name = "text_start";
            this.text_start.Size = new System.Drawing.Size(100, 20);
            this.text_start.TabIndex = 5;
            this.toolTip1.SetToolTip(this.text_start, "Starting point (x<800, y<600)");
            this.text_start.TextChanged += new System.EventHandler(this.text_start_TextChanged);
            // 
            // text_end
            // 
            this.text_end.BackColor = System.Drawing.Color.RoyalBlue;
            this.text_end.Location = new System.Drawing.Point(6, 58);
            this.text_end.Name = "text_end";
            this.text_end.Size = new System.Drawing.Size(100, 20);
            this.text_end.TabIndex = 6;
            this.toolTip1.SetToolTip(this.text_end, "Ending point (x<800, y<600)");
            this.text_end.TextChanged += new System.EventHandler(this.text_end_TextChanged);
            // 
            // button_set_start
            // 
            this.button_set_start.Location = new System.Drawing.Point(112, 30);
            this.button_set_start.Name = "button_set_start";
            this.button_set_start.Size = new System.Drawing.Size(56, 23);
            this.button_set_start.TabIndex = 7;
            this.button_set_start.Text = "Set Start";
            this.toolTip1.SetToolTip(this.button_set_start, "Sets a new starting point (x<800, y<600)");
            this.button_set_start.UseVisualStyleBackColor = true;
            this.button_set_start.Click += new System.EventHandler(this.button_set_start_Click);
            // 
            // button_set_end
            // 
            this.button_set_end.Location = new System.Drawing.Point(112, 58);
            this.button_set_end.Name = "button_set_end";
            this.button_set_end.Size = new System.Drawing.Size(56, 23);
            this.button_set_end.TabIndex = 8;
            this.button_set_end.Text = "Set End";
            this.toolTip1.SetToolTip(this.button_set_end, "Sets a new ending point (x<800, y<600)");
            this.button_set_end.UseVisualStyleBackColor = true;
            this.button_set_end.Click += new System.EventHandler(this.button_set_end_Click);
            // 
            // button_vehicle
            // 
            this.button_vehicle.Location = new System.Drawing.Point(6, 84);
            this.button_vehicle.Name = "button_vehicle";
            this.button_vehicle.Size = new System.Drawing.Size(75, 23);
            this.button_vehicle.TabIndex = 9;
            this.button_vehicle.Text = "Edit vehicle";
            this.toolTip1.SetToolTip(this.button_vehicle, "Opens a new window with options to see and edit the current vehicle");
            this.button_vehicle.UseVisualStyleBackColor = true;
            this.button_vehicle.Click += new System.EventHandler(this.button_vehicle_Click);
            // 
            // button_configuration
            // 
            this.button_configuration.Location = new System.Drawing.Point(87, 84);
            this.button_configuration.Name = "button_configuration";
            this.button_configuration.Size = new System.Drawing.Size(75, 23);
            this.button_configuration.TabIndex = 10;
            this.button_configuration.Text = "Edit Start";
            this.toolTip1.SetToolTip(this.button_configuration, "Opens a new window with options to see and edit the current starting configuratio" +
        "n");
            this.button_configuration.UseVisualStyleBackColor = true;
            this.button_configuration.Click += new System.EventHandler(this.button_configuration_Click);
            // 
            // button_path
            // 
            this.button_path.Cursor = System.Windows.Forms.Cursors.Help;
            this.button_path.Location = new System.Drawing.Point(6, 113);
            this.button_path.Name = "button_path";
            this.button_path.Size = new System.Drawing.Size(75, 23);
            this.button_path.TabIndex = 11;
            this.button_path.Text = "Start Path";
            this.button_path.UseVisualStyleBackColor = true;
            this.button_path.Click += new System.EventHandler(this.button_path_Click);
            // 
            // driveButton
            // 
            this.driveButton.Location = new System.Drawing.Point(87, 113);
            this.driveButton.Name = "driveButton";
            this.driveButton.Size = new System.Drawing.Size(75, 23);
            this.driveButton.TabIndex = 12;
            this.driveButton.Text = "DRIVE";
            this.driveButton.UseVisualStyleBackColor = true;
            this.driveButton.Click += new System.EventHandler(this.driveButton_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(1043, 13);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(180, 573);
            this.tabControl1.TabIndex = 13;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.button_load);
            this.tabPage1.Controls.Add(this.textBox1);
            this.tabPage1.Controls.Add(this.button_set_end);
            this.tabPage1.Controls.Add(this.driveButton);
            this.tabPage1.Controls.Add(this.button_set_start);
            this.tabPage1.Controls.Add(this.text_start);
            this.tabPage1.Controls.Add(this.button_path);
            this.tabPage1.Controls.Add(this.text_end);
            this.tabPage1.Controls.Add(this.button_configuration);
            this.tabPage1.Controls.Add(this.button_vehicle);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(172, 547);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(172, 571);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // tabPage3
            // 
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(172, 571);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "tabPage3";
            this.tabPage3.UseVisualStyleBackColor = true;
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
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1235, 590);
            this.Controls.Add(this.glControl1);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "Navigation";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timer_load;
        private System.Windows.Forms.Button button_load;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox text_start;
        private System.Windows.Forms.TextBox text_end;
        private System.Windows.Forms.Button button_set_start;
        private System.Windows.Forms.Button button_set_end;
        private System.Windows.Forms.Button button_vehicle;
        private System.Windows.Forms.Button button_configuration;
        private System.Windows.Forms.Button button_path;
        private System.Windows.Forms.Button driveButton;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private OpenTK.GLControl glControl1;
    }
}

