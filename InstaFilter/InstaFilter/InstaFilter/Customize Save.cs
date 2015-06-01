using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace InstaFilter
{
    public partial class Customize_Save : Form
    {
        int[] values = new int[8];
        string customPath;
        public Customize_Save(string rgb, string hsv, string bc, bool isGray, int[] valueArray)
        {
            InitializeComponent();

            lblRGB.Text = rgb;
            lblHSV.Text = hsv;
            lblBC.Text = bc;
            ckcGray.Checked = isGray;
            values = valueArray;
            txtFilter.Focus();

            customPath = Directory.GetCurrentDirectory() + @"\CVcustom\";
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (txtFilter.Text == "")
                MessageBox.Show("請輸入濾鏡名稱", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
            else if (txtFilter.Text == "Qbsuran Alang")
                MessageBox.Show("無法使用該濾鏡名稱", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
            {
                try
                {
                    foreach (string file in Directory.GetFiles(customPath))
                        if (CV.GetFilterName(file) == txtFilter.Text)
                            throw new Exception("濾鏡名稱：" + txtFilter.Text + "重複");

                    string fileName = customPath + DateTime.Now.ToString("yyyy-MM-dd-hh-mm-ss-fffffff") + @".if";

                    File.Create(fileName).Close();

                    StreamWriter sw = new StreamWriter(fileName);
                    sw.WriteLine(txtFilter.Text);
                    foreach (int a in values)
                        sw.Write(a + " ");
                    if (ckcGray.Checked)
                        sw.Write("1");
                    else
                        sw.Write("0");
                    sw.Close();

                    MessageBox.Show("存檔完成", "成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); };
            }
        }

        private void txtFilter_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Enter)
                btnSave_Click(sender, e);
        }
    }
}
