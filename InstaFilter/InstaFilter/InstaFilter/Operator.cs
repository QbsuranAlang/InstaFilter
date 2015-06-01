using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;

namespace InstaFilter
{
    public partial class Operator : Form
    {
        #region private資料
        private string procName = null;
        private string opDll = null; //operator 位置
        private string image1Path = null;//影像位置
        private string image2Path = null;//影像位置
        private string cap1Path = null;//影像位置
        private string cap2Path = null;//影像位置
        private string capture1Path = null;//capture影像位置
        private string capture2Path = null;//capture影像位置
        private string reslutPath = null;//運算結果影像位置
        private string _type = null;//運算類型
        private Point pic1Location;//picbox起始位置
        private Point pic2Location;
        private Point picReslutLocation;
        private Point lblImg1Location;//lbl起始位置
        private Point lblImg2Location;
        private Point lblImgReslutLocation;
        private bool isDo1 = false;
        private bool isDo2 = false;
        private bool work = false;
        private string information;
        private static string openFilter = "All Image Formats (*.bmp;*.jpg;*.jpeg;*.png;*.tif)|*.bmp;*.jpg;*.jpeg;*.png;*.tif|JPEG (*.jpg, *.jpeg)|*.jpg;*.jpeg|PNG (*.png)|*.png|Bitmap (*.bmp)|*.bmp|TIFF (*.tif)|*.tif";
        private static string saveFilter = "JPEG (*.jpg, *jpeg)|*.jpg;*.jpeg|PNG (*.png)|*.png|Bitmap (*.bmp)|*.bmp|TIFF (*.tif)|*.tif|All Image Formats (*.bmp;*.jpg;*.jpeg;*.png;*.tif)|*.bmp;*.jpg;*.jpeg;*.png;*.tif";
        #endregion

        public Operator(string type, bool isCodeMode, string info)
        {
            InitializeComponent();

            //switch 功能
            switch (type)
            {
                case "影像相加(Linear Dodge)":
                    procName = "_add@12";
                    this.Show();
                    break;

                case "影像相減(Linear Subtract)":
                    procName = "_sub@12";
                    this.Show();
                    break;

                case "差值(Difference)":
                    procName = "_subAbs@12";
                    this.Show();
                    break;

                case "影像融合(Opacity)":
                    procName = "_opacity@12";
                    this.Show();
                    break;

                case "正片叠底(Multiply)":
                    procName = "_multiply@12";
                    this.Show();
                    break;

                case "濾色(Screen)":
                    procName = "_screen@12";
                    this.Show();
                    break;

                case "疊加(Overlay)":
                    procName = "_overlay@12";
                    this.Show();
                    break;

                case "變暗(Darken)":
                    procName = "_darken@12";
                    this.Show();
                    break;

                case "變亮(Lighten)":
                    procName = "_lighten@12";
                    this.Show();
                    break;

                case "加亮顏色(Color Dodge)":
                    procName = "_colorDodge@12";
                    this.Show();
                    break;

                case "加深顏色(Color Burn)":
                    procName = "_colorBurn@12";
                    this.Show();
                    break;

                case "線性加深(Linear Burn)":
                    procName = "_linearBurn@12";
                    this.Show();
                    break;
                    
                case "強烈光源(Hard Light)":
                    procName = "_hardLight@12";
                    this.Show();
                    break;

                case "柔光(Soft Light)":
                    procName = "_softLight@12";
                    this.Show();
                    break;

                case "線性光源(Linear Light)":
                    procName = "_linearLight@12";
                    this.Show();
                    break;

                case "實光(Vivid Light)":
                    procName = "_vividLight@12";
                    this.Show();
                    break;

                case "實色疊印混和(Hard Mix)":
                    procName = "_hardMix@12";
                    this.Show();
                    break;

                case "排除(Exclusion)":
                    procName = "_exclusion@12";
                    this.Show();
                    break;

                case "峰值信號雜訊比(PSNR)":
                    procName = "_PSNR@8";
                    //存檔功能
                    ToolStripMenuItem p = (ToolStripMenuItem)menuStrip1.Items[0];
                    p.DropDownItems[4].Visible = false;
                    ckcHistogram.Visible = false;
                    ckcHistogram.Enabled = false;
                    ckcHistogram.Enabled = false;
                    ckcHistogram.Visible = false;
                    this.Show();
                    break;

                default:
                    MessageBox.Show("查無此功能", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    this.Dispose();
                    this.Close();
                break;
            }//end switch

            //顯示程式碼
            if (isCodeMode)
                new Code(Directory.GetCurrentDirectory() + @"\Operator.dll");
            //標題
            _type = this.Text = type;
            //dll位置
            opDll = Directory.GetCurrentDirectory() + @"\Operator.dll";
            //instafilter資訊
            information = info;
            //capture影像位置
            capture1Path = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\opCapture1.png";
            capture2Path = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\opCapture2.png";

            //取得原圖以及預覽圖中心點座標
            pic1Location.X = pic1.Location.X + pic1.Width / 2;
            pic1Location.Y = pic1.Location.Y + pic1.Width / 2;
            pic2Location.X = pic2.Location.X + pic2.Width / 2;
            pic2Location.Y = pic2.Location.Y + pic2.Width / 2;
            picReslutLocation.X = picReslut.Location.X + picReslut.Width / 2;
            picReslutLocation.Y = picReslut.Location.Y + picReslut.Width / 2;

            //取得lbl座標
            lblImg1Location = lblImg1.Location;
            lblImg2Location = lblImg2.Location;
            lblImgReslutLocation = lblReslut.Location;
        }

        private Image PathToImage(string sourceFile)
        {
            FileStream f1 = new FileStream(sourceFile, FileMode.Open);
            Byte[] data1 = new Byte[f1.Length];
            f1.Read(data1, 0, data1.Length);
            f1.Close();
            f1.Dispose();
            f1 = null;
            MemoryStream m1 = new MemoryStream(data1);
            Image img = Image.FromStream(m1); //讀入圖檔
            m1.Close();
            m1.Dispose();
            m1 = null;
            return img;
        }

        //image to buffer
        private byte[] ImageToBuffer(Image image)
        {
            byte[] buffer = null;
            using (Bitmap oBitmap = new Bitmap(image))
            {
                using (MemoryStream MS = new MemoryStream())
                {
                    oBitmap.Save(MS, System.Drawing.Imaging.ImageFormat.Png);
                    MS.Position = 0;
                    buffer = new byte[MS.Length];
                    MS.Read(buffer, 0, Convert.ToInt32(MS.Length));
                    MS.Flush();
                    MS.Close();
                    MS.Dispose();
                }
            }

            return buffer;
        }

        //buffer to image
        private Image BufferToImage(byte[] Buffer)
        {
            byte[] data = null;
            Image oImage = null;
            MemoryStream oMemoryStream = null;
            Bitmap oBitmap = null;
            //建立副本
            data = (byte[])Buffer.Clone();
            try
            {
                oMemoryStream = new MemoryStream(data);
                //設定資料流位置
                oMemoryStream.Position = 0;
                oImage = System.Drawing.Image.FromStream(oMemoryStream);
                //建立副本
                oBitmap = new Bitmap(oImage);
            }
            catch
            {
                throw;
            }
            finally
            {
                oMemoryStream.Close();
                oMemoryStream.Dispose();
                oMemoryStream = null;
            }
            return oBitmap;
        }

        private void 開啟檔案1ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = openFilter;
            open.Title = "開啟圖檔1";

            if (open.ShowDialog() == DialogResult.OK)
            {
                ckcHistogram.Enabled = true;
                work = true;
                image1Path = open.FileName;
                getImage(pic1, lblImg1, pic1Location, open.FileName);
            }//end if
            open.Dispose();
        }

        private void 開啟檔案2ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = openFilter;
            open.Title = "開啟圖檔2";

            if (open.ShowDialog() == DialogResult.OK)
            {
                ckcHistogram.Enabled = true;
                work = true;
                image2Path = open.FileName;
                getImage(pic2, lblImg2, pic2Location, open.FileName);
            }//end if
            open.Dispose();
        }

        private void getImage(PictureBox pic, Label lblImg, Point picLocation, string imagePath)
        {
            //loaded
            pic.Cursor = Cursors.Hand;//改變游標
            //開啟picbox
            pic.Visible = true;
            //讀入圖檔
            pic.Image = PathToImage(imagePath); //讀入圖檔
            //修改picbox大小
            
            Random rnd = new Random(Guid.NewGuid().GetHashCode());
            string resizeFilePath = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\" + rnd.Next() + Path.GetExtension(imagePath);

            if (ResizeImage(imagePath, resizeFilePath) == null)
                throw new Exception("Resize發生錯誤");
            
            Image tempImg = PathToImage(resizeFilePath);

            double scale = 1.3;
            if (tempImg.Width != tempImg.Height)
                scale = 1.4;
            int w = (int)(tempImg.Width * scale);
            int h = (int)(tempImg.Height * scale);
            int labelH = tempImg.Height / 2;
            pic.Width = w;
            pic.Height = h;
            pic.Location = new Point(picLocation.X - w / 2, picLocation.Y - h / 2);
            tempImg.Dispose();
            tempImg = null;

            //label位置
            lblImg.Location = new Point(picLocation.X - lblImg.Width / 2, h + pic.Location.Y + 8);
        }
        
        private string ResizeImage(string inputFile, string outputFile)
        {
            dld myDLD = new dld();
            myDLD.LoadFun(Directory.GetCurrentDirectory() + @"\Resize.dll", "_opencvResize@8");
            //回傳型態參數設定
            object[] Parameters = new object[] { Marshal.StringToBSTR(inputFile), Marshal.StringToBSTR(outputFile) }; // 參數列
            Type[] ParameterTypes = new Type[] { typeof(IntPtr), typeof(IntPtr) }; // 參數資料型態
            dld.ModePass[] themode = new dld.ModePass[] { dld.ModePass.ByValue, dld.ModePass.ByValue }; // 全部傳值呼叫
            Type Type_Return = typeof(bool);// 回傳型態

            //回傳值判斷
            bool a = (bool)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return);
            myDLD.UnLoadDll();

            if (a)
                return outputFile;
            return null;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (pic1.Image != null && pic2.Image != null && work)
            {
                work = false;
                btnDo.Visible = true;
                btnDo.Enabled = true;
                btnDo_Click(sender, e);
            }//end if
            
            if (isDo1 && isDo2)
            {
                tmrCap1.Enabled = false;
                tmrCap2.Enabled = false;
            }//end if
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            //設定最低記憶體用量(可降低記憶體用量)
            System.Diagnostics.Process.GetCurrentProcess().MinWorkingSet = new System.IntPtr(1000);
        }

        private void 離開ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pic1.Dispose();
            pic2.Dispose();
            picReslut.Dispose();
            this.Dispose();
            this.Close();
        }

        private void btnDo_Click(object sender, EventArgs e)
        {
            isDo1 = isDo2 = false;

            if (procName != "_PSNR@8")
            {
                #region procName != PSNR

                dld myDLD = new dld();
                myDLD.LoadFun(opDll, procName);

                Random rnd = new Random(Guid.NewGuid().GetHashCode());
                reslutPath = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\" + rnd.Next() + Path.GetExtension(@".png");

                //回傳型態參數設定
                object[] Parameters = new object[] { Marshal.StringToBSTR(image1Path), Marshal.StringToBSTR(image2Path), Marshal.StringToBSTR(reslutPath) }; // 參數列
                Type[] ParameterTypes = new Type[] { typeof(IntPtr), typeof(IntPtr), typeof(IntPtr) }; // 參數資料型態
                dld.ModePass[] themode = new dld.ModePass[] { dld.ModePass.ByValue, dld.ModePass.ByValue, dld.ModePass.ByValue }; // 全部傳值呼叫
                Type Type_Return = typeof(bool);// 回傳型態

                //回傳值判斷
                bool a = (bool)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return);
                myDLD.UnLoadDll();
                myDLD = null;

                //存檔功能
                ToolStripMenuItem p = (ToolStripMenuItem)menuStrip1.Items[0];

                if (a)
                {
                    getImage(picReslut, lblReslut, picReslutLocation, reslutPath);
                    lblReslut.Visible = true;
                    picReslut.Visible = true;
                    btnDo.Enabled = true;
                    btnDo.Visible = true;
                    p.DropDownItems[4].Enabled = true;
                    ckcHistogram.Enabled = true;
                }//end if
                else
                {
                    lblReslut.Visible = false;
                    picReslut.Visible = false;
                    ckcHistogram.Checked = false;
                    picReslut.Image = null;
                    picReslut.Cursor = Cursors.Default;
                    lblReslut.Location = lblImgReslutLocation;
                    reslutPath = null;
                    btnDo.Enabled = false;
                    btnDo.Visible = false;
                    p.DropDownItems[4].Enabled = false;
                    MessageBox.Show("檔案寬高不同或檔案不存在", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }//end else
                #endregion
            }
            else
            {
                #region procName == PSNR

                dld myDLD = new dld();
                myDLD.LoadFun(opDll, procName);

                //回傳型態參數設定
                object[] Parameters = new object[] { Marshal.StringToBSTR(image1Path), Marshal.StringToBSTR(image2Path) }; // 參數列
                Type[] ParameterTypes = new Type[] { typeof(IntPtr), typeof(IntPtr) }; // 參數資料型態
                dld.ModePass[] themode = new dld.ModePass[] { dld.ModePass.ByValue, dld.ModePass.ByValue }; // 全部傳值呼叫
                Type Type_Return = typeof(double);// 回傳型態

                //回傳值判斷
                double a = (double)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return);
                myDLD.UnLoadDll();
                myDLD = null;

                if (a > 0)
                {
                    if (a.ToString() == "正無窮大")
                        lblReslut.Text = "兩張圖檔完全相同";
                    else
                        lblReslut.Text = "PSNR：" + Math.Round(a, 5).ToString() + " dB";

                    lblReslut.Visible = true;
                    picReslut.Visible = true;
                    btnDo.Enabled = true;
                    lblReslut.Location = new Point(lblImgReslutLocation.X - lblReslut.Width / 2, lblReslut.Location.Y);
                }//end if
                else if(a <= 0)
                {
                    lblReslut.Visible = false;
                    lblReslut.Location = lblImgReslutLocation;
                    reslutPath = null;
                    btnDo.Enabled = false;
                    MessageBox.Show("檔案寬高不同或檔案不存在", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }//end else
                #endregion
            }
        }

        private void 另存新檔ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveAs = new SaveFileDialog();
            saveAs.Filter = saveFilter;
            saveAs.Title = "另存新檔";

            if (saveAs.ShowDialog() == DialogResult.OK)
            {
                if (File.Exists(saveAs.FileName))
                    File.Delete(saveAs.FileName);
                dld myDLD = new dld();
                myDLD.LoadFun(Directory.GetCurrentDirectory() + @"\Save.dll", "_saveImage@8");

                //回傳型態參數設定
                object[] Parameters = new object[] { Marshal.StringToBSTR(reslutPath), Marshal.StringToBSTR(saveAs.FileName) }; // 參數列
                Type[] ParameterTypes = new Type[] { typeof(IntPtr), typeof(IntPtr) }; // 參數資料型態
                dld.ModePass[] themode = new dld.ModePass[] { dld.ModePass.ByValue, dld.ModePass.ByValue }; // 全部傳值呼叫
                Type Type_Return = typeof(bool);// 回傳型態

                //回傳值判斷
                bool a = (bool)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return);
                myDLD.UnLoadDll();
                myDLD = null;
                if (!a)
                    MessageBox.Show("存檔發生錯誤", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }//end if
            saveAs.Dispose();
        }

        private void 關於InstaFilterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show(information, "關於", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void 從攝影機匯入1ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tmrCap1.Enabled = true;
            //啟動視訊
            CAP cap = new CAP("Capture 1", capture1Path, this);
            cap.Owner = this;
        }

        private void 從攝影機匯入2ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            tmrCap2.Enabled = true;
            //啟動視訊
            CAP cap = new CAP("Capture 2", capture2Path, this);
            cap.Owner = this;
        }

        private void tmrCap1_Tick(object sender, EventArgs e)
        {
            if (File.Exists(capture1Path))
            {
                Random rnd = new Random(Guid.NewGuid().GetHashCode());
                cap1Path = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\" + rnd.Next() + Path.GetExtension(capture1Path);

                if (File.Exists(cap1Path))
                    File.Delete(cap1Path);
                File.Move(capture1Path, cap1Path);
                image1Path = cap1Path;

                getImage(pic1, lblImg1, pic1Location, cap1Path);

                isDo1 = true;
                work = true;
            }//end if
        }

        private void tmrCap2_Tick(object sender, EventArgs e)
        {
            if (File.Exists(capture2Path))
            {
                Random rnd = new Random(Guid.NewGuid().GetHashCode());
                cap2Path = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\" + rnd.Next() + Path.GetExtension(capture2Path);

                if (File.Exists(cap2Path))
                    File.Delete(cap2Path);
                File.Move(capture2Path, cap2Path);
                image2Path = cap2Path;

                getImage(pic2, lblImg2, pic2Location, cap2Path);

                isDo2 = true;
                work = true;
            }//end if
        }

        private void pic_Click(object sender, EventArgs e)
        {
            PictureBox pic = (PictureBox)sender;

            try
            {
                if (pic.Name == "pic1")
                    showImage(image1Path, true, Path.GetFileName(image1Path));
                else if (pic.Name == "pic2")
                    showImage(image2Path, true, Path.GetFileName(image2Path));
                else if (pic.Name == "picReslut")
                    showImage(reslutPath, false, _type);
                else
                    throw new Exception("找不到物件 :" + pic.Name);
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }

        private void showImage(string input, bool isShowInfo, string windowName)
        {
            try
            {
                if (input != null)//視窗剛開啟
                {
                    if (isShowInfo)//info dll存在就呼叫show info
                        CV.ShowInfo(input, windowName, ckcHistogram.Checked);
                    else
                        CV.Show(input, windowName, ckcHistogram.Checked);
                }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }
    }
}
