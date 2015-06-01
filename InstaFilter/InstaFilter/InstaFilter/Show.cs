using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Emgu.CV;
using Emgu.CV.Structure;
using Emgu.CV.CvEnum;
using Emgu.CV.UI;
using System.IO;
using System.Runtime.InteropServices;
using System.Drawing.Drawing2D;

namespace InstaFilter
{
    public partial class Show : Form
    {

        public Show(string filePath, string windowName, bool isShowInfo, bool isHistogram)
        {
            InitializeComponent();

            try
            {
                if (!File.Exists(filePath))
                {
                    throw new Exception("檔案不存在");
                }//end if
                else
                {
                    //讀取圖片
                    Image<Bgra, Byte> img = new Image<Bgra, Byte>(filePath);

                    Size imgSize = img.Size;
                    Size screen = Screen.PrimaryScreen.Bounds.Size;
                    string infomation = "";
                    
                    IntPtr srcImage = CvInvoke.cvLoadImage(filePath, LOAD_IMAGE_TYPE.CV_LOAD_IMAGE_UNCHANGED);
                    MIplImage image = (MIplImage)Marshal.PtrToStructure(srcImage, typeof(MIplImage));
                    
                    //get infomation
                    if (isShowInfo)
                    {
                        FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read);

                        infomation = "檔案名稱：" + Path.GetFileName(filePath) + "\r\n" +
                            "檔案大小：" + fs.Length + " bytes\r\n" +
                            "寬：" + image.width + " pixels\r\n" +
                            "高：" + image.height + " pixels\r\n" +
                            "總像素：" + (image.height * image.width) + " pixels\r\n" +
                            "頻道數：" + image.nChannels + "\r\n" +
                            "位元深度：" + (Convert.ToDouble(image.depth) * image.nChannels) + " bits\r\n" +
                            "單一頻道位元深度：" + Convert.ToDouble(image.depth) + " bits\r\n";
                        fs.Close();
                    }//end if

                    while (imgSize.Width + 100 > screen.Width || imgSize.Height + 100 > screen.Height)
                    {
                        imgSize.Height = Convert.ToInt32(Convert.ToDouble(imgSize.Height) / 1.4);
                        imgSize.Width = Convert.ToInt32(Convert.ToDouble(imgSize.Width) / 1.4);
                    }//end while

                    //屬性設定
                    this.ClientSize = imgSize;
                    this.Text = windowName;
                    ImageBox.Size = imgSize;
                    ImageBox.Location = new Point(0, 0);
                    img.Resize(imgSize.Width, imgSize.Height, INTER.CV_INTER_LINEAR);
                    ImageBox.Image = img;

                    #region 直方圖
                    if (isHistogram)
                    {
                        if (image.nChannels == 1 || image.nChannels == 3 || image.nChannels == 4)
                        {
                            int channel = image.nChannels;
                            Image<Gray, Byte>[] splitChannels = img.Split();
                            Image<Gray, Byte>[] hsv = img.Convert<Hsv, Byte>().Split();
                            if (hsv[0].Equals(hsv[1]))//灰階影像H和S相同(全黑)
                                channel = 1;//灰階影像

                            switch (channel)
                            {
                                case 1:
                                    new Histogram(splitChannels[0], windowName + "：Gray", Color.DarkViolet).Show();
                                    break;
                                    
                                case 3:
                                    new Histogram(splitChannels[0], windowName + "：Blue", Color.Blue).Show();
                                    new Histogram(splitChannels[1], windowName + "：Green", Color.Green).Show();
                                    new Histogram(splitChannels[2], windowName + "：Red", Color.Red).Show();
                                    new Histogram(filePath);
                                    break;

                                case 4:
                                    new Histogram(splitChannels[3], windowName + "：Alpha", Color.Orange).Show();
                                    new Histogram(splitChannels[0], windowName + "：Blue", Color.Blue).Show();
                                    new Histogram(splitChannels[1], windowName + "：Green", Color.Green).Show();
                                    new Histogram(splitChannels[2], windowName + "：Red", Color.Red).Show();
                                    new Histogram(filePath);
                                    break;
                            }

                            foreach (Image<Gray, Byte> cha in splitChannels)
                                cha.Dispose();
                            foreach (Image<Gray, Byte> cha in hsv)
                                cha.Dispose();
                        }//end show Histogram
                    }//end show histogram
                    #endregion
                    this.Show();

                    if (isShowInfo)
                    {
                        if (MessageBox.Show(infomation, "資訊", MessageBoxButtons.OK, MessageBoxIcon.Information) == DialogResult.OK)
                            this.KeyUp += new KeyEventHandler(Show_KeyUpNoEnter);
                    }
                    else
                        this.KeyUp += new KeyEventHandler(Show_KeyUp);

                    //release
                    //img.Dispose();
                    CvInvoke.cvReleaseImage(ref srcImage);
                    srcImage = IntPtr.Zero;
                }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); this.Dispose(); this.Close(); }
        }

        private void Show_Paint(object sender, PaintEventArgs e)
        {
            SolidBrush white = new SolidBrush(Color.White);
            SolidBrush gray = new SolidBrush(Color.Gray);

            Size p1 = new Size(this.ClientSize.Width, this.ClientSize.Height);
            Size p0 = new Size(0, 0);

            int pixelSize = 30;
            for (int i = 1; i <= pixelSize; i++)
                for (int j = 1; j <= pixelSize; j++)
                {
                    int w = (p1.Width - p0.Width) / pixelSize + 1;
                    int h = (p1.Height - p0.Height) / pixelSize + 1;
                    int X = p0.Width + w * (i - 1);
                    int Y = p0.Height + h * (j - 1);

                    if ((i + j) % 2 == 0)
                        e.Graphics.FillRectangle(white, X, Y, w, h);
                    else
                        e.Graphics.FillRectangle(gray, X, Y, w, h);
                }//end for
        }

        private void Show_KeyUpNoEnter(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space)
            {
                this.Dispose();
                ImageBox.Dispose();
                this.Close();
            }
        }

        private void Show_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space || e.KeyCode == Keys.Enter)
            {
                this.Dispose();
                ImageBox.Dispose();
                this.Close();
            }
        }

        private void Show_SizeChanged(object sender, EventArgs e)
        {
            ImageBox.Size = this.ClientSize;
        }

    }
}
