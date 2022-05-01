using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace winformsPlayground
{
    public partial class Form1 : Form
    {
        private Form2 _form2 = null;
        private DateTime _form2HideAt;

        private Timer _timer = new Timer();

        public Form1()
        {
            InitializeComponent();
            _timer.Tick += _timer_Tick;
            _timer.Interval = 200;
        }

        private void _timer_Tick(object sender, EventArgs e)
        {
            if (DateTime.Now > _form2HideAt)
            {
                _form2?.Close();
                _timer.Stop();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            _form2?.Close();

            _form2HideAt = DateTime.Now.AddSeconds(5);
            _timer.Start();

            _form2 = new Form2();
            _form2.Show();
        }
    }
}
