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
    public partial class Customize : Form
    {
        #region private資料
        private string information;
        private Point picboxLocation;//picbox起始位置
        private Point lblLocation;//lbl起始位置
        private string imagePath; //預覽用原始圖檔位置
        private string imageApplyPath; //預覽用圖檔位置
        private int[] values = new int[8];
        private bool isChange = false;
        private static string openFilter = "All Image Formats (*.bmp;*.jpg;*.jpeg;*.png;*.tif)|*.bmp;*.jpg;*.jpeg;*.png;*.tif|JPEG (*.jpg, *.jpeg)|*.jpg;*.jpeg|PNG (*.png)|*.png|Bitmap (*.bmp)|*.bmp|TIFF (*.tif)|*.tif";
        private static string saveFilter = "JPEG (*.jpg, *jpeg)|*.jpg;*.jpeg|PNG (*.png)|*.png|Bitmap (*.bmp)|*.bmp|TIFF (*.tif)|*.tif|All Image Formats (*.bmp;*.jpg;*.jpeg;*.png;*.tif)|*.bmp;*.jpg;*.jpeg;*.png;*.tif";
        #endregion

        public Customize(string info)
        {
            InitializeComponent();

            information = info;

            //儲存座標
            picboxLocation.X = picBox.Location.X + picBox.Width / 2;
            picboxLocation.Y = picBox.Location.Y + picBox.Width / 2;
            lblLocation = lblReslut.Location;

            //預覽圖檔位置
            imageApplyPath = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\customize.png";
        }

        private void 開啟圖檔ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = openFilter;
            open.Title = "開啟圖檔";

            if (open.ShowDialog() == DialogResult.OK)
            {
                picBoxUpdate(picBox, lblReslut, picboxLocation, open.FileName);
                imagePath = open.FileName;

                //存檔功能
                ToolStripMenuItem p = (ToolStripMenuItem)menuStrip1.Items[0];
                p.DropDownItems[1].Enabled = true;
                p.DropDownItems[2].Enabled = true;
                //trackbar打開
                trkBarBlue.Enabled = trkBarGreen.Enabled = trkBarRed.Enabled = true;
                trkBarHue.Enabled = trkBarSaturation.Enabled = trkBarValue.Enabled = true;
                trkBarBrightness.Enabled = trkBarContrast.Enabled = true;
                //打開reset
                btnReset.Enabled = true;
                btnRand.Enabled = true;
                ckcGray.Enabled = true;
                ckcHistogram.Enabled = true;
                //重新設定
                btnReset_Click(sender, e);
            }//end if

            open.Dispose();
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

        private void picBoxUpdate(PictureBox pic, Label lblImg, Point picLocation, string imagePath)
        {
            //loaded
            pic.Cursor = Cursors.Hand;//改變游標
            //開啟picbox
            pic.Visible = true;
            //讀入圖檔
            pic.Image = PathToImage(imagePath); //讀入圖檔
            //修改picbox大小

            string resizeFilePath = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\_resize_apply" + Path.GetExtension(imagePath);
            if (File.Exists(resizeFilePath))
                File.Delete(resizeFilePath);

            if (ResizeImage(imagePath, resizeFilePath) == null)
                throw new Exception("Resize發生錯誤");

            Image tempImg = PathToImage(resizeFilePath);

            int w = (int)(tempImg.Width * 1.4);
            int h = (int)(tempImg.Height * 1.4);
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
            //設定最低記憶體用量(可降低記憶體用量)
            System.Diagnostics.Process.GetCurrentProcess().MinWorkingSet = new System.IntPtr(1000);
        }

        private void 離開ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            values = null;
            this.Dispose();
            this.Close();
        }

        private void picBox_Click(object sender, EventArgs e)
        {
            try
            {
                if (File.Exists(imageApplyPath))
                    CV.Show(imageApplyPath, "預覽", ckcHistogram.Checked);
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }

        private void 關於InstaFilterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show(information, "關於", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void trkBar_Scroll(object sender, EventArgs e)
        {
            values[0] = trkBarRed.Value;
            values[1] = trkBarGreen.Value;
            values[2] = trkBarBlue.Value;
            values[3] = trkBarHue.Value;
            values[4] = trkBarSaturation.Value;
            values[5] = trkBarValue.Value;
            values[6] = trkBarBrightness.Value;
            values[7] = trkBarContrast.Value;

            lblBC.Update();
            lblHSV.Update();
            lblRGB.Update();
            ckcGray.Update();

            getTrackbarInfo();

            CV.applyCustomizeSetting(imagePath, imageApplyPath, values, ckcGray.Checked);

            picBoxUpdate(picBox, lblReslut, picboxLocation, imageApplyPath);

            picBox.Update();
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            trkBarRed.Value = 0;
            trkBarGreen.Value = 0;
            trkBarBlue.Value = 0;
            trkBarHue.Value = 0;
            trkBarSaturation.Value = 0;
            trkBarValue.Value = 0;
            trkBarBrightness.Value = 0;
            trkBarContrast.Value = 0;
            ckcGray.Checked = false;
            Array.Clear(values, 0, values.Count());

            getTrackbarInfo();

            if (File.Exists(imageApplyPath))
                File.Delete(imageApplyPath);
            File.Copy(imagePath, imageApplyPath);
            picBoxUpdate(picBox, lblReslut, picboxLocation, imagePath);
        }

        private void getTrackbarInfo()
        {
            lblRGB.Text = "紅色：" + values[0] +
                        "\r\n綠色：" + values[1] +
                        "\r\n藍色：" + values[2];

            lblHSV.Text = "色相：" + values[3] +
                        "\r\n飽和度：" + values[4] +
                        "\r\n明度：" + values[5];

            lblBC.Text = "亮度：" + values[6] +
                        "\r\n對比：" + values[7];
        }

        private void btnRand_Click(object sender, EventArgs e)
        {
            Random rnd = new Random(Guid.NewGuid().GetHashCode());

            trkBarRed.Value = values[0] = rnd.Next(-50, 100);
            trkBarGreen.Value = values[1] = rnd.Next(-50, 100);
            trkBarBlue.Value = values[2] = rnd.Next(-50, 100);
            trkBarHue.Value = values[3] = rnd.Next(-50, 50);
            trkBarSaturation.Value = values[4] = rnd.Next(-50, 30);
            trkBarValue.Value = values[5] = rnd.Next(-20, 20);
            trkBarBrightness.Value = values[6] = rnd.Next(-20, 20);
            trkBarContrast.Value = values[7] = rnd.Next(-60, 80);

            //以防check box變之後做兩次
            isChange = false;
            //check change call ckcGray_CheckedChanged
            if(rnd.Next() % 2 == 0)
                ckcGray.Checked = true;
            else
                ckcGray.Checked = false;

            getTrackbarInfo();

            lblBC.Update();
            lblHSV.Update();
            lblRGB.Update();
            ckcGray.Update();

            if (!isChange)
            {
                CV.applyCustomizeSetting(imagePath, imageApplyPath, values, ckcGray.Checked);
                picBoxUpdate(picBox, lblReslut, picboxLocation, imageApplyPath);
                picBox.Update();
            }
        }
        
        private void ckcGray_CheckedChanged(object sender, EventArgs e)
        {
            isChange = true;
            CV.applyCustomizeSetting(imagePath, imageApplyPath, values, ckcGray.Checked);
            picBoxUpdate(picBox, lblReslut, picboxLocation, imageApplyPath);
            picBox.Update();
        }

        private void 刪除濾鏡ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Customize_Delete delete = new Customize_Delete();
            delete.Show(this);
        }

        private void 儲存濾鏡設定ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Customize_Save save = new Customize_Save(lblRGB.Text, lblHSV.Text, lblBC.Text, ckcGray.Checked, values);
            save.Show(this);
        }

        private void 儲存圖片ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveAs = new SaveFileDialog();
            saveAs.Filter = saveFilter;
            saveAs.Title = "另存新檔";

            if (saveAs.ShowDialog() == DialogResult.OK)
            {
                if (Path.GetExtension(imageApplyPath) != Path.GetExtension(saveAs.FileName))//副檔名不同需要轉檔
                {
                    dld myDLD = new dld();
                    myDLD.LoadFun(Directory.GetCurrentDirectory() + @"\Save.dll", "_saveImage@8");

                    //回傳型態參數設定
                    object[] Parameters = new object[] { Marshal.StringToBSTR(imageApplyPath), Marshal.StringToBSTR(saveAs.FileName) }; // 參數列
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
                else//副檔名相同
                {
                    if (File.Exists(saveAs.FileName))
                        File.Delete(saveAs.FileName);
                    File.Copy(imageApplyPath, saveAs.FileName);
                }//end else
            }//end if

            saveAs.Dispose();
        }
    }
}
