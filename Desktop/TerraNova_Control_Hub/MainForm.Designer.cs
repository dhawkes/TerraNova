namespace TerraNova_Control_Hub
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Controller_Status_LB = new System.Windows.Forms.Label();
            this.log_CB = new System.Windows.Forms.CheckBox();
            this.LogFileTB = new System.Windows.Forms.TextBox();
            this.DataDGV = new System.Windows.Forms.DataGridView();
            this.nameCol = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.unitCol = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.valueCol = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.FaultDGV = new System.Windows.Forms.DataGridView();
            this.faultCol = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.statusCol = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SaveBT = new System.Windows.Forms.Button();
            this.ResetBT = new System.Windows.Forms.Button();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.colorDialog2 = new System.Windows.Forms.ColorDialog();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DataDGV)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.FaultDGV)).BeginInit();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 50;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(8, 8);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(582, 412);
            this.pictureBox1.TabIndex = 17;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox1_Paint);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 19.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(72, 429);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(225, 31);
            this.label1.TabIndex = 20;
            this.label1.Text = "Controller Status:";
            // 
            // Controller_Status_LB
            // 
            this.Controller_Status_LB.AutoSize = true;
            this.Controller_Status_LB.Font = new System.Drawing.Font("Microsoft Sans Serif", 19.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Controller_Status_LB.ForeColor = System.Drawing.Color.Red;
            this.Controller_Status_LB.Location = new System.Drawing.Point(293, 429);
            this.Controller_Status_LB.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.Controller_Status_LB.Name = "Controller_Status_LB";
            this.Controller_Status_LB.Size = new System.Drawing.Size(234, 31);
            this.Controller_Status_LB.TabIndex = 21;
            this.Controller_Status_LB.Text = "DISCONNECTED";
            // 
            // log_CB
            // 
            this.log_CB.AutoSize = true;
            this.log_CB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.log_CB.Location = new System.Drawing.Point(597, 432);
            this.log_CB.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.log_CB.Name = "log_CB";
            this.log_CB.Size = new System.Drawing.Size(94, 24);
            this.log_CB.TabIndex = 22;
            this.log_CB.Text = "Log Data";
            this.log_CB.UseVisualStyleBackColor = true;
            this.log_CB.CheckedChanged += new System.EventHandler(this.log_CB_CheckedChanged);
            // 
            // LogFileTB
            // 
            this.LogFileTB.Enabled = false;
            this.LogFileTB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LogFileTB.ForeColor = System.Drawing.Color.Gray;
            this.LogFileTB.Location = new System.Drawing.Point(688, 430);
            this.LogFileTB.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.LogFileTB.Name = "LogFileTB";
            this.LogFileTB.Size = new System.Drawing.Size(290, 26);
            this.LogFileTB.TabIndex = 23;
            this.LogFileTB.Text = "Filename";
            this.LogFileTB.Click += new System.EventHandler(this.LogFileTB_Click);
            // 
            // DataDGV
            // 
            this.DataDGV.AllowUserToAddRows = false;
            this.DataDGV.AllowUserToDeleteRows = false;
            this.DataDGV.AllowUserToResizeColumns = false;
            this.DataDGV.AllowUserToResizeRows = false;
            this.DataDGV.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DataDGV.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.nameCol,
            this.unitCol,
            this.valueCol});
            this.DataDGV.Location = new System.Drawing.Point(597, 8);
            this.DataDGV.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.DataDGV.MultiSelect = false;
            this.DataDGV.Name = "DataDGV";
            this.DataDGV.ReadOnly = true;
            this.DataDGV.RowHeadersVisible = false;
            this.DataDGV.RowTemplate.Height = 33;
            this.DataDGV.Size = new System.Drawing.Size(327, 412);
            this.DataDGV.TabIndex = 24;
            this.DataDGV.SelectionChanged += new System.EventHandler(this.DataDGV_SelectionChanged);
            // 
            // nameCol
            // 
            this.nameCol.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.DisplayedCells;
            this.nameCol.HeaderText = "Name";
            this.nameCol.Name = "nameCol";
            this.nameCol.ReadOnly = true;
            this.nameCol.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.nameCol.Width = 60;
            // 
            // unitCol
            // 
            this.unitCol.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.DisplayedCells;
            this.unitCol.HeaderText = "Unit";
            this.unitCol.Name = "unitCol";
            this.unitCol.ReadOnly = true;
            this.unitCol.Width = 51;
            // 
            // valueCol
            // 
            this.valueCol.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.valueCol.HeaderText = "Value";
            this.valueCol.Name = "valueCol";
            this.valueCol.ReadOnly = true;
            this.valueCol.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            // 
            // FaultDGV
            // 
            this.FaultDGV.AllowUserToAddRows = false;
            this.FaultDGV.AllowUserToDeleteRows = false;
            this.FaultDGV.AllowUserToResizeColumns = false;
            this.FaultDGV.AllowUserToResizeRows = false;
            this.FaultDGV.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.FaultDGV.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.faultCol,
            this.statusCol});
            this.FaultDGV.Location = new System.Drawing.Point(927, 8);
            this.FaultDGV.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.FaultDGV.MultiSelect = false;
            this.FaultDGV.Name = "FaultDGV";
            this.FaultDGV.ReadOnly = true;
            this.FaultDGV.RowHeadersVisible = false;
            this.FaultDGV.RowTemplate.Height = 33;
            this.FaultDGV.Size = new System.Drawing.Size(234, 412);
            this.FaultDGV.TabIndex = 25;
            this.FaultDGV.SelectionChanged += new System.EventHandler(this.FaultDGV_SelectionChanged);
            // 
            // faultCol
            // 
            this.faultCol.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.DisplayedCells;
            this.faultCol.HeaderText = "Fault";
            this.faultCol.Name = "faultCol";
            this.faultCol.ReadOnly = true;
            this.faultCol.Width = 55;
            // 
            // statusCol
            // 
            this.statusCol.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.statusCol.HeaderText = "Status";
            this.statusCol.Name = "statusCol";
            this.statusCol.ReadOnly = true;
            // 
            // SaveBT
            // 
            this.SaveBT.Enabled = false;
            this.SaveBT.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SaveBT.Location = new System.Drawing.Point(981, 429);
            this.SaveBT.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.SaveBT.Name = "SaveBT";
            this.SaveBT.Size = new System.Drawing.Size(90, 28);
            this.SaveBT.TabIndex = 26;
            this.SaveBT.Text = "Save Log";
            this.SaveBT.UseVisualStyleBackColor = true;
            this.SaveBT.Click += new System.EventHandler(this.SaveBT_Click);
            // 
            // ResetBT
            // 
            this.ResetBT.Enabled = false;
            this.ResetBT.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ResetBT.Location = new System.Drawing.Point(1072, 429);
            this.ResetBT.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.ResetBT.Name = "ResetBT";
            this.ResetBT.Size = new System.Drawing.Size(90, 28);
            this.ResetBT.TabIndex = 27;
            this.ResetBT.Text = "Reset Log";
            this.ResetBT.UseVisualStyleBackColor = true;
            this.ResetBT.Click += new System.EventHandler(this.ResetBT_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.ClientSize = new System.Drawing.Size(1167, 463);
            this.Controls.Add(this.ResetBT);
            this.Controls.Add(this.SaveBT);
            this.Controls.Add(this.FaultDGV);
            this.Controls.Add(this.DataDGV);
            this.Controls.Add(this.LogFileTB);
            this.Controls.Add(this.log_CB);
            this.Controls.Add(this.Controller_Status_LB);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBox1);
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "MainForm";
            this.Text = "TerraNova Control Hub";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DataDGV)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.FaultDGV)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label Controller_Status_LB;
        private System.Windows.Forms.CheckBox log_CB;
        private System.Windows.Forms.TextBox LogFileTB;
        private System.Windows.Forms.DataGridView DataDGV;
        private System.Windows.Forms.DataGridView FaultDGV;
        private System.Windows.Forms.DataGridViewTextBoxColumn faultCol;
        private System.Windows.Forms.DataGridViewTextBoxColumn statusCol;
        private System.Windows.Forms.DataGridViewTextBoxColumn nameCol;
        private System.Windows.Forms.DataGridViewTextBoxColumn unitCol;
        private System.Windows.Forms.DataGridViewTextBoxColumn valueCol;
        private System.Windows.Forms.Button SaveBT;
        private System.Windows.Forms.Button ResetBT;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.ColorDialog colorDialog2;
    }
}

