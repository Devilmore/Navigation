namespace Navigation_OpenGL
{
    partial class Form3
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
            this.trackBar0 = new System.Windows.Forms.TrackBar();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.counter_axle = new System.Windows.Forms.NumericUpDown();
            this.button_save_config = new System.Windows.Forms.Button();
            this.button_load_config = new System.Windows.Forms.Button();
            this.button_reset_config = new System.Windows.Forms.Button();
            this.open_config = new System.Windows.Forms.OpenFileDialog();
            this.save_config = new System.Windows.Forms.SaveFileDialog();
            this.simpleOpenGlControl3 = new Tao.Platform.Windows.SimpleOpenGlControl();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar0)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.counter_axle)).BeginInit();
            this.SuspendLayout();
            // 
            // trackBar0
            // 
            this.trackBar0.Location = new System.Drawing.Point(13, 13);
            this.trackBar0.Maximum = 360;
            this.trackBar0.Name = "trackBar0";
            this.trackBar0.Size = new System.Drawing.Size(273, 45);
            this.trackBar0.TabIndex = 2;
            this.trackBar0.Value = 1;
            this.trackBar0.ValueChanged += new System.EventHandler(this.trackBar0_ValueChanged);
            // 
            // timer1
            // 
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // toolTip1
            // 
            this.toolTip1.Popup += new System.Windows.Forms.PopupEventHandler(this.toolTip1_Popup);
            // 
            // counter_axle
            // 
            this.counter_axle.Location = new System.Drawing.Point(293, 13);
            this.counter_axle.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.counter_axle.Name = "counter_axle";
            this.counter_axle.Size = new System.Drawing.Size(38, 20);
            this.counter_axle.TabIndex = 3;
            this.toolTip1.SetToolTip(this.counter_axle, "Current axle.");
            this.counter_axle.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.counter_axle.ValueChanged += new System.EventHandler(this.counter_axle_ValueChanged);
            // 
            // button_save_config
            // 
            this.button_save_config.Location = new System.Drawing.Point(338, 9);
            this.button_save_config.Name = "button_save_config";
            this.button_save_config.Size = new System.Drawing.Size(75, 23);
            this.button_save_config.TabIndex = 4;
            this.button_save_config.Text = "Save";
            this.toolTip1.SetToolTip(this.button_save_config, "Saves the current configuration.");
            this.button_save_config.UseVisualStyleBackColor = true;
            this.button_save_config.Click += new System.EventHandler(this.button_save_config_Click);
            // 
            // button_load_config
            // 
            this.button_load_config.Location = new System.Drawing.Point(420, 9);
            this.button_load_config.Name = "button_load_config";
            this.button_load_config.Size = new System.Drawing.Size(75, 23);
            this.button_load_config.TabIndex = 5;
            this.button_load_config.Text = "Load";
            this.toolTip1.SetToolTip(this.button_load_config, "Loads a configuration. Must fit current vehicle.");
            this.button_load_config.UseVisualStyleBackColor = true;
            this.button_load_config.Click += new System.EventHandler(this.button_load_config_Click);
            // 
            // button_reset_config
            // 
            this.button_reset_config.Location = new System.Drawing.Point(502, 9);
            this.button_reset_config.Name = "button_reset_config";
            this.button_reset_config.Size = new System.Drawing.Size(75, 23);
            this.button_reset_config.TabIndex = 6;
            this.button_reset_config.Text = "Reset";
            this.toolTip1.SetToolTip(this.button_reset_config, "Resets to default (random) configuration.");
            this.button_reset_config.UseVisualStyleBackColor = true;
            this.button_reset_config.Click += new System.EventHandler(this.button_reset_config_Click);
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
            // simpleOpenGlControl3
            // 
            this.simpleOpenGlControl3.AccumBits = ((byte)(0));
            this.simpleOpenGlControl3.AutoCheckErrors = false;
            this.simpleOpenGlControl3.AutoFinish = false;
            this.simpleOpenGlControl3.AutoMakeCurrent = true;
            this.simpleOpenGlControl3.AutoSwapBuffers = true;
            this.simpleOpenGlControl3.BackColor = System.Drawing.Color.Black;
            this.simpleOpenGlControl3.ColorBits = ((byte)(32));
            this.simpleOpenGlControl3.DepthBits = ((byte)(16));
            this.simpleOpenGlControl3.Location = new System.Drawing.Point(33, 53);
            this.simpleOpenGlControl3.Name = "simpleOpenGlControl3";
            this.simpleOpenGlControl3.Size = new System.Drawing.Size(676, 375);
            this.simpleOpenGlControl3.StencilBits = ((byte)(0));
            this.simpleOpenGlControl3.TabIndex = 7;
            // 
            // Form3
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 475);
            this.Controls.Add(this.simpleOpenGlControl3);
            this.Controls.Add(this.button_reset_config);
            this.Controls.Add(this.button_load_config);
            this.Controls.Add(this.button_save_config);
            this.Controls.Add(this.counter_axle);
            this.Controls.Add(this.trackBar0);
            this.Name = "Form3";
            this.Text = "Form3";
            this.Load += new System.EventHandler(this.Form3_Load);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar0)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.counter_axle)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TrackBar trackBar0;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.NumericUpDown counter_axle;
        private System.Windows.Forms.Button button_save_config;
        private System.Windows.Forms.Button button_load_config;
        private System.Windows.Forms.Button button_reset_config;
        private System.Windows.Forms.OpenFileDialog open_config;
        private System.Windows.Forms.SaveFileDialog save_config;
        private Tao.Platform.Windows.SimpleOpenGlControl simpleOpenGlControl3;
    }
}