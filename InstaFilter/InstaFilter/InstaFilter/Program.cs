using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.IO;

namespace InstaFilter
{
    static class Program
    {
        /// <summary>
        /// 應用程式的主要進入點。
        /// </summary>
        [STAThread]
        static void Main()
        {
            #region 判斷重要檔案是否存在
            List<string> dir = new List<string>();
            List<string> file = new List<string>();
            bool exit = false;
            dir.Add(@"CVdll");
            dir.Add(@"CVdllCtrl");
            dir.Add(@"CVdllSP");
            dir.Add(@"CVdllDefaultCtrl");
            dir.Add(@"If");
            dir.Add(@"CVcustom");
            /*
            file.Add(@"Combine.dll");
            file.Add(@"cudart32_55.dll");
            file.Add(@"Customize.dll");
            file.Add(@"cvextern.dll");
            file.Add(@"Emgu.CV.dll");
            file.Add(@"Emgu.CV.UI.dll");
            file.Add(@"Emgu.Util.dll");
            file.Add(@"Histogram.dll");
            file.Add(@"nppc32_55.dll");
            file.Add(@"nppi32_55.dll");
            file.Add(@"npps32_55.dll");
            file.Add(@"opencv_calib3d248.dll");
            file.Add(@"opencv_calib3d290.dll");
            file.Add(@"opencv_contrib248.dll");
            file.Add(@"opencv_contrib290.dll");
            file.Add(@"opencv_core248.dll");
            file.Add(@"opencv_core290.dll");
            file.Add(@"opencv_features2d248.dll");
            file.Add(@"opencv_features2d290.dll");
            file.Add(@"opencv_flann248.dll");
            file.Add(@"opencv_flann290.dll");
            file.Add(@"opencv_highgui248.dll");
            file.Add(@"opencv_highgui290.dll");
            file.Add(@"opencv_imgproc248.dll");
            file.Add(@"opencv_imgproc290.dll");
            file.Add(@"opencv_legacy290.dll");
            file.Add(@"opencv_ml248.dll");
            file.Add(@"opencv_ml290.dll");
            file.Add(@"opencv_nonfree290.dll");
            file.Add(@"opencv_objdetect248.dll");
            file.Add(@"opencv_objdetect290.dll");
            file.Add(@"opencv_video248.dll");
            file.Add(@"opencv_video290.dll");
            file.Add(@"Operator.dll");
            file.Add(@"Resize.dll");
            file.Add(@"Save.dll");
            file.Add(@"ZedGraph.dll");
            */
            foreach (string d in dir)
            {
                if (!Directory.Exists(d))
                {
                    Directory.CreateDirectory(d);
                }//end if
            }//end foreach

            string noFound = "";//錯誤訊息
            foreach (string f in file)
            {
                if (!File.Exists(f))
                {
                    noFound += "遺失  \"" + f + "\"  檔案\r\n";
                    exit = true;
                }//end if
            }//end foreach

            if (exit)
                MessageBox.Show(noFound, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);

            #endregion
            if (!exit)
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new InstaFilter());
            }
        }
    }
}
