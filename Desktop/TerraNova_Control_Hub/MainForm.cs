using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;
using System.IO.Ports;
using System.Diagnostics;

namespace TerraNova_Control_Hub
{
    public partial class MainForm : Form
    {
        // Control variables
        Gamepad joystick;
        string serial_port = "COM10";
        SerialPort serial;
        Stopwatch stopwatch;

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
        byte[] leftovers;

        List<(long time, int id, float val)> data_log;
        List<(long time, int id, bool val)> fault_log;

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            leftovers = new byte[0];
            stopwatch = new Stopwatch();

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
            else
            {
                stopwatch.Start();
            }
        }

        private void ResetBT_Click(object sender, EventArgs e)
        {
            string msg = "Are you sure that you would like to reset the gathered logs? Gathered data will be permanately deleted.";
            string caption = "Reset Logs?";
            MessageBoxButtons mbb = MessageBoxButtons.YesNo;
            DialogResult dr;

            dr = MessageBox.Show(msg, caption, mbb);

            if (dr == DialogResult.Yes)
            {
                data_log.Clear();
                fault_log.Clear();
                stopwatch.Restart();
            }
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
            serial = new SerialPort("COM10", 115200);    // Connect to the xbee
            serial.ReadBufferSize = 400;
            serial.Open();
            serial.ReadTimeout = 5;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            byte[] buff = new byte[800];
            for(int c = 0; c < leftovers.Length; c++)
            {
                buff[c] = leftovers[c];
            }
            long time = stopwatch.ElapsedMilliseconds;

            int len = 0;
            try
            {
                len = serial.Read(buff, leftovers.Length, 400);
            }
            catch(Exception ex)
            {
                return;
            }
            len += leftovers.Length;

            int i = 0;
            while(i < len - 1)
            {
                if(buff[i] == 0xFC && ((i > 0 && buff[i-1] != 0xFA) || i == 0))
                {
                    List<byte> frame = new List<byte>();
                    int start = i;
                    i++;
                    while(buff[i] != 0xFD || buff[i-1] == 0xFA)
                    {
                        frame.Add(buff[i]);
                        i++;
                        if(i == len)
                        {
                            leftovers = new byte[i - start];
                            for(int j = start; j < i; j++)
                            {
                                leftovers[j - start] = buff[j];
                            }
                            break;
                        }
                    }

                    if (i == len)
                        break;

                    processFrame(frame.ToArray(), time);
                }
                i++;

                
            }
        }

        private void processFrame(byte[] frame, long time)
        {
            if (frame.Length < 5)
                return;
            int des_len = 0;
            if (frame[0] == 0xFF)
                des_len = 5;
            else if (frame[0] == 0xDD)
                des_len = 8;
            else
                return;

            byte[] parsed_frame = new byte[des_len];
            int k = 0;
            for(int i = 0; i < des_len; i++)
            {
                if(frame[k] == 0xFA)
                {
                    if(k + 1 < frame.Length && frame[k + 1] == 0xFA)
                    {
                        parsed_frame[i] = 0xFA;
                        k += 2;
                    }
                    else
                    {
                        k++;
                        i--;
                    }
                }
                else
                {
                    parsed_frame[i] = frame[k];
                    k++;
                }
            }

            if (k != frame.Length)
                return;

            byte[] no_check = new byte[des_len - 2];
            for (int j = 0; j < des_len - 2; j++)
            {
                no_check[j] = parsed_frame[j];
            }

            byte[] check = Fletcher16(no_check);

            if (check[1] != parsed_frame[des_len - 2] || check[0] != parsed_frame[des_len - 1])
                return;

            if(no_check[0] == 0xDD && no_check[1] < data_rows.Count)
            {
                float val = BitConverter.ToSingle(no_check, 2);
                data_rows[no_check[1]].Cells[2].Value = val.ToString();
                data_log.Add((time, no_check[1], val));
            }
            else if(no_check[0] == 0xFF)
            {
                byte f = no_check[1];
                int j = 0;
                for(int i = 0; i < fault_rows.Count; i++)
                {
                    if(j == 8)
                    {
                        j = 0;
                        f = no_check[2];
                    }

                    bool val = (f & (1 << j)) > 0;
                    fault_rows[i].Cells[1].Value = val ? "FAULT" : "GOOD";
                    fault_rows[i].Cells[1].Style.BackColor = val ? Color.Red : Color.LightGreen;
                    fault_log.Add((time, i, val));
                    j++;
                }
            }
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
                //return;
            }

            // Sync, Driving, Steering, Buttons (A B X Y LT RT LB RB), DPAD (Up Down Left Right), Checksum, Checksum
            byte[] message = new byte[4];
            
            message[0] = (byte)(100.0f * joystick.Thumbsticks.Left.Y + 100);
            message[1] = (byte)(100.0f * joystick.Thumbsticks.Right.X + 100);
            if (joystick.A)
                message[2] |= 1 << 0;
            if (joystick.B)
                message[2] |= 1 << 1;
            if (joystick.X)
                message[2] |= 1 << 2;
            if (joystick.Y)
                message[2] |= 1 << 3;
            if (joystick.LeftTrigger > 0.4)
                message[2] |= 1 << 4;
            if (joystick.RightTrigger > 0.4)
                message[2] |= 1 << 5;

            if (joystick.DPad.Up)
                message[3] |= 1 << 0;
            if (joystick.DPad.Down)
                message[3] |= 1 << 1;
            if (joystick.DPad.Left)
                message[3] |= 1 << 2;
            if (joystick.DPad.Right)
                message[3] |= 1 << 3;
            if (joystick.LeftBumper)
                message[3] |= 1 << 4;
            if (joystick.RightBumper)
                message[3] |= 1 << 5;

            byte[] checksum = Fletcher16(message);

            List<byte> buff = new List<byte>();
            buff.Add(0xFC);
            for (int i = 0; i < 6; i++)
            {
                byte b = 0;
                if (i < 4)
                    b = message[i];
                else
                    b = checksum[i - 4];

                //if (b == 0xFA || b == 0xFC || b == 0xFD)
                    //buff.Add(0xFA);
                buff.Add(b);
            }
            buff.Add(0xFD);
            serial.Write(buff.ToArray(), 0, buff.Count);
            
        }

        private void LoadConfig()
        {
            // Load data definitions
            StreamReader sr = new StreamReader("config/data_definition.csv");

            string path = @"C:\Users\Dylan Hawkes\Documents\GIT\Senior-Design\Embedded\terranova_sketch\Constants.hpp";
            StreamWriter sw = new StreamWriter(path);
            sw.WriteLine("#pragma once");
            sw.WriteLine();
            sw.WriteLine("// This file contains generated constant values used for data collection");
            sw.WriteLine();

            int max_d = -1;
            StringBuilder sb = new StringBuilder();

            while (!sr.EndOfStream)
            {
                string[] pieces = sr.ReadLine().Split(',');
                string name = Regex.Replace(pieces[1], "(\\B[A-Z])", " $1");
                string uppername = Regex.Replace(pieces[1], "(?<=.)([A-Z])", "_$0").ToUpper();
                string[] row = new string[] { name, pieces[2], "0.0000" };
                int id = int.Parse(pieces[0]);
                DataDGV.Rows.Add(row);
                data_rows.Add(id, DataDGV.Rows[DataDGV.RowCount - 1]);

                sb.Clear();
                sb.Append("#define D_");
                sb.Append(uppername);
                sb.Append(' ');
                sb.Append(pieces[0]);
                sw.WriteLine(sb.ToString());

                max_d = max_d < id ? id : max_d;
            }
            sr.Close();

            max_d++;
            sb.Clear();
            sb.Append("#define MAX_DATA_LENGTH ");
            sb.Append(max_d);
            sw.WriteLine(sb.ToString());
            sw.WriteLine();

            sr = new StreamReader("config/fault_definition.csv");
            int max_f = -1;

            while(!sr.EndOfStream)
            {
                string[] pieces = sr.ReadLine().Split(',');
                string name = Regex.Replace(pieces[1], "(\\B[A-Z])", " $1");
                string uppername = Regex.Replace(pieces[1], "(?<=.)([A-Z])", "_$0").ToUpper();
                string[] row = new string[] { name, "GOOD" };
                int id = int.Parse(pieces[0]);
                FaultDGV.Rows.Add(row);
                fault_rows.Add(id, FaultDGV.Rows[FaultDGV.RowCount - 1]);
                FaultDGV.Rows[FaultDGV.RowCount - 1].Cells[1].Style.BackColor = Color.LightGreen;

                sb.Clear();
                sb.Append("#define F_");
                sb.Append(uppername);
                sb.Append(' ');
                sb.Append(pieces[0]);
                sw.WriteLine(sb.ToString());

                max_f = max_f < id ? id : max_f;
            }
            sr.Close();

            max_f++;
            sb.Clear();
            sb.Append("#define MAX_FAULT_LENGTH ");
            sb.Append(max_f);
            sw.WriteLine(sb.ToString());
            sw.Close();
        }

        private byte[] Fletcher16(byte[] data)
        {
            UInt16 sum1 = 0xff, sum2 = 0xff;
            int len = data.Length;
            while (len > 0)
            {
                int tlen = len > 20 ? 20 : len;
                len -= tlen;
                int i = 0;
                do
                {
                    sum2 += sum1 += data[i];
                    i++;
                } while (--tlen > 0);
                sum1 = (UInt16)((UInt16)(sum1 & 0xff) + (UInt16)(sum1 >> 8));
                sum2 = (UInt16)((UInt16)(sum2 & 0xff) + (UInt16)(sum2 >> 8));
            }

            sum1 = (UInt16)((UInt16)(sum1 & 0xff) + (UInt16)(sum1 >> 8));
            sum2 = (UInt16)((UInt16)(sum2 & 0xff) + (UInt16)(sum2 >> 8));

            byte[] output = new byte[2];
            output[0] = (byte)sum1;
            output[1] = (byte)sum2;

            return output;
        }
    }
}
