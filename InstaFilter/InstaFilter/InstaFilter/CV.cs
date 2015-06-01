using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices; // 用 DllImport 需用此 命名空間 
using System.IO;// 用 Path
using System.Windows.Forms;

namespace InstaFilter
{
    class CV
    {
        //Random rnd = new Random(Guid.NewGuid().GetHashCode());

        #region private 資料
        private string _sourceFileInTempName; //原始檔案複製一份到暫存
        private string _resizeFileName; //縮小版本檔案
        private string _tempPath; //暫存資料夾位置
        private string _resizeDll; //resize用dll位置
        private string _showDll; //show用dll位置
        #endregion

        #region CV constructor
        public CV(string resizeDll, string showDll, string sourceFile, string resizeFIleName, string tempPath)
        {
            try
            {
                Random rnd = new Random(Guid.NewGuid().GetHashCode());

                _resizeDll = resizeDll;
                //解決中文檔名問題
                _sourceFileInTempName = tempPath + @"\_" + rnd.Next() + Path.GetExtension(sourceFile);//將原檔重新命名放入暫存裡
                File.Copy(sourceFile, _sourceFileInTempName); //複製檔案

                _resizeFileName = resizeFIleName;
                _tempPath = tempPath;
                _showDll = showDll;

                //resize版本存在時, 刪除檔案
                if (File.Exists(_resizeFileName))
                    File.Delete(_resizeFileName);

                //製作resize版本
                string a = Resize(_sourceFileInTempName, _resizeFileName);
                if (a == null) throw (new Exception("resize時, 發生錯誤"));
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }//end CV constructor
        #endregion

        #region Resize
        public string Resize(string inputFile, string outputFile)
        {
            dld myDLD = new dld();
            myDLD.LoadFun(_resizeDll, "_opencvResize@8");
            //回傳型態參數設定
            object[] Parameters = new object[] { Marshal.StringToBSTR(inputFile), Marshal.StringToBSTR(outputFile) }; // 參數列
            Type[] ParameterTypes = new Type[] { typeof(IntPtr), typeof(IntPtr) }; // 參數資料型態
            dld.ModePass[] themode = new dld.ModePass[] { dld.ModePass.ByValue, dld.ModePass.ByValue }; // 全部傳值呼叫
            Type Type_Return = typeof(bool);// 回傳型態

            //回傳值判斷
            bool a = (bool)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return);
            myDLD.UnLoadDll();

            if(a)
                return outputFile;
            return null;
        }//end resize
        #endregion

        #region insideProcess
        private string insideProcess(string dll, string inputFile, string outputFile)
        {
            try
            {
                dld myDLD = new dld();
                myDLD.LoadFun(dll, "_opencvProcess@8");
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
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); return null; }
        }//end insideProcess
        #endregion

        #region Process
        public string Process(string dll)
        {
            Random rnd = new Random(Guid.NewGuid().GetHashCode());
            string outputName = _tempPath + @"\" + rnd.Next() + Path.GetExtension(_sourceFileInTempName);
            return this.insideProcess(dll, _resizeFileName, outputName);
        }//end Process
        #endregion

        #region ProcessSP
        public string ProcessSP(string dll)
        {
            Random rnd = new Random(Guid.NewGuid().GetHashCode());
            string outputName = _tempPath + @"\" + rnd.Next() + Path.GetExtension(_sourceFileInTempName);
            string tempOutput = this.insideProcess(dll, _sourceFileInTempName, outputName);
            if (tempOutput != null)//正確做出原尺寸的濾鏡
            {
                string outputName2 = _tempPath + @"\" + rnd.Next() + Path.GetExtension(_sourceFileInTempName);
                return this.Resize(tempOutput, outputName2);
            }//end if
            else
                return null;
        }//end Process
        #endregion

        #region ProcessOrginalSize
        public string ProcessOrginalSize(string processImage, string dll)
        {
            Random rnd = new Random(Guid.NewGuid().GetHashCode());
            string outputName = _tempPath + @"\" + rnd.Next() + Path.GetExtension(processImage);

            if (Path.GetExtension(dll) == ".if")
                return this.customizeFilterOrginalSize(processImage, dll);
            else
                return this.insideProcess(dll, processImage, outputName);
        }//end ProcessOrignalSize
        #endregion

        #region GetFilterName
        public static string GetFilterName(String dll)
        {
            try
            {
                if (!File.Exists(dll))
                    throw new Exception("濾鏡不存在");
                if (Path.GetExtension(dll) == ".if")
                {
                    StreamReader sr = new StreamReader(dll);
                    string filterName = sr.ReadLine();//濾鏡名稱
                    string[] temp = filterName.Split(new string[]{ Environment.NewLine }, 256, StringSplitOptions.None);
                    filterName = temp[0];
                    sr.Close();
                    return filterName;
                }//end if
                else
                {
                    dld myDLD = new dld();
                    myDLD.LoadFun(dll, "_getFilterName@0");

                    object[] Parameters = new object[] { };
                    Type[] ParameterTypes = new Type[] { };
                    dld.ModePass[] themode = new dld.ModePass[] { };

                    Type Type_Return = typeof(IntPtr);// 回傳型態
                    string filter = Marshal.PtrToStringUni((IntPtr)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return));

                    myDLD.UnLoadDll();

                    return filter;
                }//end else
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); return null; }
        }//end GetFilterName
        #endregion

        #region Show
        public static void Show(string showFile, string windowName, bool isHistogram)
        {
            new Show(showFile, windowName, false, isHistogram);
        }//end Show
        #endregion

        #region ShowInfo
        public static void ShowInfo(string showFile, string windowName, bool isHistogram)
        {
            new Show(showFile, windowName, true, isHistogram);
        }//end Show
        #endregion

        #region applyCustomizeSetting
        public static void applyCustomizeSetting(string inputFile, string outputFile, int[] values, bool isGray)
        {
            dld myDLD = new dld();
            myDLD.LoadFun(Directory.GetCurrentDirectory() + @"\Customize.dll", "_customizeImage@16");

            //回傳型態參數設定
            object[] Parameters = new object[] { Marshal.StringToBSTR(inputFile), Marshal.StringToBSTR(outputFile), values, isGray }; // 參數列
            Type[] ParameterTypes = new Type[] { typeof(IntPtr), typeof(IntPtr), typeof(int[]), typeof(bool) }; // 參數資料型態
            dld.ModePass[] themode = new dld.ModePass[] { dld.ModePass.ByValue, dld.ModePass.ByValue, dld.ModePass.ByValue, dld.ModePass.ByValue }; // 全部傳值呼叫
            Type Type_Return = typeof(bool);// 回傳型態

            //回傳值判斷
            bool a = (bool)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return);
            myDLD.UnLoadDll();
            myDLD = null;

            if (!a)
                throw new Exception("使用者自訂濾鏡發生錯誤");
        }//end applyCustomizeSetting
        #endregion

        #region customizeFilter
        public string customizeFilter(string settingsFile)
        {
            Random rnd = new Random(Guid.NewGuid().GetHashCode());
            string outputName = _tempPath + @"\" + rnd.Next() + Path.GetExtension(_sourceFileInTempName);
            return insideCustomizeFilter(_resizeFileName, outputName, settingsFile);
        }//end customizeFilter
        #endregion

        #region customizeFilterOrginalSize
        public string customizeFilterOrginalSize(string inputFile, string settingsFile)
        {
            Random rnd = new Random(Guid.NewGuid().GetHashCode());
            string outputName = _tempPath + @"\" + rnd.Next() + Path.GetExtension(_sourceFileInTempName);

            if (Path.GetExtension(settingsFile) == ".dll")
                return ProcessOrginalSize(inputFile, settingsFile);
            else
                return insideCustomizeFilter(inputFile, outputName, settingsFile);
        }//end customizeFilterOrginalSize
        #endregion

        #region insideCustomizeFilter
        public string insideCustomizeFilter(string inputFile, string outputFile, string settingsFile)
        {
            dld myDLD = new dld();
            myDLD.LoadFun(Directory.GetCurrentDirectory() + @"\Customize.dll", "_customizeFilter@12");

            //回傳型態參數設定
            object[] Parameters = new object[] { Marshal.StringToBSTR(inputFile), Marshal.StringToBSTR(outputFile), Marshal.StringToBSTR(settingsFile) }; // 參數列
            Type[] ParameterTypes = new Type[] { typeof(IntPtr), typeof(IntPtr), typeof(IntPtr) }; // 參數資料型態
            dld.ModePass[] themode = new dld.ModePass[] { dld.ModePass.ByValue, dld.ModePass.ByValue, dld.ModePass.ByValue }; // 全部傳值呼叫
            Type Type_Return = typeof(bool);// 回傳型態

            //回傳值判斷
            bool a = (bool)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return);
            myDLD.UnLoadDll();
            myDLD = null;

            if (!a)
                return null;
            else
                return outputFile;
        }//end customizeFilter
        #endregion
    }
}
