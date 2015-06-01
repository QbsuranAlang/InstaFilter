namespace InstaFilter
{
    partial class Operator
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Operator));
            this.pic2 = new System.Windows.Forms.PictureBox();
            this.pic1 = new System.Windows.Forms.PictureBox();
            this.lblImg1 = new System.Windows.Forms.Label();
            this.lblImg2 = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.檔案FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.開啟檔案1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.開啟檔案2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.從攝影機匯入1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.從攝影機匯入2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.另存新檔ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.離開ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.說明ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.關於InstaFilterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lblReslut = new System.Windows.Forms.Label();
            this.picReslut = new System.Windows.Forms.PictureBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.btnDo = new System.Windows.Forms.Button();
            this.tmrCap1 = new System.Windows.Forms.Timer(this.components);
            this.tmrCap2 = new System.Windows.Forms.Timer(this.components);
            this.ckcHistogram = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.pic2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic1)).BeginInit();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picReslut)).BeginInit();
            this.SuspendLayout();
            // 
            // pic2
            // 
            this.pic2.Location = new System.Drawing.Point(493, 54);
            this.pic2.Name = "pic2";
            this.pic2.Size = new System.Drawing.Size(243, 219);
            this.pic2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pic2.TabIndex = 1;
            this.pic2.TabStop = false;
            this.pic2.Visible = false;
            this.pic2.Click += new System.EventHandler(this.pic_Click);
            // 
            // pic1
            // 
            this.pic1.Location = new System.Drawing.Point(102, 54);
            this.pic1.Name = "pic1";
            this.pic1.Size = new System.Drawing.Size(243, 219);
            this.pic1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pic1.TabIndex = 0;
            this.pic1.TabStop = false;
            this.pic1.Visible = false;
            this.pic1.Click += new System.EventHandler(this.pic_Click);
            // 
            // lblImg1
            // 
            this.lblImg1.BackColor = System.Drawing.Color.Transparent;
            this.lblImg1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblImg1.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.lblImg1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblImg1.Location = new System.Drawing.Point(108, 151);
            this.lblImg1.Name = "lblImg1";
            this.lblImg1.Size = new System.Drawing.Size(231, 24);
            this.lblImg1.TabIndex = 3;
            this.lblImg1.Text = "圖檔1";
            this.lblImg1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblImg2
            // 
            this.lblImg2.BackColor = System.Drawing.Color.Transparent;
            this.lblImg2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblImg2.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.lblImg2.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblImg2.Location = new System.Drawing.Point(499, 151);
            this.lblImg2.Name = "lblImg2";
            this.lblImg2.Size = new System.Drawing.Size(231, 24);
            this.lblImg2.TabIndex = 4;
            this.lblImg2.Text = "圖檔2";
            this.lblImg2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.Color.Transparent;
            this.menuStrip1.Font = new System.Drawing.Font("微軟正黑體", 9.75F);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.檔案FToolStripMenuItem,
            this.說明ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(845, 25);
            this.menuStrip1.TabIndex = 5;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 檔案FToolStripMenuItem
            // 
            this.檔案FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.開啟檔案1ToolStripMenuItem,
            this.開啟檔案2ToolStripMenuItem,
            this.從攝影機匯入1ToolStripMenuItem,
            this.從攝影機匯入2ToolStripMenuItem,
            this.另存新檔ToolStripMenuItem,
            this.離開ToolStripMenuItem});
            this.檔案FToolStripMenuItem.Font = new System.Drawing.Font("微軟正黑體", 9.75F);
            this.檔案FToolStripMenuItem.Name = "檔案FToolStripMenuItem";
            this.檔案FToolStripMenuItem.Size = new System.Drawing.Size(53, 21);
            this.檔案FToolStripMenuItem.Text = "檔案&F";
            // 
            // 開啟檔案1ToolStripMenuItem
            // 
            this.開啟檔案1ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("開啟檔案1ToolStripMenuItem.Image")));
            this.開啟檔案1ToolStripMenuItem.Name = "開啟檔案1ToolStripMenuItem";
            this.開啟檔案1ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.開啟檔案1ToolStripMenuItem.Size = new System.Drawing.Size(243, 22);
            this.開啟檔案1ToolStripMenuItem.Text = "開啟圖檔1";
            this.開啟檔案1ToolStripMenuItem.Click += new System.EventHandler(this.開啟檔案1ToolStripMenuItem_Click);
            // 
            // 開啟檔案2ToolStripMenuItem
            // 
            this.開啟檔案2ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("開啟檔案2ToolStripMenuItem.Image")));
            this.開啟檔案2ToolStripMenuItem.Name = "開啟檔案2ToolStripMenuItem";
            this.開啟檔案2ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift)
                        | System.Windows.Forms.Keys.O)));
            this.開啟檔案2ToolStripMenuItem.Size = new System.Drawing.Size(243, 22);
            this.開啟檔案2ToolStripMenuItem.Text = "開啟圖檔2";
            this.開啟檔案2ToolStripMenuItem.Click += new System.EventHandler(this.開啟檔案2ToolStripMenuItem_Click);
            // 
            // 從攝影機匯入1ToolStripMenuItem
            // 
            this.從攝影機匯入1ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("從攝影機匯入1ToolStripMenuItem.Image")));
            this.從攝影機匯入1ToolStripMenuItem.Name = "從攝影機匯入1ToolStripMenuItem";
            this.從攝影機匯入1ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.I)));
            this.從攝影機匯入1ToolStripMenuItem.Size = new System.Drawing.Size(243, 22);
            this.從攝影機匯入1ToolStripMenuItem.Text = "從攝影機匯入1";
            this.從攝影機匯入1ToolStripMenuItem.Click += new System.EventHandler(this.從攝影機匯入1ToolStripMenuItem_Click);
            // 
            // 從攝影機匯入2ToolStripMenuItem
            // 
            this.從攝影機匯入2ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("從攝影機匯入2ToolStripMenuItem.Image")));
            this.從攝影機匯入2ToolStripMenuItem.Name = "從攝影機匯入2ToolStripMenuItem";
            this.從攝影機匯入2ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift)
                        | System.Windows.Forms.Keys.I)));
            this.從攝影機匯入2ToolStripMenuItem.Size = new System.Drawing.Size(243, 22);
            this.從攝影機匯入2ToolStripMenuItem.Text = "從攝影機匯入2";
            this.從攝影機匯入2ToolStripMenuItem.Click += new System.EventHandler(this.從攝影機匯入2ToolStripMenuItem_Click);
            // 
            // 另存新檔ToolStripMenuItem
            // 
            this.另存新檔ToolStripMenuItem.Enabled = false;
            this.另存新檔ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.save_as;
            this.另存新檔ToolStripMenuItem.Name = "另存新檔ToolStripMenuItem";
            this.另存新檔ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift)
                        | System.Windows.Forms.Keys.S)));
            this.另存新檔ToolStripMenuItem.Size = new System.Drawing.Size(243, 22);
            this.另存新檔ToolStripMenuItem.Text = "另存新檔";
            this.另存新檔ToolStripMenuItem.Click += new System.EventHandler(this.另存新檔ToolStripMenuItem_Click);
            // 
            // 離開ToolStripMenuItem
            // 
            this.離開ToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("離開ToolStripMenuItem.Image")));
            this.離開ToolStripMenuItem.Name = "離開ToolStripMenuItem";
            this.離開ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.離開ToolStripMenuItem.Size = new System.Drawing.Size(243, 22);
            this.離開ToolStripMenuItem.Text = "離開";
            this.離開ToolStripMenuItem.Click += new System.EventHandler(this.離開ToolStripMenuItem_Click);
            // 
            // 說明ToolStripMenuItem
            // 
            this.說明ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.關於InstaFilterToolStripMenuItem});
            this.說明ToolStripMenuItem.Name = "說明ToolStripMenuItem";
            this.說明ToolStripMenuItem.Size = new System.Drawing.Size(56, 21);
            this.說明ToolStripMenuItem.Text = "說明&H";
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
            this.lblReslut.AutoSize = true;
            this.lblReslut.BackColor = System.Drawing.Color.Transparent;
            this.lblReslut.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblReslut.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.lblReslut.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblReslut.Location = new System.Drawing.Point(391, 436);
            this.lblReslut.Name = "lblReslut";
            this.lblReslut.Size = new System.Drawing.Size(48, 24);
            this.lblReslut.TabIndex = 7;
            this.lblReslut.Text = "結果";
            this.lblReslut.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.lblReslut.Visible = false;
            // 
            // picReslut
            // 
            this.picReslut.Location = new System.Drawing.Point(294, 339);
            this.picReslut.Name = "picReslut";
            this.picReslut.Size = new System.Drawing.Size(243, 219);
            this.picReslut.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picReslut.TabIndex = 6;
            this.picReslut.TabStop = false;
            this.picReslut.Visible = false;
            this.picReslut.Click += new System.EventHandler(this.pic_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // timer2
            // 
            this.timer2.Enabled = true;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // btnDo
            // 
            this.btnDo.Enabled = false;
            this.btnDo.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnDo.Location = new System.Drawing.Point(639, 425);
            this.btnDo.Name = "btnDo";
            this.btnDo.Size = new System.Drawing.Size(91, 49);
            this.btnDo.TabIndex = 8;
            this.btnDo.Text = "運算";
            this.btnDo.UseVisualStyleBackColor = true;
            this.btnDo.Visible = false;
            this.btnDo.Click += new System.EventHandler(this.btnDo_Click);
            // 
            // tmrCap1
            // 
            this.tmrCap1.Tick += new System.EventHandler(this.tmrCap1_Tick);
            // 
            // tmrCap2
            // 
            this.tmrCap2.Tick += new System.EventHandler(this.tmrCap2_Tick);
            // 
            // ckcHistogram
            // 
            this.ckcHistogram.AutoSize = true;
            this.ckcHistogram.Enabled = false;
            this.ckcHistogram.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ckcHistogram.Location = new System.Drawing.Point(646, 492);
            this.ckcHistogram.Name = "ckcHistogram";
            this.ckcHistogram.Size = new System.Drawing.Size(76, 24);
            this.ckcHistogram.TabIndex = 22;
            this.ckcHistogram.Text = "直方圖";
            this.ckcHistogram.UseVisualStyleBackColor = true;
            // 
            // Operator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(845, 643);
            this.Controls.Add(this.ckcHistogram);
            this.Controls.Add(this.btnDo);
            this.Controls.Add(this.lblReslut);
            this.Controls.Add(this.picReslut);
            this.Controls.Add(this.lblImg2);
            this.Controls.Add(this.lblImg1);
            this.Controls.Add(this.pic2);
            this.Controls.Add(this.pic1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "Operator";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Operator";
            ((System.ComponentModel.ISupportInitialize)(this.pic2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic1)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picReslut)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pic1;
        private System.Windows.Forms.PictureBox pic2;
        private System.Windows.Forms.Label lblImg1;
        private System.Windows.Forms.Label lblImg2;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 檔案FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 開啟檔案1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 開啟檔案2ToolStripMenuItem;
        private System.Windows.Forms.Label lblReslut;
        private System.Windows.Forms.PictureBox picReslut;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.ToolStripMenuItem 離開ToolStripMenuItem;
        private System.Windows.Forms.Button btnDo;
        private System.Windows.Forms.ToolStripMenuItem 另存新檔ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 說明ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 關於InstaFilterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 從攝影機匯入1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 從攝影機匯入2ToolStripMenuItem;
        private System.Windows.Forms.Timer tmrCap1;
        private System.Windows.Forms.Timer tmrCap2;
        private System.Windows.Forms.CheckBox ckcHistogram;
    }
}