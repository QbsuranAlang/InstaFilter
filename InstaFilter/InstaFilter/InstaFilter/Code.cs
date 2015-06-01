using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Security.Cryptography;

namespace InstaFilter
{
    public partial class Code : Form
    {
        static byte[] key = { 137, 14, 59, 74, 146, 153, 72, 39, 71, 214, 174, 10, 218, 51, 32, 48, 189, 229, 209, 86, 151, 189, 230, 41, 140, 25, 19, 17, 78, 251, 64, 3 };
        static byte[] IV = { 82, 47, 253, 199, 56, 84, 241, 19, 63, 103, 156, 13, 26, 113, 158, 97 };
        static string dir = Directory.GetCurrentDirectory() + @"\If\";
        private string filterName;
        FileStream fs;
        BinaryReader br;

        public Code(string _dll)
        {
            InitializeComponent();

            txtBox.Text = @"/************************************************************************" + "\r\n" +
                                    @"      InstaFilter Copyright © Qbsuran Alang 2014 All Right Reserved. " + "\r\n" +
                                    @" ************************************************************************/" + "\r\n";

            if (Path.GetExtension(_dll) == ".dll")
            {
                filterName = CV.GetFilterName(_dll);
                txtBox.Text += @"//Filter Name：" + filterName + "\r\n\r\n";

                this.Text = filterName;

                string codeName = Directory.GetCurrentDirectory() + @"\If\" + Path.GetFileNameWithoutExtension(_dll) + @".if";

                if (File.Exists(codeName))
                {
                    Decryptor(codeName);
                    Code_SizeChanged(null, null);
                    txtBox.Select(0, 0);
                    this.Show();
                }//end if
                else
                {
                    if (filterName == "備份影像")
                        MessageBox.Show("濾鏡 : " + filterName + "\r\n不提供程式碼", "抱歉", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    else
                        MessageBox.Show("濾鏡 : " + filterName + "\r\n加密檔不存在", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    this.Dispose();
                    this.Close();
                }//end else
            }//end if
            else if (Path.GetExtension(_dll) == ".if")
            {
                filterName = CV.GetFilterName(_dll);
                txtBox.Text += @"Filter Name：" + filterName + "\r\n\r\n";

                this.Text = filterName;

                StreamReader sr = new StreamReader(_dll);
                string[] temp = sr.ReadToEnd().Split(new char[] { '\r', '\n' });
                string[] data = temp[2].Split(' ');//temp[0] = filterName, temp[1] = null(\r\n斷句), temp[2] = data
                txtBox.Text += 
                    "紅色：" + data[0] + "\r\n" +
                    "綠色：" + data[1] + "\r\n" +
                    "藍色：" + data[2] + "\r\n" +
                    "色相：" + data[3] + "\r\n" +
                    "飽和度：" + data[4] + "\r\n" +
                    "明度：" + data[5] + "\r\n" +
                    "亮度：" + data[6] + "\r\n" +
                    "對比：" + data[7] + "\r\n";

                temp = null;
                data = null;
                Code_SizeChanged(null, null);
                txtBox.Select(0, 0);
                this.Show();
            }//end if
            else if (Path.GetExtension(_dll).ToLower() == ".bmp" || Path.GetExtension(_dll).ToLower() == ".jpg" || Path.GetExtension(_dll).ToLower() == ".jpeg" || Path.GetExtension(_dll).ToLower() == ".tif" || Path.GetExtension(_dll).ToLower() == ".png")
            {
                string temp = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter\bin.if";
                if (File.Exists(temp))
                    File.Delete(temp);
                File.Copy(_dll, temp);
                br = new BinaryReader(File.Open(temp, FileMode.Open, FileAccess.Read));
                
                this.Text = Path.GetFileName(_dll);
                txtBox.Text += @"File Name：" + Path.GetFileName(_dll) + "\r\n";
                txtBox.Text += @"Extension：" + Path.GetExtension(_dll) + "\r\n\r\n";

                for (int i = 0; i < 16; i++)
                    txtBox.Text += string.Format("{0:X}", i).PadLeft(4, ' ');

                getMoreInfo();

                Code_SizeChanged(null, null);
                txtBox.Select(0, 0); 
                this.Show();
            }//end if
            else
            {
                this.Dispose();
                this.Close();
            }//end else
        }

        void Decryptor(string source)
        {
            try
            {
                string strName = Path.GetFileNameWithoutExtension(source); //檔名
                string strTxt = Path.GetExtension(source); //副檔名

                RijndaelManaged myRijndael = new RijndaelManaged();
                FileStream fsOut = File.Open(source, FileMode.Open, FileAccess.Read);

                CryptoStream csDesrypt = new CryptoStream(fsOut, myRijndael.CreateDecryptor(key, IV), CryptoStreamMode.Read);
                StreamReader sr = new StreamReader(csDesrypt);
                //rihTxtCode.Text += sr.ReadToEnd();

                string line;
                while ((line = sr.ReadLine()) != "LPWSTR _stdcall getFilterName(void)")
                {
                    txtBox.Text += line + "\r\n";
                }

                txtBox.Text += "LPWSTR _stdcall getFilterName(void)\r\n" +
                                   "{\r\n" + 
                                   "\treturn _T(\"" + filterName + "\");\r\n" +
                                   "}//end getFIlterName";

                //skip some information
                line = sr.ReadLine();
                line = sr.ReadLine();
                line = sr.ReadLine();

                txtBox.Text += "\r\n" + sr.ReadToEnd();

                sr.Close();
                fsOut.Close();
            }
            catch (Exception ex) { Console.WriteLine(ex.Message); }
        }

        private void Code_SizeChanged(object sender, EventArgs e)
        {
            txtBox.Width = this.ClientSize.Width;
            txtBox.Height = this.ClientSize.Height;
            txtBox.Location = new Point(0, 0);
        }

        private void rihTxtCode_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.C)
                Clipboard.SetText(txtBox.SelectedText);
        }

        private bool getMoreInfo()
        {
            try
            {
                byte[] buffer = new byte[1024];

                bool isEnd = false;
                br.Read(buffer, 0, buffer.Length);
                if (br.BaseStream.Position > br.BaseStream.Length)
                    isEnd = true;

                int i = 0;
                foreach (byte b in buffer)
                {
                    if ((i++ % 16) == 0)
                    {
                        txtBox.Text += Environment.NewLine;
                        i %= 16;
                    }//end if
                    txtBox.Text += string.Format("{0:X}", b).PadLeft(2, '0').PadLeft(4, ' ');
                }//end foreach

                if (isEnd)
                {
                    txtBox.KeyUp -= new KeyEventHandler(txtBox_KeyUp);
                    txtBox.Text += "\r\n  結束讀取";
                    txtBox.Select(0, 0);
                    MessageBox.Show("讀取結束", "訊息", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return true;
                }//end if
                else
                    txtBox.Text += "\r\n  前1024個byte，按Enter讀取下一個1024個byte，按下R讀取3個1024個byte\r\n";

                buffer = null;

                return isEnd;
            }
            catch (Exception) { MessageBox.Show("超出緩衝區大小", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); return true; }
        }

        private void txtBox_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                this.getMoreInfo();
            else if (e.KeyCode == Keys.R)
                for (int i = 0 ; i < 2 && !getMoreInfo() ; i++);
        }

        private void Code_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (br != null)
            {
                br.Close();
                br.Dispose();
            }
            if (fs != null)
            {
                fs.Close();
                fs.Dispose();
            }
            this.Dispose();
            this.Close();
        }
    }
}
