namespace Navigation_OpenGL
{
    partial class Form2
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
            this.text_axle0 = new System.Windows.Forms.TextBox();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.button_add_axle = new System.Windows.Forms.Button();
            this.button_add_box = new System.Windows.Forms.Button();
            this.button_reset = new System.Windows.Forms.Button();
            this.button_save_vehicle = new System.Windows.Forms.Button();
            this.button_load_vehicle = new System.Windows.Forms.Button();
            this.text_explanation = new System.Windows.Forms.TextBox();
            this.simpleOpenGlControl2 = new Tao.Platform.Windows.SimpleOpenGlControl();
            this.timer_invalidate = new System.Windows.Forms.Timer(this.components);
            this.open_vehicle = new System.Windows.Forms.OpenFileDialog();
            this.save_vehicle = new System.Windows.Forms.SaveFileDialog();
            this.SuspendLayout();
            // 
            // text_axle0
            // 
            this.text_axle0.Location = new System.Drawing.Point(110, 90);
            this.text_axle0.Multiline = true;
            this.text_axle0.Name = "text_axle0";
            this.text_axle0.ReadOnly = true;
            this.text_axle0.Size = new System.Drawing.Size(40, 40);
            this.text_axle0.TabIndex = 0;
            this.toolTip1.SetToolTip(this.text_axle0, "First axle can only be defined in the default constructor");
            // 
            // button_add_axle
            // 
            this.button_add_axle.Location = new System.Drawing.Point(93, 136);
            this.button_add_axle.Name = "button_add_axle";
            this.button_add_axle.Size = new System.Drawing.Size(75, 23);
            this.button_add_axle.TabIndex = 2;
            this.button_add_axle.Text = "Add Axle";
            this.toolTip1.SetToolTip(this.button_add_axle, "Adds the latest box to the vehicle");
            this.button_add_axle.UseVisualStyleBackColor = true;
            this.button_add_axle.Click += new System.EventHandler(this.button_add_axle_Click);
            // 
            // button_add_box
            // 
            this.button_add_box.Location = new System.Drawing.Point(12, 136);
            this.button_add_box.Name = "button_add_box";
            this.button_add_box.Size = new System.Drawing.Size(75, 23);
            this.button_add_box.TabIndex = 8;
            this.button_add_box.Text = "Add Box";
            this.toolTip1.SetToolTip(this.button_add_box, "Adds an additional box for the next axle");
            this.button_add_box.UseVisualStyleBackColor = true;
            this.button_add_box.Click += new System.EventHandler(this.button_add_box_Click);
            // 
            // button_reset
            // 
            this.button_reset.Location = new System.Drawing.Point(336, 136);
            this.button_reset.Name = "button_reset";
            this.button_reset.Size = new System.Drawing.Size(75, 23);
            this.button_reset.TabIndex = 9;
            this.button_reset.Text = "Reset";
            this.toolTip1.SetToolTip(this.button_reset, "Resets the vehicle to the default one");
            this.button_reset.UseVisualStyleBackColor = true;
            this.button_reset.Click += new System.EventHandler(this.button_reset_Click);
            // 
            // button_save_vehicle
            // 
            this.button_save_vehicle.Location = new System.Drawing.Point(174, 136);
            this.button_save_vehicle.Name = "button_save_vehicle";
            this.button_save_vehicle.Size = new System.Drawing.Size(75, 23);
            this.button_save_vehicle.TabIndex = 10;
            this.button_save_vehicle.Text = "Save";
            this.toolTip1.SetToolTip(this.button_save_vehicle, "Saves the current starting configuration");
            this.button_save_vehicle.UseVisualStyleBackColor = true;
            this.button_save_vehicle.Click += new System.EventHandler(this.button_save_vehicle_Click);
            // 
            // button_load_vehicle
            // 
            this.button_load_vehicle.Location = new System.Drawing.Point(255, 136);
            this.button_load_vehicle.Name = "button_load_vehicle";
            this.button_load_vehicle.Size = new System.Drawing.Size(75, 23);
            this.button_load_vehicle.TabIndex = 11;
            this.button_load_vehicle.Text = "Load";
            this.toolTip1.SetToolTip(this.button_load_vehicle, "Loads a starting configuration");
            this.button_load_vehicle.UseVisualStyleBackColor = true;
            this.button_load_vehicle.Click += new System.EventHandler(this.button_load_vehicle_Click);
            // 
            // text_explanation
            // 
            this.text_explanation.Location = new System.Drawing.Point(4, 90);
            this.text_explanation.Multiline = true;
            this.text_explanation.Name = "text_explanation";
            this.text_explanation.ReadOnly = true;
            this.text_explanation.Size = new System.Drawing.Size(100, 40);
            this.text_explanation.TabIndex = 1;
            // 
            // simpleOpenGlControl2
            // 
            this.simpleOpenGlControl2.AccumBits = ((byte)(0));
            this.simpleOpenGlControl2.AutoCheckErrors = false;
            this.simpleOpenGlControl2.AutoFinish = false;
            this.simpleOpenGlControl2.AutoMakeCurrent = true;
            this.simpleOpenGlControl2.AutoSwapBuffers = true;
            this.simpleOpenGlControl2.BackColor = System.Drawing.Color.Black;
            this.simpleOpenGlControl2.ColorBits = ((byte)(32));
            this.simpleOpenGlControl2.DepthBits = ((byte)(16));
            this.simpleOpenGlControl2.Location = new System.Drawing.Point(12, 165);
            this.simpleOpenGlControl2.Name = "simpleOpenGlControl2";
            this.simpleOpenGlControl2.Size = new System.Drawing.Size(760, 85);
            this.simpleOpenGlControl2.StencilBits = ((byte)(0));
            this.simpleOpenGlControl2.TabIndex = 7;
            this.simpleOpenGlControl2.Load += new System.EventHandler(this.simpleOpenGlControl2_Load);
            this.simpleOpenGlControl2.Paint += new System.Windows.Forms.PaintEventHandler(this.simpleOpenGlControl2_Paint);
            // 
            // timer_invalidate
            // 
            this.timer_invalidate.Tick += new System.EventHandler(this.timer_invalidate_Tick);
            // 
            // open_vehicle
            // 
            this.open_vehicle.DefaultExt = "txt";
            this.open_vehicle.FileName = "vehicle";
            this.open_vehicle.InitialDirectory = "C:";
            this.open_vehicle.Title = "Open Vehicle";
            this.open_vehicle.FileOk += new System.ComponentModel.CancelEventHandler(this.open_vehicle_FileOk);
            // 
            // save_vehicle
            // 
            this.save_vehicle.DefaultExt = "txt";
            this.save_vehicle.FileName = "vehicle";
            this.save_vehicle.InitialDirectory = "C:";
            this.save_vehicle.Title = "Save Vehicle";
            this.save_vehicle.FileOk += new System.ComponentModel.CancelEventHandler(this.save_vehicle_FileOk);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 262);
            this.Controls.Add(this.button_load_vehicle);
            this.Controls.Add(this.button_save_vehicle);
            this.Controls.Add(this.button_reset);
            this.Controls.Add(this.button_add_box);
            this.Controls.Add(this.simpleOpenGlControl2);
            this.Controls.Add(this.button_add_axle);
            this.Controls.Add(this.text_explanation);
            this.Controls.Add(this.text_axle0);
            this.Name = "Form2";
            this.Text = "Vehicle Editor";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox text_axle0;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.TextBox text_explanation;
        private System.Windows.Forms.Button button_add_axle;
        private Tao.Platform.Windows.SimpleOpenGlControl simpleOpenGlControl2;
        private System.Windows.Forms.Button button_add_box;
        private System.Windows.Forms.Button button_reset;
        private System.Windows.Forms.Timer timer_invalidate;
        private System.Windows.Forms.OpenFileDialog open_vehicle;
        private System.Windows.Forms.SaveFileDialog save_vehicle;
        private System.Windows.Forms.Button button_save_vehicle;
        private System.Windows.Forms.Button button_load_vehicle;
    }
}