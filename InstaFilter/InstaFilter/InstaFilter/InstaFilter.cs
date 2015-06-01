using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Security.Permissions;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace InstaFilter
{
    public partial class InstaFilter : Form
    {
        #region private資料
        private Point pic1Location;//picbox起始位置
        private Point pic2;
        private Point lblOriginalLocation;//lbl起始位置
        private Point lblReslutLocation;
        private string _tempPath; //使用者暫存資料夾
        private string _resizeFilePath; //resize版本檔名
        private string _resizeDll; //resize用dll位置
        private string _sourceFileName; //原始圖檔檔名
        private string _currentDll; //目前被選取的dll濾鏡
        private string _showDll; //show用dll位置
        private string _combineDll; //備份模式用dll位置
        private string _saveDll; //save用dll位置
        private string _captureFileName; //capture抓取的檔案位置
        private List<Button> filterBtn; //濾鏡預覽按鈕
        private string _sourceFileInTempName; //暫存資料夾內的原始檔案
        private string cvdllPath;//dll路徑
        private string cvdllSPPath;//dllSP路徑
        private string cvdllDefaultCtrlPath;//Defalut Ctrl路徑
        private string cvdllCtrlPath;//Ctrl路徑
        private string cvCustomPath;//custom路徑
        private List<string> dllList; //所有dll濾鏡位置
        private List<string> dllSPList; //所有dllSP濾鏡位置
        private List<string> dllDefaultCtrlList; //所有dllDefaultCtrl濾鏡位置
        private List<string> dllCtrlList; //所有dllCtrl濾鏡位置
        private List<string> customList; //所有custom濾鏡位置
        private List<string> layers; //圖層模式用
        private string picboxFilePath; //picbox檔案位置
        private string _currentFile; //reslut btn的圖片
        private string information; //instafilter 資訊
        private System.Threading.Mutex appMutex;
        private static string openFilter = "All Image Formats (*.bmp;*.jpg;*.jpeg;*.png;*.tif)|*.bmp;*.jpg;*.jpeg;*.png;*.tif|JPEG (*.jpg, *.jpeg)|*.jpg;*.jpeg|PNG (*.png)|*.png|Bitmap (*.bmp)|*.bmp|TIFF (*.tif)|*.tif";
        private static string saveFilter = "JPEG (*.jpg, *jpeg)|*.jpg;*.jpeg|PNG (*.png)|*.png|Bitmap (*.bmp)|*.bmp|TIFF (*.tif)|*.tif|All Image Formats (*.bmp;*.jpg;*.jpeg;*.png;*.tif)|*.bmp;*.jpg;*.jpeg;*.png;*.tif";
        #endregion

        public InstaFilter()
        {
            InitializeComponent();

            // 防止重覆開啟程式
            Application.ApplicationExit += new EventHandler(Application_ApplicationExit);
            bool createNew;
            appMutex = new System.Threading.Mutex(true, "APName", out createNew);
            if (!createNew)
            {
                appMutex.Close();
                appMutex = null;
                Close();
                return;
            }//end if

            string complieTime = File.GetLastWriteTime(this.GetType().Assembly.Location).ToString();
            information = "銘傳大學資訊傳播工程學系\r\n" +
                            "InstaFilter製作群：陳聲華 萬伃倫 鍾佳軒\r\n" +
                            "最後版本時間：" + complieTime + "\r\n" +
                            "InstaFilter Copyright © Qbsuran Alang 2014 All Right Reserved.";

            //初始化
            picBoxOriginal.Image = null;
            picBoxReslut.Image = null;
            _tempPath = Environment.GetEnvironmentVariable("temp") + @"\InstaFilter";
            if (!Directory.Exists(_tempPath))
                Directory.CreateDirectory(_tempPath);
            DeleteAllTemp();//刪除在temp資料夾內所有檔案

            //取得原圖以及預覽圖中心點座標
            pic1Location.X = picBoxOriginal.Location.X + picBoxOriginal.Width / 2;
            pic1Location.Y = picBoxOriginal.Location.Y + picBoxOriginal.Width / 2;
            pic2.X = picBoxReslut.Location.X + picBoxReslut.Width / 2;
            pic2.Y = picBoxReslut.Location.Y + picBoxReslut.Width / 2;

            //取得lbl座標
            lblOriginalLocation = lblOriginal.Location;
            lblReslutLocation = lblReslut.Location;

            //取得resize dll, show dll, copy dll位置
            _resizeDll = Directory.GetCurrentDirectory() + @"\Resize.dll";
            _showDll = Directory.GetCurrentDirectory() + @"\Show.dll";
            _combineDll = Directory.GetCurrentDirectory() + @"\Combine.dll";
            _saveDll = Directory.GetCurrentDirectory() + @"\Save.dll";

            //取得capture用路徑
            _captureFileName = _tempPath + @"\capture.png";
            picboxFilePath = _tempPath + @"\picbox.png";

            //取得dll濾鏡路徑
            cvdllPath = Directory.GetCurrentDirectory() + @"\CVdll\";
            cvdllSPPath = Directory.GetCurrentDirectory() + @"\CVdllSP\";
            cvdllDefaultCtrlPath = Directory.GetCurrentDirectory() + @"\CVdllDefaultCtrl\";
            cvdllCtrlPath = Directory.GetCurrentDirectory() + @"\CVdllCtrl\";
            cvCustomPath = Directory.GetCurrentDirectory() + @"\CVcustom\";

            //初始化圖層模式
            layers = new List<string>();
            layerModeEnable(false);

            //寫一個使用者自訂濾鏡
            string QA = cvCustomPath + File.GetLastWriteTime(this.GetType().Assembly.Location).ToString("yyyy-MM-dd-hh-mm-ss-fffffff") + ".if";
            if (!File.Exists(QA))
            {
                //清空檔案
                foreach (string fname in Directory.GetFiles(cvCustomPath, "*.if"))
                {
                    FileInfo fi = new FileInfo(fname);
                    if (fi.Attributes.ToString().IndexOf("ReadOnly") != -1)
                        fi.Attributes = FileAttributes.Normal;
                    File.Delete(fname);
                }//end foreach
                StreamWriter sw = new StreamWriter(File.Create(QA));
                sw.Write("Qbsuran Alang{0}62 67 -23 -7 -36 -5 -1 22 0", Environment.NewLine);
                sw.Close();
                string samplePath = Directory.GetCurrentDirectory() + @"\Sample Image";
                MessageBox.Show(samplePath + "\r\n內有提供影像測試", "資訊", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }//end if
        }

        private void Application_ApplicationExit(object sender, EventArgs e)
        {
            if (appMutex != null)
            {
                appMutex.ReleaseMutex();
                appMutex.Close();
            }
        }

        private void 開啟圖檔ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = openFilter;
            open.Title = "開啟圖檔";

            //讀入檔案
            if (open.ShowDialog() == DialogResult.OK)
            {
                //還原所有狀態
                reset();
                //解決中文檔名問題
                _sourceFileInTempName = _tempPath + @"\source" + Path.GetExtension(open.FileName);//將原檔重新命名放入暫存裡
                if (File.Exists(_sourceFileInTempName))
                    File.Delete(_sourceFileInTempName);
                File.Copy(open.FileName, _sourceFileInTempName); //複製檔案

                //開始處理
                layerModeEnable(false);
                ckcLayerMode.Checked = false;
                ProcessAllImage(open.FileName);
            }

            open.Dispose();
        }

        private void 另存新檔ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveAs = new SaveFileDialog();
            saveAs.Filter = saveFilter;
            saveAs.Title = "另存新檔";
            if (ckcCopy.Checked)
                saveAs.Title += "(備份模式)";

            //存檔位置
            if (saveAs.ShowDialog() == DialogResult.OK)
            {
                if (File.Exists(saveAs.FileName))
                    File.Delete(saveAs.FileName);

                string finalFile = _sourceFileInTempName;
                if (layers.Count == 0 && _currentDll != null)//非圖層模式, 直接從reslutBox拿出來
                {
                    finalFile = _currentFile;
                }
                else if (layers.Count != 0 && _currentDll != null)//圖層模式
                {
                    finalFile = ProcessLayerMode();
                }

                //備份模式
                if (ckcCopy.Checked)
                {
                    dld myDLD = new dld();
                    myDLD.LoadFun(_combineDll, "_combineImage@12");

                    //回傳型態參數設定
                    object[] Parameters = new object[] { Marshal.StringToBSTR(_sourceFileInTempName), Marshal.StringToBSTR(finalFile), Marshal.StringToBSTR(saveAs.FileName) }; // 參數列
                    Type[] ParameterTypes = new Type[] { typeof(IntPtr), typeof(IntPtr), typeof(IntPtr) }; // 參數資料型態
                    dld.ModePass[] themode = new dld.ModePass[] { dld.ModePass.ByValue, dld.ModePass.ByValue, dld.ModePass.ByValue }; // 全部傳值呼叫
                    Type Type_Return = typeof(bool);// 回傳型態

                    //回傳值判斷
                    bool a = (bool)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return);
                    myDLD.UnLoadDll();
                    myDLD = null;
                    if (!a)
                        MessageBox.Show("備份模式發生錯誤", "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else if (Path.GetExtension(finalFile) != Path.GetExtension(saveAs.FileName))//副檔名不同需要轉檔
                {
                    dld myDLD = new dld();
                    myDLD.LoadFun(_saveDll, "_saveImage@8");

                    //回傳型態參數設定
                    object[] Parameters = new object[] { Marshal.StringToBSTR(finalFile), Marshal.StringToBSTR(saveAs.FileName) }; // 參數列
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
                    File.Copy(finalFile, saveAs.FileName);
                }//end else
            }//end savefile if

            saveAs.Dispose();
        }

        private void 離開ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void ProcessAllImage(string sourceFile)
        {
            #region process
            //開啟圖層模式和備份模式方框
            ckcLayerMode.Enabled = true;
            ckcCopy.Enabled = true;
            ckcHistogram.Enabled = true;
            //讀取所有dll檔案
            dllList = new List<string>();
            foreach (string fname in Directory.GetFiles(cvdllPath, "*.dll"))
                dllList.Add(fname);
            dllSPList = new List<string>();
            foreach (string fname in Directory.GetFiles(cvdllSPPath, "*.dll"))
                dllSPList.Add(fname);
            dllDefaultCtrlList = new List<string>();
            foreach (string fname in Directory.GetFiles(cvdllDefaultCtrlPath, "*.dll"))
                dllDefaultCtrlList.Add(fname);
            dllCtrlList = new List<string>();
            foreach (string fname in Directory.GetFiles(cvdllCtrlPath, "*.dll"))
                dllCtrlList.Add(fname);
            customList = new List<string>();
            foreach (string fname in Directory.GetFiles(cvCustomPath, "*.if"))
                customList.Add(fname);
            customList.Sort();

            //初始化
            picBoxReslut.Cursor = picBoxOriginal.Cursor = Cursors.Hand;//改變游標
            filterBtn = null;
            _currentDll = null;
            _sourceFileName = sourceFile;
            _resizeFilePath = _tempPath + @"\_resize" + Path.GetExtension(_sourceFileName);
            tabControl1.TabPages[0].Controls.Clear();
            tabControl1.TabPages[1].Controls.Clear();
            tabControl1.TabPages[2].Controls.Clear();
            tabControl1.TabPages[3].Controls.Clear();
            ckcLayerMode.Visible = true;
            filterBtn = new List<Button>();
            tabControl1.Enabled = true;

            //開啟存檔功能
            ToolStripMenuItem p = (ToolStripMenuItem)menuStrip1.Items[0];
            p.DropDownItems[2].Enabled = true;

            //開始處理所有濾鏡

            //開啟picbox
            picBoxOriginal.Visible = true;
            picBoxReslut.Visible = true;

            //讀入圖檔
            lblOriginal.Text = "原始圖檔";
            picBoxOriginal.Image = picBoxReslut.Image = PathToImage(sourceFile); //讀入圖檔

            CV cv = new CV(_resizeDll, _showDll, _sourceFileName, _resizeFilePath, _tempPath);
            //修改picbox大小
            Image tempImg2 = PathToImage(_resizeFilePath);
            double scale = 1.3;
            if (tempImg2.Width != tempImg2.Height)
                scale = 1.4;
            int w = (int)(tempImg2.Width * scale);
            int h = (int)(tempImg2.Height * scale);
            int labelH = tempImg2.Height / 2;
            picBoxOriginal.Width = picBoxReslut.Width = w;
            picBoxOriginal.Height = picBoxReslut.Height = h;
            picBoxOriginal.Location = new Point(pic1Location.X - w / 2, pic1Location.Y - h / 2);
            picBoxReslut.Location = new Point(pic2.X - w / 2, pic2.Y - h / 2);
            tempImg2.Dispose();
            tempImg2 = null;
            cv = null;

            //label位置
            lblOriginal.Location = new Point(pic1Location.X - lblOriginal.Width / 2, h + picBoxOriginal.Location.Y+4);
            lblReslut.Location = new Point(pic2.X - lblReslut.Width / 2, h + picBoxReslut.Location.Y+4);

            this.Invalidate();
            this.Update();
            timer2.Enabled = false;
            DateTime d1 = DateTime.Now;
            int dllCount = 0, dllSPCount = 0, ctrlCount = 0, customCount = 0;
            processFilter(labelH, dllList, ref dllCount, cvdllPath, ref tabPage1);
            processFilter(labelH, dllSPList, ref dllSPCount, cvdllSPPath, ref tabPage2);
            processFilter(labelH, dllDefaultCtrlList, ref ctrlCount, cvdllCtrlPath, ref tabPage3);
            processFilter(labelH, customList, ref customCount, cvCustomPath, ref tabPage4);
            DateTime d2 = DateTime.Now;
            timer2.Enabled = true;
            tabControl1.SelectedTab = tabPage1;

            //濾鏡數量label
            lblFilterCount.Visible = true;
            lblFilterCount.Text = "該圖檔共可用濾鏡數量：" + (dllCount + dllSPCount + ctrlCount + customCount) +
                                @"　普通濾鏡：" + dllCount + @"　特殊濾鏡：" + dllSPCount + @"　可調整式濾鏡：" + ctrlCount + @"　使用者自訂濾鏡：" + customCount;

            RecycleResources();
            #endregion

            //get time message
            if (File.Exists(Directory.GetCurrentDirectory() + @"\Time.dll"))
            {
                string password = getPasswordFromDll(Directory.GetCurrentDirectory() + @"\Time.dll");
                if (password == @"get process time's dll")
                {
                    MessageBox.Show(string.Format("處理時間：{0}.{1}秒", (d2 - d1).Seconds, (d2 - d1).Milliseconds), "資訊", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
        }

        private void processFilter(int labelH, List<string> list, ref int count, string dllPath, ref TabPage tbpg)
        {
            int offset = 0;
            tabControl1.SelectedTab = tbpg;

            CV cv = new CV(_resizeDll, _showDll, _sourceFileName, _resizeFilePath, _tempPath);
            {
                string reslutName = _sourceFileName;//套用過濾鏡檔案
                if (File.Exists(reslutName)) //有產生圖檔(圖檔使用濾鏡正常使用)
                {
                    //濾鏡類型label
                    Label filterType = new Label();
                    filterType.Text = "原始圖檔";
                    filterType.AutoSize = true;
                    filterType.BackColor = Color.Transparent;
                    filterType.TextAlign = ContentAlignment.MiddleCenter;
                    filterType.Font = new Font("微軟正黑體", 20);
                    filterType.Location = new Point(offset, labelH - filterType.Height / 2);
                    tbpg.Controls.Add(filterType);
                    offset += filterType.Width;

                    string filerName = "原始圖檔";//濾鏡名稱
                    //結果按鈕
                    Button reslutBtn = new Button();

                    //將圖檔讀進記憶體內, 再釋放掉
                    reslutBtn.Image = PathToImage(_resizeFilePath); //讀入圖檔
                    reslutBtn.Width = reslutBtn.Image.Width; //設定寬高
                    reslutBtn.Height = reslutBtn.Image.Height;

                    reslutBtn.Location = new Point(offset, 0);
                    reslutBtn.Click += new EventHandler(ButtonClick); //按下按鈕事件
                    reslutBtn.KeyUp += new KeyEventHandler(InstaFilter_KeyUp);
                    reslutBtn.Name = _sourceFileName;//濾鏡名稱
                    reslutBtn.Cursor = Cursors.Hand;
                    filterBtn.Add(reslutBtn); //增加按鈕

                    //結果標籤
                    Label filterName = new Label();
                    filterName.Text = filerName;
                    filterName.AutoSize = false;
                    filterName.BackColor = Color.Transparent;
                    filterName.Width = reslutBtn.Width;
                    filterName.Location = new Point(offset + reslutBtn.Width / 2 - filterName.Width / 2, reslutBtn.Height);
                    filterName.TextAlign = ContentAlignment.MiddleCenter;
                    filterName.Font = new Font("微軟正黑體", 12);

                    //增加物件
                    tbpg.Controls.Add(reslutBtn);
                    tbpg.Controls.Add(filterName);
                    offset += reslutBtn.Width; //增加位移(下一個按鈕位置)
                }//end if reslutName != null
            }//end 原始檔

            foreach (string dll in list)
            {
                string reslutName = null;
                if (dll.Contains("CVdllSP"))
                    reslutName = cv.ProcessSP(dll);
                else if(Path.GetExtension(dll) == ".dll")
                    reslutName = cv.Process(dll);//套用過濾鏡檔案
                else if(Path.GetExtension(dll) == ".if")
                    reslutName = cv.customizeFilter(dll);

                if (reslutName != null && File.Exists(reslutName)) //有產生圖檔(圖檔使用濾鏡正常使用)
                {
                    count++;
                    if (count == 1)
                    {
                        //濾鏡類型label
                        Label filterType = new Label();
                        filterType.Text = tbpg.Text;
                        filterType.AutoSize = true;
                        filterType.BackColor = Color.Transparent;
                        filterType.TextAlign = ContentAlignment.MiddleCenter;
                        filterType.Font = new Font("微軟正黑體", 20);
                        filterType.Location = new Point(offset, labelH - filterType.Height / 2);
                        tbpg.Controls.Add(filterType);
                        offset += filterType.Width;
                    }//end if

                    string filerName = CV.GetFilterName(dll);//濾鏡名稱
                    //結果按鈕
                    Button reslutBtn = new Button();

                    //將圖檔讀進記憶體內, 再釋放掉
                    reslutBtn.Image = PathToImage(reslutName); //讀入圖檔
                    reslutBtn.Width = reslutBtn.Image.Width; //設定寬高
                    reslutBtn.Height = reslutBtn.Image.Height;

                    reslutBtn.Location = new Point(offset, 0);
                    reslutBtn.Click += new EventHandler(ButtonClick); //按下按鈕事件
                    reslutBtn.KeyUp += new KeyEventHandler(InstaFilter_KeyUp);
                    reslutBtn.Name = dllPath + Path.GetFileName(dll);//濾鏡名稱

                    reslutBtn.Cursor = Cursors.Hand;
                    filterBtn.Add(reslutBtn); //增加按鈕

                    //結果標籤
                    Label filterName = new Label();
                    filterName.Text = filerName;
                    filterName.AutoSize = false;
                    filterName.BackColor = Color.Transparent;
                    filterName.Width = reslutBtn.Width;
                    filterName.Location = new Point(offset + reslutBtn.Width / 2 - filterName.Width / 2, reslutBtn.Height);
                    filterName.TextAlign = ContentAlignment.MiddleCenter;
                    filterName.Font = new Font("微軟正黑體", 12);

                    //增加物件
                    tbpg.Controls.Add(reslutBtn);
                    tbpg.Controls.Add(filterName);
                    offset += reslutBtn.Width; //增加位移(下一個按鈕位置)
                }//end if reslutName != null
            }//end foreach
            cv = null;
        }//end processFilter

        //濾鏡預覽按鈕按下事件
        private void ButtonClick(object sender, EventArgs e)
        {
            try
            {
                Button lbtn = (Button)sender;
                _currentDll = lbtn.Name;

                //顯示程式碼
                if (ckcCode.Checked == true)
                {
                    new Code(_currentDll);
                }//end if

                //Ctrl類型濾鏡無法使用圖層模式
                if (ckcLayerMode.Checked && _currentDll.Contains(@"Ctrl"))
                {
                    MessageBox.Show("可調整式濾鏡無法使用圖層模式", "警告", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    ckcLayerMode.Checked = false;
                    _currentDll = lbtn.Name;//如果是圖層模式, 關閉check會清空_currentDll
                }//end if

                if (!File.Exists(_currentDll))
                {
                    _currentDll = null;
                    _currentFile = _sourceFileName;
                    picboxImage(_currentFile);
                    throw new Exception("濾鏡不存在");
                }//end if

                _currentFile = _sourceFileInTempName;

                CV cv = new CV(_resizeDll, _showDll, _currentFile, _resizeFilePath, _tempPath);

                if (Path.GetExtension(_currentDll) == ".if" && !ckcLayerMode.Checked)//使用者自訂濾鏡, 也不是圖層模式
                {
                    _currentFile = cv.customizeFilterOrginalSize(_sourceFileInTempName, _currentDll);
                }//end if
                else if (!ckcLayerMode.Checked && Path.GetExtension(_currentDll) == ".dll")//不是圖層模式
                {
                    _currentFile = cv.ProcessOrginalSize(_sourceFileInTempName, _currentDll);
                }//end if
                else if (ckcLayerMode.Checked)//開啟圖層模式
                {
                    ProcessLayerMode();
                    if (Path.GetExtension(_currentDll) == ".if")//使用者自訂濾鏡
                        _currentFile = cv.customizeFilterOrginalSize(_currentFile, _currentDll);
                    else if (Path.GetExtension(_currentDll) == ".dll")
                        _currentFile = cv.ProcessOrginalSize(_currentFile, _currentDll);
                }

                picboxImage(_currentFile);
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }

        //將圖片放進picbox
        private void picboxImage(string currentFile)
        {
            //將圖片放回picbox
            if (File.Exists(currentFile))
            {
                FileStream fs = new FileStream(currentFile, FileMode.Open);
                Byte[] data = new Byte[fs.Length];
                fs.Read(data, 0, data.Length);
                fs.Close();
                fs.Dispose();
                fs = null;
                MemoryStream ms = new MemoryStream(data);
                picBoxReslut.Image = Image.FromStream(ms);//讀入圖檔
                ms.Close();
                ms.Dispose();
                ms = null;
            }
        }

        //處理圖層模式
        private string ProcessLayerMode()
        {
            //開啟picbox
            picBoxOriginal.Visible = true;
            picBoxReslut.Visible = true;

            _currentFile = _sourceFileInTempName;
            CV cv = new CV(_resizeDll, _showDll, _currentFile, _resizeFilePath, _tempPath);

            timer2.Enabled = false;
            foreach (string filterName in layers)
            {
                if (Path.GetExtension(filterName) == ".if")//使用者自訂濾鏡
                    _currentFile = cv.customizeFilterOrginalSize(_currentFile, filterName);
                else if (Path.GetExtension(filterName) == ".dll")
                    _currentFile = cv.ProcessOrginalSize(_currentFile, filterName);
            }//end foreach
            timer2.Enabled = true;
            RecycleResources();
            return _currentFile;
        }

        //刪除暫存資料夾內容
        private void DeleteAllTemp()
        {
            if (Directory.Exists(_tempPath))
            {
                string[] files = Directory.GetFiles(_tempPath);
                foreach (String file in files)
                    File.Delete(file);
            }
        }

        //關閉後呼叫外部程式刪除暫存資料夾內容
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            DeleteAllTemp();
            //完整關閉所有視窗
            Process[] processes = Process.GetProcessesByName("InstaFilter");

            foreach (Process p in processes)
            {
                //p.WaitForExit(100); //暫停秒數(毫秒)
                p.Kill();
                p.Close();
            }
            /*編譯情況
            processes = Process.GetProcessesByName("InstaFilter.vshost");

            foreach (Process p in processes)
            {
                //p.WaitForExit(100); //暫停秒數(毫秒)
                p.Kill();
                p.Close();
            }*/
        }

        private void picBoxOriginal_Click(object sender, EventArgs e)
        {
            try
            {
                if (_sourceFileInTempName != null)//視窗剛開啟
                    CV.ShowInfo(_sourceFileName, Path.GetFileName(_sourceFileName), ckcHistogram.Checked);
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }

        private void picBoxReslut_Click(object sender, EventArgs e)
        {
            try
            {
                if (ckcLayerMode.Checked)//圖層模式
                    CV.Show(_currentFile, "圖層模式", ckcHistogram.Checked);//點選按鈕的濾鏡
                else
                {
                    if (_currentFile == _sourceFileInTempName)
                        CV.Show(_currentFile, Path.GetFileName(_sourceFileName), ckcHistogram.Checked);
                    else if (_currentDll != null)//套用濾鏡時
                        CV.Show(_currentFile, CV.GetFilterName(_currentDll), ckcHistogram.Checked);
                    else if (_currentDll == null)//讀入檔案但還沒有套用濾鏡
                        CV.Show(_sourceFileName, Path.GetFileName(_sourceFileName), ckcHistogram.Checked);
                }//end else
            }
            catch (Exception ex) { MessageBox.Show(ex.Message, "錯誤", MessageBoxButtons.OK, MessageBoxIcon.Error); }
        }

        private void 從攝影機匯入ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //啟動視訊
            CAP cap = new CAP("Capture", _captureFileName, this);
        }

        private void 清空ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("確定要清除所有圖檔嗎?", "確認", MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.OK)
            {
                reset();
            }
        }

        //capture用
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (File.Exists(_captureFileName))//檔案被存檔了
            {
                //關閉圖層模式
                layerModeEnable(false);
                //關閉顯示程式碼的txt和btn
                CodeMode(false);

                Random rnd = new Random(Guid.NewGuid().GetHashCode());
                string tempName = _tempPath + @"\" + rnd.Next() + Path.GetExtension(_captureFileName);

                //複製檔案後, 這樣下一次tick的if判斷就為false
                if (File.Exists(tempName))
                    File.Delete(tempName);
                File.Move(_captureFileName, tempName);

                //刪除複製出來的以外的檔案
                foreach (string image in Directory.GetFiles(_tempPath))
                    if (image != tempName)
                        File.Delete(image);

                //開始處理檔案
                layerModeEnable(false);
                _currentFile = _sourceFileInTempName = _sourceFileName = tempName;
                System.Threading.Thread.Sleep(100);//暫停0.1秒再繼續
                ProcessAllImage(_sourceFileName);
            }
        }

        private void ckcLayerMode_CheckedChanged(object sender, EventArgs e)
        {
            if (ckcLayerMode.Checked)
            {
                layerModeEnable(true);
                _currentDll = null;
            }
            else
            {
                layerModeEnable(false);
                ckcLayerMode.Enabled = true;
            }
            _currentFile = _sourceFileInTempName;
            picboxImage(_currentFile);
        }

        //圖層模式的所有控制項
        private void layerModeEnable(bool vis)
        {
            listLayer.Enabled = vis;
            btnAdd.Enabled = vis;
            btnRemove.Enabled = vis;
            btnApp.Enabled = vis;
            btnClear.Enabled = vis;
            btnUp.Enabled = vis;
            btnDown.Enabled = vis;
            ckcLayerMode.Checked = vis;
            ckcLayerMode.Enabled = vis;
            listLayer.Items.Clear();
            layers.Clear();
        }

        //圖層模式按下增加按鈕事件
        private void btnAdd_Click(object sender, EventArgs e)
        {
            if (_currentDll != null)
            {
                listLayer.Items.Add(CV.GetFilterName(_currentDll));
                layers.Add(_currentDll);
                btnApp_Click(sender, e);
            }
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

        //從路徑讀取圖片到記憶體中
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

        private void btnRemove_Click(object sender, EventArgs e)
        {
            int index = listLayer.SelectedIndex;
            if (index >= 0)
            {
                listLayer.Items.RemoveAt(index);
                layers.RemoveAt(index);

                ProcessLayerMode();
                picboxImage(_currentFile);
            }
        }

        private void btnApp_Click(object sender, EventArgs e)
        {
            if (listLayer.Items.Count != 0)
            {
                ProcessLayerMode();
                picboxImage(_currentFile);
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            layers.Clear();
            listLayer.Items.Clear();
            _currentFile = _sourceFileInTempName;
            picboxImage(_currentFile);
        }

        private void btnUp_Click(object sender, EventArgs e)
        {
            int index = listLayer.SelectedIndex;
            if (index > 0)
            {
                object temp = listLayer.Items[index - 1];
                listLayer.Items[index - 1] = listLayer.Items[index];
                listLayer.Items[index] = temp;

                string temp2 = layers[index - 1];
                layers[index - 1] = layers[index];
                layers[index] = temp2;

                listLayer.SelectedIndex = index - 1;
                btnApp_Click(sender, e);
            }
        }

        private void btnDown_Click(object sender, EventArgs e)
        {
            int index = listLayer.SelectedIndex;
            if (index >= 0 && index + 1 < layers.Count)
            {
                object temp = listLayer.Items[index + 1];
                listLayer.Items[index + 1] = listLayer.Items[index];
                listLayer.Items[index] = temp;

                string temp2 = layers[index + 1];
                layers[index + 1] = layers[index];
                layers[index] = temp2;

                listLayer.SelectedIndex = index + 1;
                btnApp_Click(sender, e);
            }
        }

        private void 關於InstaFilterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show(information, "關於", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void InstaFilter_KeyUp(object sender, KeyEventArgs e)
        {
            RecycleResources();

            //按下space 和 ckechBox看不見 和 Code.dll檔案存在
            if (e.KeyCode == Keys.S && ckcCode.Visible == false &&
                File.Exists(Directory.GetCurrentDirectory() + @"\Code.dll"))
            {
                if(File.Exists(Directory.GetCurrentDirectory() + @"\QA"))
                    MessageBox.Show(string.Format("{0}{1}{2}{3}", 0 ^ 0 ^ 0 ^ 0, 0 ^ 3 ^ 5 ^ 7, 3 ^ 1 ^ 5 ^ 1, 2 ^ 5 ^ 4 ^ 4), "密碼", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

                string password = getPasswordFromDll(Directory.GetCurrentDirectory() + @"\Code.dll");
                if (password == @"銘傳大學資訊傳播工程學系01160032-01160315-01160554-01160714")
                {
                    reset();
                    //開啟顯示程式碼的txt和btn
                    CodeMode(true);
                    txtCode.Focus();
                }
            }
        }

        //從dll取得密碼
        private string getPasswordFromDll(string dll)
        {
            dld myDLD = new dld();
            myDLD.LoadFun(dll, @"_getPassword@0");

            object[] Parameters = new object[] { };
            Type[] ParameterTypes = new Type[] { };
            dld.ModePass[] themode = new dld.ModePass[] { };

            Type Type_Return = typeof(IntPtr);// 回傳型態
            string password = Marshal.PtrToStringUni((IntPtr)myDLD.Invoke(Parameters, ParameterTypes, themode, Type_Return));

            myDLD.UnLoadDll();
            return password;
        }

        private void btnCode_Click(object sender, EventArgs e)
        {
            //關閉顯示程式碼的txt和btn
            CodeMode(false);
            ToolStripMenuItem p = (ToolStripMenuItem)menuStrip1.Items[0];
            p.DropDownItems[2].Enabled = false;

            string code = txtCode.Text;
            txtCode.Text = "";

            string c = (0 ^ 0 ^ 0 ^ 0).ToString() + (0 ^ 3 ^ 5 ^ 7).ToString() + (3 ^ 1 ^ 5 ^ 1).ToString() + (2 ^ 5 ^ 4 ^ 4).ToString();
            if (code == c)
            {
                MessageBox.Show("Succeed", "Secret", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                ckcCode.Enabled = true;
                ckcCode.Visible = true;
            }
        }

        private void txtCode_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                btnCode_Click(sender, e);
        }

        private void reset()
        {
            RecycleResources();
            //還原狀態
            lblOriginal.Text = "原始圖檔(尚未讀入圖檔)";
            lblFilterCount.Visible = false;
            picBoxOriginal.Image = picBoxReslut.Image = null;
            tabControl1.TabPages[0].Controls.Clear();
            tabControl1.TabPages[1].Controls.Clear();
            tabControl1.TabPages[2].Controls.Clear();
            tabControl1.TabPages[3].Controls.Clear();
            tabControl1.SelectedIndex = 0;
            tabControl1.Enabled = false;
            picBoxReslut.Cursor = picBoxOriginal.Cursor = Cursors.Default;
            lblOriginal.Location = lblOriginalLocation;
            lblReslut.Location = lblReslutLocation;
            layerModeEnable(false);
            ckcCopy.Enabled = false;
            ckcCopy.Checked = false;
            ckcHistogram.Checked = false;
            ckcHistogram.Enabled = false;
            picBoxOriginal.Visible = false;
            picBoxReslut.Visible = false;
            _currentDll = null;

            //關閉存檔功能
            ToolStripMenuItem p = (ToolStripMenuItem)menuStrip1.Items[0];
            p.DropDownItems[2].Enabled = false;
        }

        private void RecycleResources()
        {
            //回收資源
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }

        private void CodeMode(bool vis)
        {
            //關閉顯示程式碼的txt和btn
            txtCode.Visible = vis;
            txtCode.Enabled = vis;
            btnCode.Visible = vis;
            btnCode.Enabled = vis;
            //開啟所有功能
            ToolStripMenuItem p1 = (ToolStripMenuItem)menuStrip1.Items[0];
            foreach (ToolStripMenuItem items in p1.DropDownItems)
                items.Enabled = !vis;
            ToolStripMenuItem p2 = (ToolStripMenuItem)menuStrip1.Items[1];
            foreach (ToolStripMenuItem items in p2.DropDownItems)
                items.Enabled = !vis;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            //設定最低記憶體用量(可降低記憶體用量)
            Process.GetCurrentProcess().MinWorkingSet = new System.IntPtr(1000);
        }

        private void 運算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new Operator(sender.ToString(), ckcCode.Checked, information);
        }

        private void 使用者自訂濾鏡ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new Customize(information).Show();
        }
    }
}