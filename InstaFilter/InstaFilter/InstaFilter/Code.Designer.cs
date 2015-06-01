namespace InstaFilter
{
    partial class Code
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Code));
            this.txtBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // txtBox
            // 
            this.txtBox.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.txtBox.Font = new System.Drawing.Font("Monaco", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtBox.ForeColor = System.Drawing.Color.Chartreuse;
            this.txtBox.Location = new System.Drawing.Point(0, 0);
            this.txtBox.Multiline = true;
            this.txtBox.Name = "txtBox";
            this.txtBox.ReadOnly = true;
            this.txtBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtBox.Size = new System.Drawing.Size(100, 22);
            this.txtBox.TabIndex = 2;
            this.txtBox.WordWrap = false;
            this.txtBox.KeyUp += new System.Windows.Forms.KeyEventHandler(this.txtBox_KeyUp);
            // 
            // Code
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(1084, 572);
            this.Controls.Add(this.txtBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Code";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Code";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Code_FormClosing);
            this.SizeChanged += new System.EventHandler(this.Code_SizeChanged);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtBox;
    }
}