namespace InstaFilter
{
    partial class InstaFilter
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置 Managed 資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
        /// 修改這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(InstaFilter));
            this.lblOriginal = new System.Windows.Forms.Label();
            this.lblReslut = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.rToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.開啟圖檔ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.從攝影機匯入ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.另存新檔ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.清空ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.離開ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.運算ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.影像相加ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.影像相減ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.影像相減絕對值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pSNRToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.正片叠底ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.濾色ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.疊加OverlayToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.變暗DarkenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.變亮LightenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.colorDodgeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.加亮顏色ColorDodgeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.線性加深LinearBurnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.hardLightToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.柔光SoftLightToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.實光VividLightToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.線性光源LinearLightToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.實色疊印混和HardMixToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.排除ExclusionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pSNRToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.使用者自訂濾鏡ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.說明IToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.關於InstaFilterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.lblFilterCount = new System.Windows.Forms.Label();
            this.ckcLayerMode = new System.Windows.Forms.CheckBox();
            this.listLayer = new System.Windows.Forms.ListBox();
            this.btnAdd = new System.Windows.Forms.Button();
            this.btnRemove = new System.Windows.Forms.Button();
            this.btnApp = new System.Windows.Forms.Button();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnUp = new System.Windows.Forms.Button();
            this.btnDown = new System.Windows.Forms.Button();
            this.txtCode = new System.Windows.Forms.TextBox();
            this.btnCode = new System.Windows.Forms.Button();
            this.ckcCode = new System.Windows.Forms.CheckBox();
            this.ckcCopy = new System.Windows.Forms.CheckBox();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.ckcHistogram = new System.Windows.Forms.CheckBox();
            this.picBoxReslut = new System.Windows.Forms.PictureBox();
            this.picBoxOriginal = new System.Windows.Forms.PictureBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBoxReslut)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBoxOriginal)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblOriginal
            // 
            this.lblOriginal.BackColor = System.Drawing.Color.Transparent;
            this.lblOriginal.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblOriginal.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.lblOriginal.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblOriginal.Location = new System.Drawing.Point(96, 164);
            this.lblOriginal.Name = "lblOriginal";
            this.lblOriginal.Size = new System.Drawing.Size(231, 24);
            this.lblOriginal.TabIndex = 2;
            this.lblOriginal.Text = "原始圖檔(尚未讀入圖檔)";
            this.lblOriginal.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblReslut
            // 
            this.lblReslut.BackColor = System.Drawing.Color.Transparent;
            this.lblReslut.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.lblReslut.Location = new System.Drawing.Point(537, 164);
            this.lblReslut.Name = "lblReslut";
            this.lblReslut.Size = new System.Drawing.Size(67, 24);
            this.lblReslut.TabIndex = 3;
            this.lblReslut.Text = "效果圖";
            this.lblReslut.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.Color.Transparent;
            this.menuStrip1.Font = new System.Drawing.Font("微軟正黑體", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.rToolStripMenuItem,
            this.運算ToolStripMenuItem,
            this.說明IToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1132, 25);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // rToolStripMenuItem
            // 
            this.rToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.開啟圖檔ToolStripMenuItem,
            this.從攝影機匯入ToolStripMenuItem,
            this.另存新檔ToolStripMenuItem,
            this.清空ToolStripMenuItem,
            this.離開ToolStripMenuItem});
            this.rToolStripMenuItem.Name = "rToolStripMenuItem";
            this.rToolStripMenuItem.ShowShortcutKeys = false;
            this.rToolStripMenuItem.Size = new System.Drawing.Size(53, 21);
            this.rToolStripMenuItem.Text = "檔案&F";
            // 
            // 開啟圖檔ToolStripMenuItem
            // 
            this.開啟圖檔ToolStripMenuItem.AutoSize = false;
            this.開啟圖檔ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.Image;
            this.開啟圖檔ToolStripMenuItem.Name = "開啟圖檔ToolStripMenuItem";
            this.開啟圖檔ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.開啟圖檔ToolStripMenuItem.Size = new System.Drawing.Size(250, 22);
            this.開啟圖檔ToolStripMenuItem.Text = "開啟圖檔";
            this.開啟圖檔ToolStripMenuItem.Click += new System.EventHandler(this.開啟圖檔ToolStripMenuItem_Click);
            // 
            // 從攝影機匯入ToolStripMenuItem
            // 
            this.從攝影機匯入ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.camera;
            this.從攝影機匯入ToolStripMenuItem.Name = "從攝影機匯入ToolStripMenuItem";
            this.從攝影機匯入ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.I)));
            this.從攝影機匯入ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.從攝影機匯入ToolStripMenuItem.Text = "從攝影機匯入";
            this.從攝影機匯入ToolStripMenuItem.Click += new System.EventHandler(this.從攝影機匯入ToolStripMenuItem_Click);
            // 
            // 另存新檔ToolStripMenuItem
            // 
            this.另存新檔ToolStripMenuItem.Enabled = false;
            this.另存新檔ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.save_as;
            this.另存新檔ToolStripMenuItem.Name = "另存新檔ToolStripMenuItem";
            this.另存新檔ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
            this.另存新檔ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.另存新檔ToolStripMenuItem.Text = "另存新檔";
            this.另存新檔ToolStripMenuItem.Click += new System.EventHandler(this.另存新檔ToolStripMenuItem_Click);
            // 
            // 清空ToolStripMenuItem
            // 
            this.清空ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.clear;
            this.清空ToolStripMenuItem.Name = "清空ToolStripMenuItem";
            this.清空ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.R)));
            this.清空ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.清空ToolStripMenuItem.Text = "清空畫面";
            this.清空ToolStripMenuItem.Click += new System.EventHandler(this.清空ToolStripMenuItem_Click);
            // 
            // 離開ToolStripMenuItem
            // 
            this.離開ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.exit;
            this.離開ToolStripMenuItem.Name = "離開ToolStripMenuItem";
            this.離開ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.離開ToolStripMenuItem.Size = new System.Drawing.Size(212, 22);
            this.離開ToolStripMenuItem.Text = "離開";
            this.離開ToolStripMenuItem.Click += new System.EventHandler(this.離開ToolStripMenuItem_Click);
            // 
            // 運算ToolStripMenuItem
            // 
            this.運算ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.影像相加ToolStripMenuItem,
            this.影像相減ToolStripMenuItem,
            this.影像相減絕對值ToolStripMenuItem,
            this.pSNRToolStripMenuItem,
            this.正片叠底ToolStripMenuItem,
            this.濾色ToolStripMenuItem,
            this.疊加OverlayToolStripMenuItem,
            this.變暗DarkenToolStripMenuItem,
            this.變亮LightenToolStripMenuItem,
            this.colorDodgeToolStripMenuItem,
            this.加亮顏色ColorDodgeToolStripMenuItem,
            this.線性加深LinearBurnToolStripMenuItem,
            this.hardLightToolStripMenuItem,
            this.柔光SoftLightToolStripMenuItem,
            this.實光VividLightToolStripMenuItem,
            this.線性光源LinearLightToolStripMenuItem,
            this.實色疊印混和HardMixToolStripMenuItem,
            this.排除ExclusionToolStripMenuItem,
            this.pSNRToolStripMenuItem1,
            this.使用者自訂濾鏡ToolStripMenuItem});
            this.運算ToolStripMenuItem.Name = "運算ToolStripMenuItem";
            this.運算ToolStripMenuItem.Size = new System.Drawing.Size(57, 21);
            this.運算ToolStripMenuItem.Text = "運算&O";
            // 
            // 影像相加ToolStripMenuItem
            // 
            this.影像相加ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.add;
            this.影像相加ToolStripMenuItem.Name = "影像相加ToolStripMenuItem";
            this.影像相加ToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.影像相加ToolStripMenuItem.Text = "影像相加(Linear Dodge)";
            this.影像相加ToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 影像相減ToolStripMenuItem
            // 
            this.影像相減ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.subtract;
            this.影像相減ToolStripMenuItem.Name = "影像相減ToolStripMenuItem";
            this.影像相減ToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.影像相減ToolStripMenuItem.Text = "影像相減(Linear Subtract)";
            this.影像相減ToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 影像相減絕對值ToolStripMenuItem
            // 
            this.影像相減絕對值ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.abs;
            this.影像相減絕對值ToolStripMenuItem.Name = "影像相減絕對值ToolStripMenuItem";
            this.影像相減絕對值ToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.影像相減絕對值ToolStripMenuItem.Text = "差值(Difference)";
            this.影像相減絕對值ToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // pSNRToolStripMenuItem
            // 
            this.pSNRToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.equalizer;
            this.pSNRToolStripMenuItem.Name = "pSNRToolStripMenuItem";
            this.pSNRToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.pSNRToolStripMenuItem.Text = "影像融合(Opacity)";
            this.pSNRToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 正片叠底ToolStripMenuItem
            // 
            this.正片叠底ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.close;
            this.正片叠底ToolStripMenuItem.Name = "正片叠底ToolStripMenuItem";
            this.正片叠底ToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.正片叠底ToolStripMenuItem.Text = "正片叠底(Multiply)";
            this.正片叠底ToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 濾色ToolStripMenuItem
            // 
            this.濾色ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.arrow3_s;
            this.濾色ToolStripMenuItem.Name = "濾色ToolStripMenuItem";
            this.濾色ToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.濾色ToolStripMenuItem.Text = "濾色(Screen)";
            this.濾色ToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 疊加OverlayToolStripMenuItem
            // 
            this.疊加OverlayToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.addWeight;
            this.疊加OverlayToolStripMenuItem.Name = "疊加OverlayToolStripMenuItem";
            this.疊加OverlayToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.疊加OverlayToolStripMenuItem.Text = "疊加(Overlay)";
            this.疊加OverlayToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 變暗DarkenToolStripMenuItem
            // 
            this.變暗DarkenToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.arrow1_s;
            this.變暗DarkenToolStripMenuItem.Name = "變暗DarkenToolStripMenuItem";
            this.變暗DarkenToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.變暗DarkenToolStripMenuItem.Text = "變暗(Darken)";
            this.變暗DarkenToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 變亮LightenToolStripMenuItem
            // 
            this.變亮LightenToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.arrow1_n;
            this.變亮LightenToolStripMenuItem.Name = "變亮LightenToolStripMenuItem";
            this.變亮LightenToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.變亮LightenToolStripMenuItem.Text = "變亮(Lighten)";
            this.變亮LightenToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // colorDodgeToolStripMenuItem
            // 
            this.colorDodgeToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.arrow2_nw;
            this.colorDodgeToolStripMenuItem.Name = "colorDodgeToolStripMenuItem";
            this.colorDodgeToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.colorDodgeToolStripMenuItem.Text = "加亮顏色(Color Dodge)";
            this.colorDodgeToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 加亮顏色ColorDodgeToolStripMenuItem
            // 
            this.加亮顏色ColorDodgeToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.arrow2_n;
            this.加亮顏色ColorDodgeToolStripMenuItem.Name = "加亮顏色ColorDodgeToolStripMenuItem";
            this.加亮顏色ColorDodgeToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.加亮顏色ColorDodgeToolStripMenuItem.Text = "加深顏色(Color Burn)";
            this.加亮顏色ColorDodgeToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 線性加深LinearBurnToolStripMenuItem
            // 
            this.線性加深LinearBurnToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.arrow2_ne;
            this.線性加深LinearBurnToolStripMenuItem.Name = "線性加深LinearBurnToolStripMenuItem";
            this.線性加深LinearBurnToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.線性加深LinearBurnToolStripMenuItem.Text = "線性加深(Linear Burn)";
            this.線性加深LinearBurnToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // hardLightToolStripMenuItem
            // 
            this.hardLightToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.day;
            this.hardLightToolStripMenuItem.Name = "hardLightToolStripMenuItem";
            this.hardLightToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.hardLightToolStripMenuItem.Text = "強烈光源(Hard Light)";
            this.hardLightToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 柔光SoftLightToolStripMenuItem
            // 
            this.柔光SoftLightToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.night;
            this.柔光SoftLightToolStripMenuItem.Name = "柔光SoftLightToolStripMenuItem";
            this.柔光SoftLightToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.柔光SoftLightToolStripMenuItem.Text = "柔光(Soft Light)";
            this.柔光SoftLightToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 實光VividLightToolStripMenuItem
            // 
            this.實光VividLightToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.star;
            this.實光VividLightToolStripMenuItem.Name = "實光VividLightToolStripMenuItem";
            this.實光VividLightToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.實光VividLightToolStripMenuItem.Text = "實光(Vivid Light)";
            this.實光VividLightToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 線性光源LinearLightToolStripMenuItem
            // 
            this.線性光源LinearLightToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.toggle;
            this.線性光源LinearLightToolStripMenuItem.Name = "線性光源LinearLightToolStripMenuItem";
            this.線性光源LinearLightToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.線性光源LinearLightToolStripMenuItem.Text = "線性光源(Linear Light)";
            this.線性光源LinearLightToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 實色疊印混和HardMixToolStripMenuItem
            // 
            this.實色疊印混和HardMixToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.graph;
            this.實色疊印混和HardMixToolStripMenuItem.Name = "實色疊印混和HardMixToolStripMenuItem";
            this.實色疊印混和HardMixToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.實色疊印混和HardMixToolStripMenuItem.Text = "實色疊印混和(Hard Mix)";
            this.實色疊印混和HardMixToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 排除ExclusionToolStripMenuItem
            // 
            this.排除ExclusionToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.bstop;
            this.排除ExclusionToolStripMenuItem.Name = "排除ExclusionToolStripMenuItem";
            this.排除ExclusionToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.排除ExclusionToolStripMenuItem.Text = "排除(Exclusion)";
            this.排除ExclusionToolStripMenuItem.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // pSNRToolStripMenuItem1
            // 
            this.pSNRToolStripMenuItem1.Image = global::InstaFilter.Properties.Resources.psnr;
            this.pSNRToolStripMenuItem1.Name = "pSNRToolStripMenuItem1";
            this.pSNRToolStripMenuItem1.Size = new System.Drawing.Size(227, 22);
            this.pSNRToolStripMenuItem1.Text = "峰值信號雜訊比(PSNR)";
            this.pSNRToolStripMenuItem1.Click += new System.EventHandler(this.運算ToolStripMenuItem_Click);
            // 
            // 使用者自訂濾鏡ToolStripMenuItem
            // 
            this.使用者自訂濾鏡ToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.customize;
            this.使用者自訂濾鏡ToolStripMenuItem.Name = "使用者自訂濾鏡ToolStripMenuItem";
            this.使用者自訂濾鏡ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.使用者自訂濾鏡ToolStripMenuItem.Size = new System.Drawing.Size(227, 22);
            this.使用者自訂濾鏡ToolStripMenuItem.Text = "使用者自訂濾鏡";
            this.使用者自訂濾鏡ToolStripMenuItem.Click += new System.EventHandler(this.使用者自訂濾鏡ToolStripMenuItem_Click);
            // 
            // 說明IToolStripMenuItem
            // 
            this.說明IToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.關於InstaFilterToolStripMenuItem});
            this.說明IToolStripMenuItem.Name = "說明IToolStripMenuItem";
            this.說明IToolStripMenuItem.Size = new System.Drawing.Size(56, 21);
            this.說明IToolStripMenuItem.Text = "說明&H";
            // 
            // 關於InstaFilterToolStripMenuItem
            // 
            this.關於InstaFilterToolStripMenuItem.Image = global::InstaFilter.Properties.Resources.information;
            this.關於InstaFilterToolStripMenuItem.Name = "關於InstaFilterToolStripMenuItem";
            this.關於InstaFilterToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.H)));
            this.關於InstaFilterToolStripMenuItem.Size = new System.Drawing.Size(215, 22);
            this.關於InstaFilterToolStripMenuItem.Text = "關於 InstaFilter";
            this.關於InstaFilterToolStripMenuItem.Click += new System.EventHandler(this.關於InstaFilterToolStripMenuItem_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 800;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // lblFilterCount
            // 
            this.lblFilterCount.BackColor = System.Drawing.Color.Transparent;
            this.lblFilterCount.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblFilterCount.Font = new System.Drawing.Font("微軟正黑體", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.lblFilterCount.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblFilterCount.Location = new System.Drawing.Point(27, 656);
            this.lblFilterCount.Name = "lblFilterCount";
            this.lblFilterCount.Size = new System.Drawing.Size(1120, 24);
            this.lblFilterCount.TabIndex = 7;
            this.lblFilterCount.Text = "該圖檔共可用濾鏡數量";
            this.lblFilterCount.Visible = false;
            // 
            // ckcLayerMode
            // 
            this.ckcLayerMode.AutoSize = true;
            this.ckcLayerMode.Enabled = false;
            this.ckcLayerMode.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ckcLayerMode.Location = new System.Drawing.Point(822, 27);
            this.ckcLayerMode.Name = "ckcLayerMode";
            this.ckcLayerMode.Size = new System.Drawing.Size(92, 24);
            this.ckcLayerMode.TabIndex = 8;
            this.ckcLayerMode.Text = "圖層模式";
            this.ckcLayerMode.UseVisualStyleBackColor = true;
            this.ckcLayerMode.CheckedChanged += new System.EventHandler(this.ckcLayerMode_CheckedChanged);
            this.ckcLayerMode.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // listLayer
            // 
            this.listLayer.BackColor = System.Drawing.Color.Gainsboro;
            this.listLayer.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.listLayer.FormattingEnabled = true;
            this.listLayer.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.listLayer.ItemHeight = 20;
            this.listLayer.Location = new System.Drawing.Point(808, 60);
            this.listLayer.Name = "listLayer";
            this.listLayer.Size = new System.Drawing.Size(198, 184);
            this.listLayer.TabIndex = 10;
            this.listLayer.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // btnAdd
            // 
            this.btnAdd.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnAdd.Location = new System.Drawing.Point(827, 256);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(60, 27);
            this.btnAdd.TabIndex = 11;
            this.btnAdd.Text = "增加";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            this.btnAdd.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // btnRemove
            // 
            this.btnRemove.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnRemove.Location = new System.Drawing.Point(928, 256);
            this.btnRemove.Name = "btnRemove";
            this.btnRemove.Size = new System.Drawing.Size(60, 27);
            this.btnRemove.TabIndex = 12;
            this.btnRemove.Text = "移除";
            this.btnRemove.UseVisualStyleBackColor = true;
            this.btnRemove.Click += new System.EventHandler(this.btnRemove_Click);
            this.btnRemove.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // btnApp
            // 
            this.btnApp.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnApp.Location = new System.Drawing.Point(810, 289);
            this.btnApp.Name = "btnApp";
            this.btnApp.Size = new System.Drawing.Size(95, 27);
            this.btnApp.TabIndex = 13;
            this.btnApp.Text = "套用圖層";
            this.btnApp.UseVisualStyleBackColor = true;
            this.btnApp.Click += new System.EventHandler(this.btnApp_Click);
            this.btnApp.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // btnClear
            // 
            this.btnClear.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnClear.Location = new System.Drawing.Point(911, 289);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(95, 27);
            this.btnClear.TabIndex = 14;
            this.btnClear.Text = "清除圖層";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            this.btnClear.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // btnUp
            // 
            this.btnUp.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnUp.Location = new System.Drawing.Point(1020, 106);
            this.btnUp.Name = "btnUp";
            this.btnUp.Size = new System.Drawing.Size(30, 28);
            this.btnUp.TabIndex = 15;
            this.btnUp.Text = "↑";
            this.btnUp.UseVisualStyleBackColor = true;
            this.btnUp.Click += new System.EventHandler(this.btnUp_Click);
            this.btnUp.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // btnDown
            // 
            this.btnDown.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnDown.Location = new System.Drawing.Point(1020, 174);
            this.btnDown.Name = "btnDown";
            this.btnDown.Size = new System.Drawing.Size(30, 28);
            this.btnDown.TabIndex = 16;
            this.btnDown.Text = "↓";
            this.btnDown.UseVisualStyleBackColor = true;
            this.btnDown.Click += new System.EventHandler(this.btnDown_Click);
            this.btnDown.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // txtCode
            // 
            this.txtCode.Enabled = false;
            this.txtCode.Font = new System.Drawing.Font("微軟正黑體", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.txtCode.Location = new System.Drawing.Point(333, 260);
            this.txtCode.Name = "txtCode";
            this.txtCode.PasswordChar = '*';
            this.txtCode.Size = new System.Drawing.Size(170, 32);
            this.txtCode.TabIndex = 17;
            this.txtCode.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtCode.Visible = false;
            this.txtCode.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtCode_KeyDown);
            // 
            // btnCode
            // 
            this.btnCode.Enabled = false;
            this.btnCode.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btnCode.Location = new System.Drawing.Point(379, 293);
            this.btnCode.Name = "btnCode";
            this.btnCode.Size = new System.Drawing.Size(79, 27);
            this.btnCode.TabIndex = 18;
            this.btnCode.Text = "Secret";
            this.btnCode.UseVisualStyleBackColor = true;
            this.btnCode.Visible = false;
            this.btnCode.Click += new System.EventHandler(this.btnCode_Click);
            // 
            // ckcCode
            // 
            this.ckcCode.AutoSize = true;
            this.ckcCode.Enabled = false;
            this.ckcCode.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ckcCode.Location = new System.Drawing.Point(808, 322);
            this.ckcCode.Name = "ckcCode";
            this.ckcCode.Size = new System.Drawing.Size(108, 24);
            this.ckcCode.TabIndex = 19;
            this.ckcCode.Text = "顯示程式碼";
            this.ckcCode.UseVisualStyleBackColor = true;
            this.ckcCode.Visible = false;
            // 
            // ckcCopy
            // 
            this.ckcCopy.AutoSize = true;
            this.ckcCopy.Enabled = false;
            this.ckcCopy.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ckcCopy.Location = new System.Drawing.Point(928, 322);
            this.ckcCopy.Name = "ckcCopy";
            this.ckcCopy.Size = new System.Drawing.Size(92, 24);
            this.ckcCopy.TabIndex = 20;
            this.ckcCopy.Text = "備份模式";
            this.ckcCopy.UseVisualStyleBackColor = true;
            this.ckcCopy.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            // 
            // timer2
            // 
            this.timer2.Enabled = true;
            this.timer2.Interval = 1000;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // ckcHistogram
            // 
            this.ckcHistogram.AutoSize = true;
            this.ckcHistogram.Enabled = false;
            this.ckcHistogram.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ckcHistogram.Location = new System.Drawing.Point(928, 27);
            this.ckcHistogram.Name = "ckcHistogram";
            this.ckcHistogram.Size = new System.Drawing.Size(76, 24);
            this.ckcHistogram.TabIndex = 21;
            this.ckcHistogram.Text = "直方圖";
            this.ckcHistogram.UseVisualStyleBackColor = true;
            // 
            // picBoxReslut
            // 
            this.picBoxReslut.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.picBoxReslut.BackColor = System.Drawing.Color.Transparent;
            this.picBoxReslut.Cursor = System.Windows.Forms.Cursors.Default;
            this.picBoxReslut.Location = new System.Drawing.Point(430, 43);
            this.picBoxReslut.Name = "picBoxReslut";
            this.picBoxReslut.Size = new System.Drawing.Size(280, 280);
            this.picBoxReslut.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picBoxReslut.TabIndex = 1;
            this.picBoxReslut.TabStop = false;
            this.picBoxReslut.Visible = false;
            this.picBoxReslut.Click += new System.EventHandler(this.picBoxReslut_Click);
            // 
            // picBoxOriginal
            // 
            this.picBoxOriginal.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.picBoxOriginal.BackColor = System.Drawing.Color.Transparent;
            this.picBoxOriginal.Location = new System.Drawing.Point(71, 43);
            this.picBoxOriginal.Name = "picBoxOriginal";
            this.picBoxOriginal.Size = new System.Drawing.Size(280, 280);
            this.picBoxOriginal.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picBoxOriginal.TabIndex = 0;
            this.picBoxOriginal.TabStop = false;
            this.picBoxOriginal.Visible = false;
            this.picBoxOriginal.Click += new System.EventHandler(this.picBoxOriginal_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Enabled = false;
            this.tabControl1.Font = new System.Drawing.Font("微軟正黑體", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.tabControl1.Location = new System.Drawing.Point(31, 357);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1077, 296);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.AutoScroll = true;
            this.tabPage1.BackColor = System.Drawing.Color.Gainsboro;
            this.tabPage1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPage1.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.tabPage1.Location = new System.Drawing.Point(4, 29);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(1069, 263);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "普通濾鏡";
            // 
            // tabPage2
            // 
            this.tabPage2.AutoScroll = true;
            this.tabPage2.BackColor = System.Drawing.Color.Gainsboro;
            this.tabPage2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPage2.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.tabPage2.Location = new System.Drawing.Point(4, 29);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(1069, 249);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "特殊濾鏡";
            // 
            // tabPage3
            // 
            this.tabPage3.AutoScroll = true;
            this.tabPage3.BackColor = System.Drawing.Color.Gainsboro;
            this.tabPage3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPage3.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.tabPage3.Location = new System.Drawing.Point(4, 29);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(1069, 249);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "可調整式濾鏡";
            // 
            // tabPage4
            // 
            this.tabPage4.AutoScroll = true;
            this.tabPage4.BackColor = System.Drawing.Color.Gainsboro;
            this.tabPage4.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPage4.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.tabPage4.Location = new System.Drawing.Point(4, 29);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(1069, 249);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "使用者自訂濾鏡";
            // 
            // InstaFilter
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(1132, 686);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.ckcHistogram);
            this.Controls.Add(this.ckcCopy);
            this.Controls.Add(this.ckcCode);
            this.Controls.Add(this.btnCode);
            this.Controls.Add(this.txtCode);
            this.Controls.Add(this.btnDown);
            this.Controls.Add(this.btnUp);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.btnApp);
            this.Controls.Add(this.btnRemove);
            this.Controls.Add(this.btnAdd);
            this.Controls.Add(this.listLayer);
            this.Controls.Add(this.ckcLayerMode);
            this.Controls.Add(this.lblReslut);
            this.Controls.Add(this.lblFilterCount);
            this.Controls.Add(this.lblOriginal);
            this.Controls.Add(this.picBoxReslut);
            this.Controls.Add(this.picBoxOriginal);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "InstaFilter";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "InstaFilter";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.InstaFilter_KeyUp);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBoxReslut)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBoxOriginal)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion

        private System.Windows.Forms.PictureBox picBoxReslut;
        private System.Windows.Forms.Label lblOriginal;
        private System.Windows.Forms.Label lblReslut;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem rToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 開啟圖檔ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 另存新檔ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 離開ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 說明IToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 關於InstaFilterToolStripMenuItem;
        private System.Windows.Forms.PictureBox picBoxOriginal;
        private System.Windows.Forms.ToolStripMenuItem 從攝影機匯入ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 清空ToolStripMenuItem;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label lblFilterCount;
        private System.Windows.Forms.CheckBox ckcLayerMode;
        private System.Windows.Forms.ListBox listLayer;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnRemove;
        private System.Windows.Forms.Button btnApp;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnUp;
        private System.Windows.Forms.Button btnDown;
        private System.Windows.Forms.TextBox txtCode;
        private System.Windows.Forms.Button btnCode;
        private System.Windows.Forms.CheckBox ckcCode;
        private System.Windows.Forms.CheckBox ckcCopy;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.ToolStripMenuItem 運算ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 影像相加ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 影像相減ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 影像相減絕對值ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pSNRToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pSNRToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 使用者自訂濾鏡ToolStripMenuItem;
        private System.Windows.Forms.CheckBox ckcHistogram;
        private System.Windows.Forms.ToolStripMenuItem 正片叠底ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 濾色ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 疊加OverlayToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 變暗DarkenToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 變亮LightenToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem colorDodgeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 加亮顏色ColorDodgeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 線性加深LinearBurnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem hardLightToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 柔光SoftLightToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 線性光源LinearLightToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 實光VividLightToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 實色疊印混和HardMixToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 排除ExclusionToolStripMenuItem;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
    }
}

