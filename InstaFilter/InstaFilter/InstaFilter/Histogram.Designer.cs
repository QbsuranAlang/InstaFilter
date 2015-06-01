namespace InstaFilter
{
    partial class Histogram
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Histogram));
            this.label1 = new System.Windows.Forms.Label();
            this.tkbLevel = new System.Windows.Forms.TrackBar();
            this.histogramBox = new Emgu.CV.UI.HistogramBox();
            this.tkbLower = new System.Windows.Forms.TrackBar();
            this.label2 = new System.Windows.Forms.Label();
            this.tkbUpper = new System.Windows.Forms.TrackBar();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.tkbLevel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tkbLower)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tkbUpper)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label1.Location = new System.Drawing.Point(7, 517);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(152, 24);
            this.label1.TabIndex = 7;
            this.label1.Text = "量化階層：256";
            this.label1.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // tkbLevel
            // 
            this.tkbLevel.Location = new System.Drawing.Point(149, 507);
            this.tkbLevel.Maximum = 256;
            this.tkbLevel.Minimum = 2;
            this.tkbLevel.Name = "tkbLevel";
            this.tkbLevel.Size = new System.Drawing.Size(507, 45);
            this.tkbLevel.TabIndex = 8;
            this.tkbLevel.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.tkbLevel.Value = 256;
            this.tkbLevel.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            this.tkbLevel.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Histogram_KeyUp);
            // 
            // histogramBox
            // 
            this.histogramBox.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.histogramBox.Location = new System.Drawing.Point(0, 0);
            this.histogramBox.Margin = new System.Windows.Forms.Padding(5, 5, 5, 5);
            this.histogramBox.Name = "histogramBox";
            this.histogramBox.Size = new System.Drawing.Size(668, 500);
            this.histogramBox.TabIndex = 9;
            this.histogramBox.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Histogram_KeyUp);
            // 
            // tkbLower
            // 
            this.tkbLower.Location = new System.Drawing.Point(149, 558);
            this.tkbLower.Maximum = 256;
            this.tkbLower.Name = "tkbLower";
            this.tkbLower.Size = new System.Drawing.Size(507, 45);
            this.tkbLower.TabIndex = 11;
            this.tkbLower.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.tkbLower.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            this.tkbLower.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Histogram_KeyUp);
            // 
            // label2
            // 
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label2.Location = new System.Drawing.Point(7, 568);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(152, 24);
            this.label2.TabIndex = 10;
            this.label2.Text = "下界：0";
            this.label2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // tkbUpper
            // 
            this.tkbUpper.Location = new System.Drawing.Point(149, 609);
            this.tkbUpper.Maximum = 255;
            this.tkbUpper.Minimum = 2;
            this.tkbUpper.Name = "tkbUpper";
            this.tkbUpper.Size = new System.Drawing.Size(507, 45);
            this.tkbUpper.TabIndex = 13;
            this.tkbUpper.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.tkbUpper.Value = 255;
            this.tkbUpper.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            this.tkbUpper.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Histogram_KeyUp);
            // 
            // label3
            // 
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label3.Location = new System.Drawing.Point(7, 619);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(152, 24);
            this.label3.TabIndex = 12;
            this.label3.Text = "上界：255";
            this.label3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // Histogram
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(668, 654);
            this.Controls.Add(this.tkbUpper);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tkbLower);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.histogramBox);
            this.Controls.Add(this.tkbLevel);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Histogram";
            this.Text = "Histogram";
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Histogram_KeyUp);
            ((System.ComponentModel.ISupportInitialize)(this.tkbLevel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tkbLower)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tkbUpper)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TrackBar tkbLevel;
        private Emgu.CV.UI.HistogramBox histogramBox;
        private System.Windows.Forms.TrackBar tkbLower;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TrackBar tkbUpper;
        private System.Windows.Forms.Label label3;
    }
}