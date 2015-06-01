namespace InstaFilter
{
    partial class Customize
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Customize));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.檔案FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.開啟圖檔ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.儲存圖片ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.儲存設定ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.刪除濾鏡ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.離開ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.說明HToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.關於InstaFilterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lblReslut = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.trkBarRed = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.trkBarGreen = new System.Windows.Forms.TrackBar();
            this.label3 = new System.Windows.Forms.Label();
            this.trkBarBlue = new System.Windows.Forms.TrackBar();
            this.label4 = new System.Windows.Forms.Label();
            this.trkBarValue = new System.Windows.Forms.TrackBar();
            this.label5 = new System.Windows.Forms.Label();
            this.trkBarSaturation = new System.Windows.Forms.TrackBar();
            this.label6 = new System.Windows.Forms.Label();
            this.trkBarHue = new System.Windows.Forms.TrackBar();
            this.label7 = new System.Windows.Forms.Label();
            this.trkBarContrast = new System.Windows.Forms.TrackBar();
            this.label8 = new System.Windows.Forms.Label();
            this.trkBarBrightness = new System.Windows.Forms.TrackBar();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnReset = new System.Windows.Forms.Button();
            this.lblRGB = new System.Windows.Forms.Label();
            this.lblHSV = new System.Windows.Forms.Label();
            this.lblBC = new System.Windows.Forms.Label();
            this.btnRand = new System.Windows.Forms.Button();
            this.ckcGray = new System.Windows.Forms.CheckBox();
            this.picBox = new System.Windows.Forms.PictureBox();
            this.ckcHistogram = new System.Windows.Forms.CheckBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarRed)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarGreen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarBlue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarSaturation)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarHue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarContrast)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarBrightness)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBox)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.Color.Transparent;
            this.menuStrip1.Font = new System.Drawing.Font("微軟正黑體", 9.75F);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.檔案FToolStripMenuItem,
            this.說明HToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(908, 25);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 檔案FToolStripMenuItem
            // 
            this.檔案FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.開啟圖檔ToolStripMenuItem,
            this.儲存圖片ToolStripMenuItem,
            this.儲存設定ToolStripMenuItem,
            this.刪除濾鏡ToolStripMenuItem,
            this.離開ToolStripMenuItem});
            this.檔案FToolStripMenuItem.Name = "檔案FToolStripMenuItem";
            this.檔案FToolStripMenuItem.Size = new System.Drawing.Size(53, 21);
            this.檔案FToolStripMenuItem.Text = "檔案&F";
            // 
            // 開啟圖檔ToolStripMenuItem
            // 
            this.開啟圖檔ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.Image;
            this.開啟圖檔ToolStripMenuItem.Name = "開啟圖檔ToolStripMenuItem";
            this.開啟圖檔ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.開啟圖檔ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.開啟圖檔ToolStripMenuItem.Text = "開啟圖檔";
            this.開啟圖檔ToolStripMenuItem.Click += new System.EventHandler(this.開啟圖檔ToolStripMenuItem_Click);
            // 
            // 儲存圖片ToolStripMenuItem
            // 
            this.儲存圖片ToolStripMenuItem.Enabled = false;
            this.儲存圖片ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.save_as;
            this.儲存圖片ToolStripMenuItem.Name = "儲存圖片ToolStripMenuItem";
            this.儲存圖片ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
            this.儲存圖片ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.儲存圖片ToolStripMenuItem.Text = "儲存圖片";
            this.儲存圖片ToolStripMenuItem.Click += new System.EventHandler(this.儲存圖片ToolStripMenuItem_Click);
            // 
            // 儲存設定ToolStripMenuItem
            // 
            this.儲存設定ToolStripMenuItem.Enabled = false;
            this.儲存設定ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.Save_color;
            this.儲存設定ToolStripMenuItem.Name = "儲存設定ToolStripMenuItem";
            this.儲存設定ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.儲存設定ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.儲存設定ToolStripMenuItem.Text = "儲存濾鏡設定";
            this.儲存設定ToolStripMenuItem.Click += new System.EventHandler(this.儲存濾鏡設定ToolStripMenuItem_Click);
            // 
            // 刪除濾鏡ToolStripMenuItem
            // 
            this.刪除濾鏡ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.Delete;
            this.刪除濾鏡ToolStripMenuItem.Name = "刪除濾鏡ToolStripMenuItem";
            this.刪除濾鏡ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.D)));
            this.刪除濾鏡ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.刪除濾鏡ToolStripMenuItem.Text = "刪除濾鏡";
            this.刪除濾鏡ToolStripMenuItem.Click += new System.EventHandler(this.刪除濾鏡ToolStripMenuItem_Click);
            // 
            // 離開ToolStripMenuItem
            // 
            this.離開ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.exit;
            this.離開ToolStripMenuItem.Name = "離開ToolStripMenuItem";
            this.離開ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.離開ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.離開ToolStripMenuItem.Text = "離開";
            this.離開ToolStripMenuItem.Click += new System.EventHandler(this.離開ToolStripMenuItem_Click);
            // 
            // 說明HToolStripMenuItem
            // 
            this.說明HToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.關於InstaFilterToolStripMenuItem});
            this.說明HToolStripMenuItem.Name = "說明HToolStripMenuItem";
            this.說明HToolStripMenuItem.Size = new System.Drawing.Size(56, 21);
            this.說明HToolStripMenuItem.Text = "說明&H";
            // 
            // 關於InstaFilterToolStripMenuItem
            // 
            this.關於InstaFilterToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.information;
            this.關於InstaFilterToolStripMenuItem.Name = "關於InstaFilterToolStripMenuItem";
            this.關於InstaFilterToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.H)));
            this.關於InstaFilterToolStripMenuItem.Size = new System.Drawing.Size(215, 22);
            this.關於InstaFilterToolStripMenuItem.Text = "關於 InstaFilter";
            this.關於InstaFilterToolStripMenuItem.Click += new System.EventHandler(this.關於InstaFilterToolStripMenuItem_Click);
            // 
            // lblReslut
            // 
            this.lblReslut.BackColor = System.Drawing.Color.Transparent;
            this.lblReslut.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.lblReslut.Location = new System.Drawing.Point(663, 167);
            this.lblReslut.Name = "lblReslut";
            this.lblReslut.Size = new System.Drawing.Size(67, 24);
            this.lblReslut.TabIndex = 4;
            this.lblReslut.Text = "效果圖";
            this.lblReslut.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // trkBarRed
            // 
            this.trkBarRed.Enabled = false;
            this.trkBarRed.Location = new System.Drawing.Point(120, 73);
            this.trkBarRed.Maximum = 255;
            this.trkBarRed.Minimum = -255;
            this.trkBarRed.Name = "trkBarRed";
            this.trkBarRed.Size = new System.Drawing.Size(354, 45);
            this.trkBarRed.TabIndex = 5;
            this.trkBarRed.TickFrequency = 10;
            this.trkBarRed.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trkBarRed.Scroll += new System.EventHandler(this.trkBar_Scroll);
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label1.Location = new System.Drawing.Point(47, 83);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(67, 24);
            this.label1.TabIndex = 6;
            this.label1.Text = "紅色";
            this.label1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label2
            // 
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label2.Location = new System.Drawing.Point(47, 143);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 24);
            this.label2.TabIndex = 8;
            this.label2.Text = "綠色";
            this.label2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // trkBarGreen
            // 
            this.trkBarGreen.Enabled = false;
            this.trkBarGreen.Location = new System.Drawing.Point(120, 133);
            this.trkBarGreen.Maximum = 255;
            this.trkBarGreen.Minimum = -255;
            this.trkBarGreen.Name = "trkBarGreen";
            this.trkBarGreen.Size = new System.Drawing.Size(354, 45);
            this.trkBarGreen.TabIndex = 7;
            this.trkBarGreen.TickFrequency = 10;
            this.trkBarGreen.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trkBarGreen.Scroll += new System.EventHandler(this.trkBar_Scroll);
            // 
            // label3
            // 
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label3.Location = new System.Drawing.Point(47, 203);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(67, 24);
            this.label3.TabIndex = 10;
            this.label3.Text = "藍色";
            this.label3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // trkBarBlue
            // 
            this.trkBarBlue.Enabled = false;
            this.trkBarBlue.Location = new System.Drawing.Point(120, 193);
            this.trkBarBlue.Maximum = 255;
            this.trkBarBlue.Minimum = -255;
            this.trkBarBlue.Name = "trkBarBlue";
            this.trkBarBlue.Size = new System.Drawing.Size(354, 45);
            this.trkBarBlue.TabIndex = 9;
            this.trkBarBlue.TickFrequency = 10;
            this.trkBarBlue.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trkBarBlue.Scroll += new System.EventHandler(this.trkBar_Scroll);
            // 
            // label4
            // 
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label4.Location = new System.Drawing.Point(47, 383);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(67, 24);
            this.label4.TabIndex = 16;
            this.label4.Text = "明度";
            this.label4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // trkBarValue
            // 
            this.trkBarValue.Enabled = false;
            this.trkBarValue.Location = new System.Drawing.Point(120, 373);
            this.trkBarValue.Maximum = 100;
            this.trkBarValue.Minimum = -100;
            this.trkBarValue.Name = "trkBarValue";
            this.trkBarValue.Size = new System.Drawing.Size(354, 45);
            this.trkBarValue.TabIndex = 15;
            this.trkBarValue.TickFrequency = 10;
            this.trkBarValue.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trkBarValue.Scroll += new System.EventHandler(this.trkBar_Scroll);
            // 
            // label5
            // 
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label5.Location = new System.Drawing.Point(47, 323);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(67, 24);
            this.label5.TabIndex = 14;
            this.label5.Text = "飽和度";
            this.label5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // trkBarSaturation
            // 
            this.trkBarSaturation.Enabled = false;
            this.trkBarSaturation.Location = new System.Drawing.Point(120, 313);
            this.trkBarSaturation.Maximum = 100;
            this.trkBarSaturation.Minimum = -100;
            this.trkBarSaturation.Name = "trkBarSaturation";
            this.trkBarSaturation.Size = new System.Drawing.Size(354, 45);
            this.trkBarSaturation.TabIndex = 13;
            this.trkBarSaturation.TickFrequency = 10;
            this.trkBarSaturation.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trkBarSaturation.Scroll += new System.EventHandler(this.trkBar_Scroll);
            // 
            // label6
            // 
            this.label6.BackColor = System.Drawing.Color.Transparent;
            this.label6.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label6.Location = new System.Drawing.Point(47, 263);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 24);
            this.label6.TabIndex = 12;
            this.label6.Text = "色相";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // trkBarHue
            // 
            this.trkBarHue.Enabled = false;
            this.trkBarHue.Location = new System.Drawing.Point(120, 253);
            this.trkBarHue.Maximum = 180;
            this.trkBarHue.Minimum = -180;
            this.trkBarHue.Name = "trkBarHue";
            this.trkBarHue.Size = new System.Drawing.Size(354, 45);
            this.trkBarHue.TabIndex = 11;
            this.trkBarHue.TickFrequency = 10;
            this.trkBarHue.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trkBarHue.Scroll += new System.EventHandler(this.trkBar_Scroll);
            // 
            // label7
            // 
            this.label7.BackColor = System.Drawing.Color.Transparent;
            this.label7.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label7.Location = new System.Drawing.Point(47, 503);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(67, 24);
            this.label7.TabIndex = 20;
            this.label7.Text = "對比";
            this.label7.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // trkBarContrast
            // 
            this.trkBarContrast.Enabled = false;
            this.trkBarContrast.Location = new System.Drawing.Point(120, 493);
            this.trkBarContrast.Maximum = 100;
            this.trkBarContrast.Minimum = -100;
            this.trkBarContrast.Name = "trkBarContrast";
            this.trkBarContrast.Size = new System.Drawing.Size(354, 45);
            this.trkBarContrast.TabIndex = 19;
            this.trkBarContrast.TickFrequency = 10;
            this.trkBarContrast.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trkBarContrast.Scroll += new System.EventHandler(this.trkBar_Scroll);
            // 
            // label8
            // 
            this.label8.BackColor = System.Drawing.Color.Transparent;
            this.label8.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label8.Location = new System.Drawing.Point(47, 443);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(67, 24);
            this.label8.TabIndex = 18;
            this.label8.Text = "亮度";
            this.label8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // trkBarBrightness
            // 
            this.trkBarBrightness.Enabled = false;
            this.trkBarBrightness.Location = new System.Drawing.Point(120, 433);
            this.trkBarBrightness.Maximum = 100;
            this.trkBarBrightness.Minimum = -100;
            this.trkBarBrightness.Name = "trkBarBrightness";
            this.trkBarBrightness.Size = new System.Drawing.Size(354, 45);
            this.trkBarBrightness.TabIndex = 17;
            this.trkBarBrightness.TickFrequency = 10;
            this.trkBarBrightness.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trkBarBrightness.Scroll += new System.EventHandler(this.trkBar_Scroll);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox1.Font = new System.Drawing.Font("微軟正黑體", 10F);
            this.groupBox1.Location = new System.Drawing.Point(32, 49);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(463, 504);
            this.groupBox1.TabIndex = 21;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "控制盤";
            // 
            // btnReset
            // 
            this.btnReset.Enabled = false;
            this.btnReset.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnReset.Location = new System.Drawing.Point(524, 519);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(75, 34);
            this.btnReset.TabIndex = 22;
            this.btnReset.Text = "重設";
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // lblRGB
            // 
            this.lblRGB.BackColor = System.Drawing.Color.Transparent;
            this.lblRGB.Font = new System.Drawing.Font("微軟正黑體", 14.25F);
            this.lblRGB.Location = new System.Drawing.Point(504, 414);
            this.lblRGB.Name = "lblRGB";
            this.lblRGB.Size = new System.Drawing.Size(123, 83);
            this.lblRGB.TabIndex = 23;
            this.lblRGB.Text = "紅色：0\r\n綠色：0\r\n藍色：0";
            this.lblRGB.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lblHSV
            // 
            this.lblHSV.BackColor = System.Drawing.Color.Transparent;
            this.lblHSV.Font = new System.Drawing.Font("微軟正黑體", 14.25F);
            this.lblHSV.Location = new System.Drawing.Point(638, 414);
            this.lblHSV.Name = "lblHSV";
            this.lblHSV.Size = new System.Drawing.Size(142, 83);
            this.lblHSV.TabIndex = 24;
            this.lblHSV.Text = "色相：0\r\n飽和度：0\r\n明度：0";
            this.lblHSV.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lblBC
            // 
            this.lblBC.BackColor = System.Drawing.Color.Transparent;
            this.lblBC.Font = new System.Drawing.Font("微軟正黑體", 14.25F);
            this.lblBC.Location = new System.Drawing.Point(777, 414);
            this.lblBC.Name = "lblBC";
            this.lblBC.Size = new System.Drawing.Size(123, 83);
            this.lblBC.TabIndex = 25;
            this.lblBC.Text = "亮度：0\r\n對比：0";
            this.lblBC.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // btnRand
            // 
            this.btnRand.Enabled = false;
            this.btnRand.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnRand.Location = new System.Drawing.Point(655, 519);
            this.btnRand.Name = "btnRand";
            this.btnRand.Size = new System.Drawing.Size(75, 34);
            this.btnRand.TabIndex = 26;
            this.btnRand.Text = "隨機";
            this.btnRand.UseVisualStyleBackColor = true;
            this.btnRand.Click += new System.EventHandler(this.btnRand_Click);
            // 
            // ckcGray
            // 
            this.ckcGray.AutoSize = true;
            this.ckcGray.Enabled = false;
            this.ckcGray.Font = new System.Drawing.Font("微軟正黑體", 12F);
            this.ckcGray.Location = new System.Drawing.Point(766, 503);
            this.ckcGray.Name = "ckcGray";
            this.ckcGray.Size = new System.Drawing.Size(60, 24);
            this.ckcGray.TabIndex = 27;
            this.ckcGray.Text = "灰階";
            this.ckcGray.UseVisualStyleBackColor = true;
            this.ckcGray.CheckedChanged += new System.EventHandler(this.ckcGray_CheckedChanged);
            // 
            // picBox
            // 
            this.picBox.Location = new System.Drawing.Point(566, 71);
            this.picBox.Name = "picBox";
            this.picBox.Size = new System.Drawing.Size(260, 227);
            this.picBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picBox.TabIndex = 1;
            this.picBox.TabStop = false;
            this.picBox.Click += new System.EventHandler(this.picBox_Click);
            // 
            // ckcHistogram
            // 
            this.ckcHistogram.AutoSize = true;
            this.ckcHistogram.Enabled = false;
            this.ckcHistogram.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ckcHistogram.Location = new System.Drawing.Point(766, 533);
            this.ckcHistogram.Name = "ckcHistogram";
            this.ckcHistogram.Size = new System.Drawing.Size(76, 24);
            this.ckcHistogram.TabIndex = 28;
            this.ckcHistogram.Text = "直方圖";
            this.ckcHistogram.UseVisualStyleBackColor = true;
            // 
            // Customize
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(908, 569);
            this.Controls.Add(this.ckcHistogram);
            this.Controls.Add(this.ckcGray);
            this.Controls.Add(this.btnRand);
            this.Controls.Add(this.lblBC);
            this.Controls.Add(this.lblHSV);
            this.Controls.Add(this.lblRGB);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.trkBarContrast);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.trkBarBrightness);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.trkBarValue);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.trkBarSaturation);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.trkBarHue);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.trkBarBlue);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.trkBarGreen);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.trkBarRed);
            this.Controls.Add(this.lblReslut);
            this.Controls.Add(this.picBox);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "Customize";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "使用者自訂濾鏡";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarRed)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarGreen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarBlue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarSaturation)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarHue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarContrast)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trkBarBrightness)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 檔案FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 開啟圖檔ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 儲存設定ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 離開ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 說明HToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 關於InstaFilterToolStripMenuItem;
        private System.Windows.Forms.PictureBox picBox;
        private System.Windows.Forms.Label lblReslut;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TrackBar trkBarRed;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TrackBar trkBarGreen;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TrackBar trkBarBlue;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TrackBar trkBarValue;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TrackBar trkBarSaturation;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TrackBar trkBarHue;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TrackBar trkBarContrast;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TrackBar trkBarBrightness;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Label lblRGB;
        private System.Windows.Forms.Label lblHSV;
        private System.Windows.Forms.Label lblBC;
        private System.Windows.Forms.Button btnRand;
        private System.Windows.Forms.CheckBox ckcGray;
        private System.Windows.Forms.ToolStripMenuItem 刪除濾鏡ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 儲存圖片ToolStripMenuItem;
        private System.Windows.Forms.CheckBox ckcHistogram;
    }
}