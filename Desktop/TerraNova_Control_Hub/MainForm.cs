using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;

namespace TerraNova_Control_Hub
{
    public partial class MainForm : Form
    {
        // Control variables
        Gamepad joystick;
        string serial_port = "COM5";

        // GUI variables
        Image init_img;
        Point left_stick = new Point(113, 93);
        Point right_stick = new Point(335, 187);
        Size stick_size = new Size(62, 62);
        Pen pen;
        Brush brush1, brush2, brush3, brush4;

        // Data variables
        Dictionary<int, DataGridViewRow> data_rows;
        Dictionary<int, DataGridViewRow> fault_rows;

        List<(long time, int id, float val)> data_log;
        List<(long time, int id, bool val)> fault_log;

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;

            g.DrawImage(init_img, new Point(0, 0));

            float lx = (stick_size.Width / 2.0f) - 4f + (stick_size.Width / 2.0f) * ((float)joystick.Thumbsticks.Left.X);
            float ly = (stick_size.Height / 2.0f) - 4f + (stick_size.Height / 2.0f) * (-(float)joystick.Thumbsticks.Left.Y);
            float rx = (stick_size.Width / 2.0f) - 4f + (stick_size.Width / 2.0f) * ((float)joystick.Thumbsticks.Right.X);
            float ry = (stick_size.Height / 2.0f) - 4f + (stick_size.Height / 2.0f) * (-(float)joystick.Thumbsticks.Right.Y);

            g.FillEllipse(brush3, new Rectangle(left_stick, stick_size));
            g.FillEllipse(brush1, lx + left_stick.X, ly + left_stick.Y, 8.0f, 8.0f);
            g.FillEllipse(brush3, new Rectangle(right_stick, stick_size));
            g.FillEllipse(brush2, rx + right_stick.X, ry + right_stick.Y, 8.0f, 8.0f);

            if (joystick.A)
            {
                g.FillEllipse(brush4, 419, 145, 40, 42);
            }
            if (joystick.Y)
            {
                g.FillEllipse(brush4, 419, 62, 40, 42);
            }
            if (joystick.B)
            {
                g.FillEllipse(brush4, 460, 103, 40, 42);
            }
            if (joystick.X)
            {
                g.FillEllipse(brush4, 379, 103, 40, 42);
            }
        }

        private void DataDGV_SelectionChanged(object sender, EventArgs e)
        {
            DataDGV.ClearSelection();
        }

        private void FaultDGV_SelectionChanged(object sender, EventArgs e)
        {
            FaultDGV.ClearSelection();
        }

        private void log_CB_CheckedChanged(object sender, EventArgs e)
        {
            SaveBT.Enabled = log_CB.Checked;
            ResetBT.Enabled = log_CB.Checked;
            LogFileTB.Enabled = log_CB.Checked;

            if(!log_CB.Checked)
            {
                data_log.Clear();
                fault_log.Clear();
                LogFileTB.Text = "Filename";
                LogFileTB.ForeColor = Color.Gray;
            }
        }

        private void ResetBT_Click(object sender, EventArgs e)
        {
            data_log.Clear();
            fault_log.Clear();
        }

        private void SaveBT_Click(object sender, EventArgs e)
        {
            StringBuilder sb = new StringBuilder(@"data\");
            sb.Append(DateTime.Now.ToShortDateString().Replace('/', '-'));
            sb.Append('_');
            sb.Append(DateTime.Now.ToLongTimeString().Replace(':', '-').Replace(' ', '_'));
            if(LogFileTB.Text != "Filename" && LogFileTB.Text != "")
            {
                sb.Append('_');
                sb.Append(LogFileTB.Text);
            }
            sb.Append(".nova");

            string fname = sb.ToString();

            StreamWriter sw = new StreamWriter(fname);

            // Write header
            foreach(KeyValuePair<int, DataGridViewRow> entry in data_rows)
            {
                sb = new StringBuilder("DATADEF,");
                sb.Append(entry.Key);
                sb.Append(',');
                sb.Append(entry.Value.Cells[0].Value.ToString().Replace(" ", ""));
                sb.Append(',');
                sb.Append(entry.Value.Cells[1].Value.ToString());
                sw.WriteLine(sb.ToString());
            }
            foreach(KeyValuePair<int, DataGridViewRow> entry in fault_rows)
            {
                sb = new StringBuilder("FAULTDEF,");
                sb.Append(entry.Key);
                sb.Append(',');
                sb.Append(entry.Value.Cells[0].Value.ToString());
                sw.WriteLine(sb.ToString());
            }

            // Write data
            foreach(var val in data_log)
            {
                sb = new StringBuilder("DATA,");
                sb.Append(val.time.ToString());
                sb.Append(',');
                sb.Append(val.id.ToString());
                sb.Append(',');
                sb.Append(val.val.ToString());
                sw.WriteLine(sb.ToString());
            }
            foreach(var val in fault_log)
            {
                sb = new StringBuilder("FAULT,");
                sb.Append(val.time.ToString());
                sb.Append(',');
                sb.Append(val.id.ToString());
                sb.Append(',');
                sb.Append(val.val.ToString());
                sw.WriteLine(sb.ToString());
            }

            sw.Close();

            data_log.Clear();
            fault_log.Clear();
        }

        private void LogFileTB_Click(object sender, EventArgs e)
        {
            if(LogFileTB.Text == "Filename")
            {
                LogFileTB.Text = "";
                LogFileTB.ForeColor = Color.Black;
            }
        }

        public MainForm()
        {
            // Initialize graphic components
            InitializeComponent();
            pictureBox1.Image = new Bitmap(pictureBox1.Image, pictureBox1.Size);
            init_img = pictureBox1.Image;

            pen = new Pen(Color.Black);
            brush1 = new SolidBrush(Color.Blue);
            brush2 = new SolidBrush(Color.Red);
            brush3 = new SolidBrush(Color.White);
            brush4 = new SolidBrush(Color.FromArgb(100, Color.Black));

            data_rows = new Dictionary<int, DataGridViewRow>();
            fault_rows = new Dictionary<int, DataGridViewRow>();
            data_log = new List<(long time, int id, float val)>();
            fault_log = new List<(long time, int id, bool val)>();

            LoadConfig();

            // Initialize components
            joystick = new Gamepad(1);                  // Connect to the xbox controller
            /*serial = new SerialPort("COM5", 115200);    // Connect to the Laptop ESP via serial port COM5
            serial.Open();*/
        }

        // This is run every 50ms
        private void timer1_Tick(object sender, EventArgs e)
        {
            // Update the joystick state, if connected
            try
            {
                joystick.LoadState();
                pictureBox1.Refresh();
                Controller_Status_LB.Text = "CONNECTED";
                Controller_Status_LB.ForeColor = Color.Green;
            }
            catch
            {
                Controller_Status_LB.Text = "DISCONNECTED";
                Controller_Status_LB.ForeColor = Color.Red;
                return;
            }
        }

        private void LoadConfig()
        {
            // Load data definitions
            StreamReader sr = new StreamReader("config/data_definition.csv");
            while(!sr.EndOfStream)
            {
                string[] pieces = sr.ReadLine().Split(',');
                string name = Regex.Replace(pieces[1], "(\\B[A-Z])", " $1");
                string[] row = new string[] { name, pieces[2], "0.0000" };
                DataDGV.Rows.Add(row);
                data_rows.Add(int.Parse(pieces[0]), DataDGV.Rows[DataDGV.RowCount - 1]);
            }
            sr.Close();

            sr = new StreamReader("config/fault_definition.csv");
            while(!sr.EndOfStream)
            {
                string[] pieces = sr.ReadLine().Split(',');
                string name = Regex.Replace(pieces[1], "(\\B[A-Z])", " $1");
                string[] row = new string[] { name, "GOOD" };
                FaultDGV.Rows.Add(row);
                fault_rows.Add(int.Parse(pieces[0]), FaultDGV.Rows[FaultDGV.RowCount - 1]);
                FaultDGV.Rows[FaultDGV.RowCount - 1].Cells[1].Style.BackColor = Color.LightGreen;
            }
            sr.Close();
        }
    }
}
