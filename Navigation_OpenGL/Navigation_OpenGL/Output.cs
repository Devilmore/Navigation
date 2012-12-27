using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Navigation_OpenGL
{
    public partial class Output : Form
    {
        string m_output;

        public Output()
        {
            InitializeComponent();
        }

        public Output(string s)
        {
            InitializeComponent();
            m_output = s;
            this.richTextBox1.Text = s;
        }

        private void Output_Load(object sender, EventArgs e)
        {

        }

        private void button_close_Click(object sender, EventArgs e)
        {
            Variables.paused = false;
            this.Close();
        }

        private void button_skip_Click(object sender, EventArgs e)
        {
            Variables.paused = false;
            Variables.popDebugging = false;
            this.Close();
        }
    }
}
