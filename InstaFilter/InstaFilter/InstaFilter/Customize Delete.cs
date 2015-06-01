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
    public partial class Customize_Delete : Form
    {
        public Customize_Delete()
        {
            InitializeComponent();

            //add items
            foreach (string fname in Directory.GetFiles(Directory.GetCurrentDirectory() + @"\CVcustom", "*.if"))
            {
                string filterName = CV.GetFilterName(fname);
                if (filterName != "Qbsuran Alang")
                    checkedListBox1.Items.Add(filterName);
            }//end foreach

            if (checkedListBox1.Items.Count == 0)
                btnDel.Enabled = false;
        }

        private void btnDel_Click(object sender, EventArgs e)
        {
            if (checkedListBox1.SelectedItems.Count != 0 && MessageBox.Show("確定要刪除選取的濾鏡？", "確認", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation) == DialogResult.OK)
            {
                try
                {
                    //delete file
                    foreach (string fname in Directory.GetFiles(Directory.GetCurrentDirectory() + @"\CVcustom", "*.if"))
                    {
                        string filterName = CV.GetFilterName(fname);
                        for (int i = 0; i < checkedListBox1.CheckedIndices.Count; i++)
                            if (checkedListBox1.CheckedItems[i].ToString() == filterName)
                                File.Delete(fname);
                    }//end for

                    //delete items
                    while (checkedListBox1.CheckedItems.Count > 0)
                    {
                        checkedListBox1.Items.Remove(checkedListBox1.Items[checkedListBox1.CheckedIndices[0]]);
                    }//end while
                    MessageBox.Show("已刪除選取濾鏡", "訊息", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            }//end if MessageBOx
        }
    }
}
