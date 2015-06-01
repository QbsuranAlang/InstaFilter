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
using Emgu.CV;
using Emgu.CV.Structure;
using Emgu.CV.CvEnum;
using Emgu.CV.UI;

namespace InstaFilter
{
    public partial class Histogram : Form
    {
        private Image<Gray, Byte> image;
        private Color color;
        private string windowName;
        private double[] scaleData; //hsv
        private const int colorType = 12;

        public Histogram(Image<Gray, Byte> src, string window, Color colorName)
        {
            InitializeComponent();

            this.Text = windowName;
            this.ClientSize = new Size(histogramBox.Width, this.ClientSize.Height);

            image = src.Clone();
            windowName = this.Text = window;
            color = colorName;
            trackBar1_Scroll(null, null);            
        }

        public Histogram(string fileName)
        {
            InitializeComponent();

            this.Text = Path.GetFileName(fileName) + "：Hue色相分布";
            string output = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\histogram.if";

            dld myDLD = new dld();
            myDLD.LoadFun(Directory.GetCurrentDirectory() + @"\Histogram.dll", "_HistogramProcess@8");
            //回傳型態參數設定
            object[] Parameters = new object[] { Marshal.StringToBSTR(fileName), Marshal.StringToBSTR(output) }; // 參數列
            Type[] ParameterTypes = new Type[] { typeof(IntPtr), typeof(IntPtr) }; // 參數資料型態
            dld.ModePass[] themode = new dld.ModePass[] { dld.ModePass.ByValue, dld.ModePass.ByValue }; // 全部傳值呼叫
            Type Type_Return = typeof(bool);// 回傳型態

            //回傳值判斷
            bool a = (bool)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return);
            myDLD.UnLoadDll();

            if(a && File.Exists(output))
            {
                this.Controls.Clear();
                this.Paint += new PaintEventHandler(Histogram_Paint);

                //read draw data
                StreamReader sr = new StreamReader(output);
                string[] scaleString = sr.ReadToEnd().Split(' ');
                scaleData = new double[colorType];
                for (int i = 0; i < colorType; i++)
                    scaleData[i] = double.Parse(scaleString[i]);
                sr.Close();

                this.Invalidate();
                this.Show();
            }
            else
            {
                this.Dispose();
                this.Close();
            }//end else
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            int Bbin = tkbLevel.Value; //切割量化的數量

            tkbLower.Maximum = tkbUpper.Value - 1;
            tkbUpper.Minimum = tkbLower.Value + 1;
            label1.Text = "量化階層：" + tkbLevel.Value;
            label2.Text = "下界：" + tkbLower.Value;
            label3.Text = "上界：" + tkbUpper.Value;
            label1.Update();
            label2.Update();
            label3.Update();

            RangeF BRange = new RangeF(tkbLower.Value, tkbUpper.Value);
            DenseHistogram Hist = new DenseHistogram(Bbin, BRange);
            Hist.Calculate(new Image<Gray, Byte>[] { image }, false, null);
            //histogram屬性
            histogramBox.ClearHistogram();
            histogramBox.AddHistogram(windowName, color, Hist);
            histogramBox.Location = new Point(0, 0);
            histogramBox.Refresh();
            histogramBox.Update();

            this.Controls.Add(histogramBox);
            Hist.Dispose();
            this.Update();
        }

        private void Histogram_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space || e.KeyCode == Keys.Enter)
            {
                this.Dispose();
                histogramBox.Dispose();
                this.Close();
            }
        }

        private void Histogram_Paint(object sender, PaintEventArgs e)
        {
            Color[] colors = new Color[colorType];
            int w = 60;
            int h = 300;
            colors[0] = Color.FromArgb(255, 0, 0); //紅色
            colors[1] = Color.FromArgb(255, 128, 0); //橙色
            colors[2] = Color.FromArgb(255, 255, 0); //黃色
            colors[3] = Color.FromArgb(128, 255, 0); //黃綠
            colors[4] = Color.FromArgb(0, 255, 0); //綠色
            colors[5] = Color.FromArgb(0, 255, 128); //青綠
            colors[6] = Color.FromArgb(0, 255, 255); //青色
            colors[7] = Color.FromArgb(0, 128, 255); //靛藍
            colors[8] = Color.FromArgb(0, 0, 255); //藍色
            colors[9] = Color.FromArgb(128, 0, 255); //紫色
            colors[10] = Color.FromArgb(255, 0, 255); //品紅
            colors[11] = Color.FromArgb(255, 0, 128); //紫紅

            this.ClientSize = new Size(colorType * w, h);

            e.Graphics.FillRectangle(new SolidBrush(Color.Black), 0, 0, colorType * w, h);
            for (int i = 0; i < colorType; i++)
            {
                int height = (int)(h * scaleData[i]);
                e.Graphics.FillRectangle(new SolidBrush(colors[i]), w * i, h - height, w, height);
            }//end for
        }
    }
}
