namespace InstaFilter
{
    partial class Customize_Save
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Customize_Save));
            this.ckcGray = new System.Windows.Forms.CheckBox();
            this.txtFilter = new System.Windows.Forms.TextBox();
            this.btnSave = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.lblBC = new System.Windows.Forms.Label();
            this.lblHSV = new System.Windows.Forms.Label();
            this.lblRGB = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // ckcGray
            // 
            this.ckcGray.AutoSize = true;
            this.ckcGray.Enabled = false;
            this.ckcGray.Font = new System.Drawing.Font("微軟正黑體", 12F);
            this.ckcGray.Location = new System.Drawing.Point(378, 138);
            this.ckcGray.Name = "ckcGray";
            this.ckcGray.Size = new System.Drawing.Size(60, 24);
            this.ckcGray.TabIndex = 29;
            this.ckcGray.Text = "灰階";
            this.ckcGray.UseVisualStyleBackColor = true;
            // 
            // txtFilter
            // 
            this.txtFilter.Font = new System.Drawing.Font("微軟正黑體", 14F, System.Drawing.FontStyle.Bold);
            this.txtFilter.Location = new System.Drawing.Point(205, 191);
            this.txtFilter.MaxLength = 20;
            this.txtFilter.Name = "txtFilter";
            this.txtFilter.Size = new System.Drawing.Size(230, 32);
            this.txtFilter.TabIndex = 30;
            this.txtFilter.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtFilter.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtFilter_KeyDown);
            // 
            // btnSave
            // 
            this.btnSave.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnSave.Location = new System.Drawing.Point(192, 250);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(112, 34);
            this.btnSave.TabIndex = 31;
            this.btnSave.Text = "儲存濾鏡";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label1.Location = new System.Drawing.Point(90, 194);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(109, 24);
            this.label1.TabIndex = 32;
            this.label1.Text = "濾鏡名稱：";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lblBC
            // 
            this.lblBC.BackColor = System.Drawing.Color.Transparent;
            this.lblBC.Font = new System.Drawing.Font("微軟正黑體", 14.25F);
            this.lblBC.Location = new System.Drawing.Point(313, 48);
            this.lblBC.Name = "lblBC";
            this.lblBC.Size = new System.Drawing.Size(123, 83);
            this.lblBC.TabIndex = 35;
            this.lblBC.Text = "亮度：0\r\n對比：0";
            this.lblBC.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lblHSV
            // 
            this.lblHSV.BackColor = System.Drawing.Color.Transparent;
            this.lblHSV.Font = new System.Drawing.Font("微軟正黑體", 14.25F);
            this.lblHSV.Location = new System.Drawing.Point(174, 48);
            this.lblHSV.Name = "lblHSV";
            this.lblHSV.Size = new System.Drawing.Size(142, 83);
            this.lblHSV.TabIndex = 34;
            this.lblHSV.Text = "色相：0\r\n飽和度：0\r\n明度：0";
            this.lblHSV.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lblRGB
            // 
            this.lblRGB.BackColor = System.Drawing.Color.Transparent;
            this.lblRGB.Font = new System.Drawing.Font("微軟正黑體", 14.25F);
            this.lblRGB.Location = new System.Drawing.Point(40, 48);
            this.lblRGB.Name = "lblRGB";
            this.lblRGB.Size = new System.Drawing.Size(123, 83);
            this.lblRGB.TabIndex = 33;
            this.lblRGB.Text = "紅色：0\r\n綠色：0\r\n藍色：0";
            this.lblRGB.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // Customize_Save
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(494, 325);
            this.Controls.Add(this.lblBC);
            this.Controls.Add(this.lblHSV);
            this.Controls.Add(this.lblRGB);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.txtFilter);
            this.Controls.Add(this.ckcGray);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Customize_Save";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "儲存設定";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox ckcGray;
        private System.Windows.Forms.TextBox txtFilter;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblBC;
        private System.Windows.Forms.Label lblHSV;
        private System.Windows.Forms.Label lblRGB;
    }
}