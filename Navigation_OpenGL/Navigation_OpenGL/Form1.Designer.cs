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
            this.simpleOpenGlControl1 = new Tao.Platform.Windows.SimpleOpenGlControl();
            this.timer_load = new System.Windows.Forms.Timer(this.components);
            this.picture_map = new System.Windows.Forms.PictureBox();
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
            ((System.ComponentModel.ISupportInitialize)(this.picture_map)).BeginInit();
            this.SuspendLayout();
            // 
            // simpleOpenGlControl1
            // 
            this.simpleOpenGlControl1.AccumBits = ((byte)(0));
            this.simpleOpenGlControl1.AutoCheckErrors = false;
            this.simpleOpenGlControl1.AutoFinish = false;
            this.simpleOpenGlControl1.AutoMakeCurrent = true;
            this.simpleOpenGlControl1.AutoSwapBuffers = true;
            this.simpleOpenGlControl1.BackColor = System.Drawing.Color.Black;
            this.simpleOpenGlControl1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.simpleOpenGlControl1.ColorBits = ((byte)(32));
            this.simpleOpenGlControl1.DepthBits = ((byte)(16));
            this.simpleOpenGlControl1.Location = new System.Drawing.Point(13, 13);
            this.simpleOpenGlControl1.Name = "simpleOpenGlControl1";
            this.simpleOpenGlControl1.Size = new System.Drawing.Size(799, 599);
            this.simpleOpenGlControl1.StencilBits = ((byte)(0));
            this.simpleOpenGlControl1.TabIndex = 0;
            this.simpleOpenGlControl1.Load += new System.EventHandler(this.simpleOpenGlControl1_Load);
            this.simpleOpenGlControl1.Paint += new System.Windows.Forms.PaintEventHandler(this.simpleOpenGlControl1_Paint);
            // 
            // timer_load
            // 
            this.timer_load.Interval = 1000;
            this.timer_load.Tick += new System.EventHandler(this.timer_load_Tick);
            // 
            // picture_map
            // 
            this.picture_map.Location = new System.Drawing.Point(13, 13);
            this.picture_map.Name = "picture_map";
            this.picture_map.Size = new System.Drawing.Size(800, 600);
            this.picture_map.TabIndex = 1;
            this.picture_map.TabStop = false;
            // 
            // button_load
            // 
            this.button_load.Location = new System.Drawing.Point(819, 13);
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
            this.textBox1.Location = new System.Drawing.Point(819, 281);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(128, 84);
            this.textBox1.TabIndex = 3;
            this.toolTip1.SetToolTip(this.textBox1, "Send debuging output here.");
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // text_start
            // 
            this.text_start.BackColor = System.Drawing.Color.Red;
            this.text_start.Location = new System.Drawing.Point(820, 73);
            this.text_start.Name = "text_start";
            this.text_start.Size = new System.Drawing.Size(100, 20);
            this.text_start.TabIndex = 5;
            this.toolTip1.SetToolTip(this.text_start, "Starting point (x<800, y<600)");
            this.text_start.TextChanged += new System.EventHandler(this.text_start_TextChanged);
            // 
            // text_end
            // 
            this.text_end.BackColor = System.Drawing.Color.RoyalBlue;
            this.text_end.Location = new System.Drawing.Point(820, 100);
            this.text_end.Name = "text_end";
            this.text_end.Size = new System.Drawing.Size(100, 20);
            this.text_end.TabIndex = 6;
            this.toolTip1.SetToolTip(this.text_end, "Ending point (x<800, y<600)");
            this.text_end.TextChanged += new System.EventHandler(this.text_end_TextChanged);
            // 
            // button_set_start
            // 
            this.button_set_start.Location = new System.Drawing.Point(927, 73);
            this.button_set_start.Name = "button_set_start";
            this.button_set_start.Size = new System.Drawing.Size(75, 23);
            this.button_set_start.TabIndex = 7;
            this.button_set_start.Text = "Set Start";
            this.toolTip1.SetToolTip(this.button_set_start, "Sets a new starting point (x<800, y<600)");
            this.button_set_start.UseVisualStyleBackColor = true;
            this.button_set_start.Click += new System.EventHandler(this.button_set_start_Click);
            // 
            // button_set_end
            // 
            this.button_set_end.Location = new System.Drawing.Point(927, 100);
            this.button_set_end.Name = "button_set_end";
            this.button_set_end.Size = new System.Drawing.Size(75, 23);
            this.button_set_end.TabIndex = 8;
            this.button_set_end.Text = "Set End";
            this.toolTip1.SetToolTip(this.button_set_end, "Sets a new ending point (x<800, y<600)");
            this.button_set_end.UseVisualStyleBackColor = true;
            this.button_set_end.Click += new System.EventHandler(this.button_set_end_Click);
            // 
            // button_vehicle
            // 
            this.button_vehicle.Location = new System.Drawing.Point(820, 126);
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
            this.button_configuration.Location = new System.Drawing.Point(901, 126);
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
            this.button_path.Location = new System.Drawing.Point(820, 156);
            this.button_path.Name = "button_path";
            this.button_path.Size = new System.Drawing.Size(75, 23);
            this.button_path.TabIndex = 11;
            this.button_path.Text = "Start Path";
            this.button_path.UseVisualStyleBackColor = true;
            this.button_path.Click += new System.EventHandler(this.button_path_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1011, 622);
            this.Controls.Add(this.button_path);
            this.Controls.Add(this.button_configuration);
            this.Controls.Add(this.button_vehicle);
            this.Controls.Add(this.button_set_end);
            this.Controls.Add(this.button_set_start);
            this.Controls.Add(this.text_end);
            this.Controls.Add(this.text_start);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.simpleOpenGlControl1);
            this.Controls.Add(this.picture_map);
            this.Controls.Add(this.button_load);
            this.Name = "Form1";
            this.Text = "Navigation";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.picture_map)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Tao.Platform.Windows.SimpleOpenGlControl simpleOpenGlControl1;
        private System.Windows.Forms.Timer timer_load;
        private System.Windows.Forms.PictureBox picture_map;
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
    }
}

