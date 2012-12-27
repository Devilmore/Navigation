namespace Navigation_OpenGL
{
    partial class Output
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
            this.button_close = new System.Windows.Forms.Button();
            this.button_skip = new System.Windows.Forms.Button();
            this.button_save_all = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // button_close
            // 
            this.button_close.Location = new System.Drawing.Point(668, 13);
            this.button_close.Name = "button_close";
            this.button_close.Size = new System.Drawing.Size(75, 23);
            this.button_close.TabIndex = 0;
            this.button_close.Text = "Close";
            this.button_close.UseVisualStyleBackColor = true;
            this.button_close.Click += new System.EventHandler(this.button_close_Click);
            // 
            // button_skip
            // 
            this.button_skip.Location = new System.Drawing.Point(668, 43);
            this.button_skip.Name = "button_skip";
            this.button_skip.Size = new System.Drawing.Size(75, 23);
            this.button_skip.TabIndex = 1;
            this.button_skip.Text = "Skip";
            this.button_skip.UseVisualStyleBackColor = true;
            this.button_skip.Click += new System.EventHandler(this.button_skip_Click);
            // 
            // button_save_all
            // 
            this.button_save_all.Location = new System.Drawing.Point(668, 73);
            this.button_save_all.Name = "button_save_all";
            this.button_save_all.Size = new System.Drawing.Size(75, 23);
            this.button_save_all.TabIndex = 2;
            this.button_save_all.Text = "Save All";
            this.button_save_all.UseVisualStyleBackColor = true;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(13, 13);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(561, 558);
            this.richTextBox1.TabIndex = 3;
            this.richTextBox1.Text = "";
            // 
            // Output
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(837, 583);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.button_save_all);
            this.Controls.Add(this.button_skip);
            this.Controls.Add(this.button_close);
            this.Name = "Output";
            this.Text = "Output";
            this.Load += new System.EventHandler(this.Output_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_close;
        private System.Windows.Forms.Button button_skip;
        private System.Windows.Forms.Button button_save_all;
        private System.Windows.Forms.RichTextBox richTextBox1;
    }
}