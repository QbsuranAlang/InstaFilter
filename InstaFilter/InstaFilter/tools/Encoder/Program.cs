using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.Cryptography;

namespace Encoder
{
    class Program
    {
        static List<string> cppList = new List<string>();
        static byte[] key = { 137, 14, 59, 74, 146, 153, 72, 39, 71, 214, 174, 10, 218, 51, 32, 48, 189, 229, 209, 86, 151, 189, 230, 41, 140, 25, 19, 17, 78, 251, 64, 3 };
        static byte[] IV = { 82, 47, 253, 199, 56, 84, 241, 19, 63, 103, 156, 13, 26, 113, 158, 97 };
        static void Main(string[] args)
        {
            GetFiles(Directory.GetCurrentDirectory());
            Encryptor("If");
            //Decryptor("ifDeCode", "ifCode");
        }

        //取得目錄和子目錄下所有要的檔案
        static void GetFiles(string strFilePath)
        {
            int i;
            //取得所有資料夾後, 遞迴呼叫
            string[] oDirectorys = Directory.GetDirectories(strFilePath);
            for (i = 0; i < oDirectorys.Length; i++)
                GetFiles(oDirectorys[i]);

            //取得所有檔案
            string[] oFiles = System.IO.Directory.GetFiles(strFilePath);
            for (i = 0; i < oFiles.Length; i++)
                if (oFiles[i].Contains(".cpp") && !oFiles[i].Contains("tools") &&
                    !oFiles[i].Contains("cvdllDefaultCtrl") && !oFiles[i].Contains("Recovery.cpp"))
                    cppList.Add(oFiles[i]);
        }

        static void Encryptor(string dir)
        {
            //建立儲存位置
            if (!Directory.Exists(dir))
                Directory.CreateDirectory(dir);

            try
            {
                foreach (string strPath in cppList)
                {
                    string strName = Path.GetFileNameWithoutExtension(strPath); //檔名
                    string strTxt = Path.GetExtension(strPath); //副檔名

                    string strOutName = Directory.GetCurrentDirectory() + @"\" + dir + @"\" + Path.GetFileNameWithoutExtension(strPath) + @".if"; //輸出位置

                    RijndaelManaged myRijndael = new RijndaelManaged();
                    FileStream fsOut = File.Open(strOutName, FileMode.Create, FileAccess.Write);
                    FileStream fsIn = File.Open(strPath, FileMode.Open, FileAccess.Read);

                    //寫入加密檔
                    CryptoStream csDesrypt = new CryptoStream(fsOut, myRijndael.CreateEncryptor(key, IV), CryptoStreamMode.Write);
                    //新增閱讀器閱讀內容
                    BinaryReader br = new BinaryReader(fsIn);
                    //將資料寫入加密內容
                    csDesrypt.Write(br.ReadBytes((int)fsIn.Length), 0, (int)fsIn.Length);

                    csDesrypt.FlushFinalBlock();
                    csDesrypt.Close();
                    fsIn.Close();
                    fsOut.Close();
                }
            }
            catch (Exception ex) { Console.WriteLine(ex.Message); }

        }

        static void Decryptor(string dir, string source)
        {
            //解密
            if (!Directory.Exists(dir))
                Directory.CreateDirectory(dir);

            List<string> decode = new List<string>();
            foreach (string file in Directory.GetFiles(Directory.GetCurrentDirectory() + @"\" + source, "*.if"))
                decode.Add(file);

            try
            {
                foreach (string strPath in decode)
                {
                    string strName = Path.GetFileNameWithoutExtension(strPath); //檔名
                    string strTxt = Path.GetExtension(strPath); //副檔名

                    string strInName = Directory.GetCurrentDirectory() + @"\" + dir + @"\" + Path.GetFileNameWithoutExtension(strPath) + @".cpp"; //輸出位置

                    RijndaelManaged myRijndael = new RijndaelManaged();
                    FileStream fsOut = File.Open(strPath, FileMode.Open, FileAccess.Read);

                    CryptoStream csDesrypt = new CryptoStream(fsOut, myRijndael.CreateDecryptor(key, IV), CryptoStreamMode.Read);
                    StreamReader sr = new StreamReader(csDesrypt);
                    StreamWriter sw = new StreamWriter(strInName);
                    sw.Write(sr.ReadToEnd());
                    sw.Flush();
                    sw.Close();
                    sr.Close();
                    fsOut.Close();
                }
            }
            catch (Exception ex) { Console.WriteLine(ex.Message); }
        }
    }
}