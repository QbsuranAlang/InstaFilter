using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;

namespace GetFilterList
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("開始取得濾鏡...");
            List<string> dllList = new List<string>();
            List<string> dllSPList = new List<string>();
            List<string> dllCtrlList = new List<string>();

            string output = Directory.GetCurrentDirectory() + @"\濾鏡清單.txt";
            File.Create(output).Close();
            StreamWriter sw = new StreamWriter(output);

            sw.WriteLine("普通濾鏡：\r\n");
            GetFiles(Directory.GetCurrentDirectory() + @"\cvdllRelease\", ref dllList);
            foreach (string fileName in dllList)
            {
                string filterName = GetFilterName(fileName);
                Console.WriteLine(filterName);
                sw.WriteLine(filterName);
            }

            sw.WriteLine("\r\n======================================\r\n特殊濾鏡：\r\n");
            GetFiles(Directory.GetCurrentDirectory() + @"\cvdllSPRelease\", ref dllSPList);
            foreach (string fileName in dllSPList)
            {
                string filterName = GetFilterName(fileName);
                Console.WriteLine(filterName);
                sw.WriteLine(filterName);
            }

            sw.WriteLine("\r\n======================================\r\n可調整式濾鏡：\r\n");
            GetFiles(Directory.GetCurrentDirectory() + @"\cvdllCtrlRelease\", ref dllCtrlList);
            foreach (string fileName in dllCtrlList)
            {
                string filterName = GetFilterName(fileName);
                Console.WriteLine(filterName);
                sw.WriteLine(filterName);
            }

            sw.WriteLine("\r\n普通濾鏡：" + dllList.Count + "，特殊濾鏡：" + dllSPList.Count + "，可調整式濾鏡：" + dllCtrlList.Count);
            sw.Write("共：" + (dllList.Count + dllSPList.Count + dllCtrlList.Count));
            sw.Close();


            Console.WriteLine("完成");
        }

        //取得目錄和子目錄下所有要的檔案
        static void GetFiles(string strFilePath, ref List<string> list)
        {
            int i;
            //取得所有資料夾後, 遞迴呼叫
            string[] oDirectorys = Directory.GetDirectories(strFilePath);
            for (i = 0; i < oDirectorys.Length; i++)
                GetFiles(oDirectorys[i], ref list);

            //取得所有檔案
            string[] oFiles = System.IO.Directory.GetFiles(strFilePath);
            for (i = 0; i < oFiles.Length; i++)
                if (oFiles[i].Contains(".dll"))
                    list.Add(oFiles[i]);
        }

        public static string GetFilterName(String dll)
        {
            if (Path.GetExtension(dll) == ".if")
            {
                StreamReader sr = new StreamReader(dll);
                string filterName = sr.ReadLine();//濾鏡名稱
                string[] temp = filterName.Split(' ');
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
        }//end GetFilterName
    }
}
