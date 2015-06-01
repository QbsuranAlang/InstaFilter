using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
// 要引用的類別 
using Emgu.CV;
using Emgu.CV.Structure;
using Emgu.CV.CvEnum;

namespace InstaFilter
{
    public partial class CAP : Form
    {
        Image<Bgr, Byte> ImageFrame;
        private string _outputFile;
        private Capture _capture;

        public CAP(string title, string outputFile, Form boss)
        {
            InitializeComponent();

            //建立capture
            try
            {
                this.Owner = boss;
                this.Text = title;
                _outputFile = outputFile;
                _capture = new Capture();
                int w = _capture.Width;
                int h = _capture.Height;
                _capture.SetCaptureProperty(CAP_PROP.CV_CAP_PROP_FRAME_WIDTH, w);
                _capture.SetCaptureProperty(CAP_PROP.CV_CAP_PROP_FRAME_HEIGHT, h);
                captureImageBox.Size = new Size(w, h);
                this.ClientSize = new Size(w, h);
                CAP_SizeChanged(null, null);
                MessageBox.Show("按下任意鍵擷取圖片", "訊息", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.Show();
                timer1.Enabled = true;
            }
            catch (Exception)
            {
                MessageBox.Show("請確認Camera驅動程式安裝正確", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
                captureImageBox.Dispose();
                this.Dispose();
                this.Close();
            }
        }

        private void CAP_FormClosed(object sender, FormClosedEventArgs e)
        {
            timer1.Enabled = false;
            if (_capture != null)
                _capture.Dispose();
            if (this != null)
                this.Dispose();
            captureImageBox.Dispose();
            this.Close();
        }

        private void CAP_KeyUp(object sender, KeyEventArgs e)
        {
            System.Threading.Thread.Sleep(100);
            ImageFrame.Save(_outputFile);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                ImageFrame = _capture.QueryFrame().Flip(FLIP.HORIZONTAL);
                //開啟攝影機時, 攝影機中斷連線
                if (ImageFrame == null)
                    throw new Exception();
                captureImageBox.Image = ImageFrame;
                this.Focus();
            }
            catch (Exception)
            {
                timer1.Enabled = false;
                _capture.Dispose();
                captureImageBox.Dispose();
                this.Dispose();
                this.Close();
                MessageBox.Show("攝影機中斷連線", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void CAP_SizeChanged(object sender, EventArgs e)
        {
            captureImageBox.Size = this.ClientSize;
            captureImageBox.Location = new Point(0, 0);
        }
    }
}