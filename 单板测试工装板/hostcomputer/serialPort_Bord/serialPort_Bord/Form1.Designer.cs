using serialPort_Bord.Properties;

namespace serialPort_Bord
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.Dis_Rece_TextBox = new System.Windows.Forms.TextBox();
            this.SerialNum_ComboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SerialOption_Button = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.BuadRate_ComboBox = new System.Windows.Forms.ComboBox();
            this.SendData_Button = new System.Windows.Forms.Button();
            this.SendHex_CheckBox = new System.Windows.Forms.CheckBox();
            this.Current_Button = new System.Windows.Forms.Button();
            this.ZeroBia_CheckBox = new System.Windows.Forms.CheckBox();
            this.Reset_Button = new System.Windows.Forms.Button();
            this.Key_Button = new System.Windows.Forms.Button();
            this.HeadWare_Button = new System.Windows.Forms.Button();
            this.OpenValve_Button = new System.Windows.Forms.Button();
            this.CloseValve_Button = new System.Windows.Forms.Button();
            this.SerialPort_Entity = new System.IO.Ports.SerialPort(this.components);
            this.ClearReceDis_Button = new System.Windows.Forms.Button();
            this.ClearSendData_Button = new System.Windows.Forms.Button();
            this.Chan0MaxValve_TextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.Chan0MinValve_TextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.Chan1MinValve_TextBox = new System.Windows.Forms.TextBox();
            this.Chan1MaxValve_TextBox = new System.Windows.Forms.TextBox();
            this.Chan0Cancel_Button = new System.Windows.Forms.Button();
            this.Chan0Confirm_Button = new System.Windows.Forms.Button();
            this.SendData_TextBox = new System.Windows.Forms.TextBox();
            this.Chan1Confirm_Button = new System.Windows.Forms.Button();
            this.Chan1Cancel_Button = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.TableNumConfig_TextBox = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.SystemTag_Lable = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.TableNumConfig_Confirm_Button = new System.Windows.Forms.Button();
            this.TableNum_Cancel_Button = new System.Windows.Forms.Button();
            this.CloseValve_PictureBox = new System.Windows.Forms.PictureBox();
            this.OPenValve_PictureBox = new System.Windows.Forms.PictureBox();
            this.HeadWare_PictureBox = new System.Windows.Forms.PictureBox();
            this.Key_PictureBox = new System.Windows.Forms.PictureBox();
            this.SerialPortState_PictureBox = new System.Windows.Forms.PictureBox();
            this.Current_PictureBox = new System.Windows.Forms.PictureBox();
            this.Timer_StateUpdata = new System.Windows.Forms.Timer(this.components);
            this.SerialPort_Update = new System.Windows.Forms.Timer(this.components);
            this.label14 = new System.Windows.Forms.Label();
            this.TableNumber_TextBox = new System.Windows.Forms.TextBox();
            this.TableNnumber_Confirm_Button = new System.Windows.Forms.Button();
            this.label15 = new System.Windows.Forms.Label();
            this.IP_PORT_Confirm_Button = new System.Windows.Forms.Button();
            this.Port_Num_TextBox = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.TableNum_PictureBox = new System.Windows.Forms.PictureBox();
            this.IP_Port_PictureBox = new System.Windows.Forms.PictureBox();
            this.MainIPAddress_MaskedTextBox = new System.Windows.Forms.MaskedTextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.SubIPAddress_MaskedTextBox = new System.Windows.Forms.MaskedTextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.GetIP_PictureBox = new System.Windows.Forms.PictureBox();
            this.GetIP_Button = new System.Windows.Forms.Button();
            this.label17 = new System.Windows.Forms.Label();
            this.Rece_HexCheckBox = new System.Windows.Forms.CheckBox();
            this.AutoAdd_CheckBox = new System.Windows.Forms.CheckBox();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CloseValve_PictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.OPenValve_PictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeadWare_PictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Key_PictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SerialPortState_PictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Current_PictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TableNum_PictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.IP_Port_PictureBox)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.GetIP_PictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // Dis_Rece_TextBox
            // 
            this.Dis_Rece_TextBox.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Dis_Rece_TextBox.Location = new System.Drawing.Point(12, 12);
            this.Dis_Rece_TextBox.Multiline = true;
            this.Dis_Rece_TextBox.Name = "Dis_Rece_TextBox";
            this.Dis_Rece_TextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.Dis_Rece_TextBox.Size = new System.Drawing.Size(599, 420);
            this.Dis_Rece_TextBox.TabIndex = 0;
            // 
            // SerialNum_ComboBox
            // 
            this.SerialNum_ComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.SerialNum_ComboBox.FormattingEnabled = true;
            this.SerialNum_ComboBox.Location = new System.Drawing.Point(676, 11);
            this.SerialNum_ComboBox.Name = "SerialNum_ComboBox";
            this.SerialNum_ComboBox.Size = new System.Drawing.Size(112, 20);
            this.SerialNum_ComboBox.Sorted = true;
            this.SerialNum_ComboBox.TabIndex = 1;
            this.SerialNum_ComboBox.Click += new System.EventHandler(this.SerialNum_ComboBox_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(627, 14);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "串口号";
            // 
            // SerialOption_Button
            // 
            this.SerialOption_Button.Location = new System.Drawing.Point(713, 70);
            this.SerialOption_Button.Name = "SerialOption_Button";
            this.SerialOption_Button.Size = new System.Drawing.Size(75, 23);
            this.SerialOption_Button.TabIndex = 3;
            this.SerialOption_Button.Text = "打开串口";
            this.SerialOption_Button.UseVisualStyleBackColor = true;
            this.SerialOption_Button.Click += new System.EventHandler(this.SerialOption_Button_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(627, 42);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "波特率";
            // 
            // BuadRate_ComboBox
            // 
            this.BuadRate_ComboBox.FormattingEnabled = true;
            this.BuadRate_ComboBox.Location = new System.Drawing.Point(676, 39);
            this.BuadRate_ComboBox.Name = "BuadRate_ComboBox";
            this.BuadRate_ComboBox.Size = new System.Drawing.Size(112, 20);
            this.BuadRate_ComboBox.TabIndex = 2;
            // 
            // SendData_Button
            // 
            this.SendData_Button.Location = new System.Drawing.Point(475, 84);
            this.SendData_Button.Name = "SendData_Button";
            this.SendData_Button.Size = new System.Drawing.Size(72, 29);
            this.SendData_Button.TabIndex = 2;
            this.SendData_Button.Text = "发送";
            this.SendData_Button.UseVisualStyleBackColor = true;
            this.SendData_Button.Click += new System.EventHandler(this.SendData_Button_Click);
            // 
            // SendHex_CheckBox
            // 
            this.SendHex_CheckBox.AutoSize = true;
            this.SendHex_CheckBox.Location = new System.Drawing.Point(543, 35);
            this.SendHex_CheckBox.Name = "SendHex_CheckBox";
            this.SendHex_CheckBox.Size = new System.Drawing.Size(42, 16);
            this.SendHex_CheckBox.TabIndex = 4;
            this.SendHex_CheckBox.Text = "HEX";
            this.SendHex_CheckBox.UseVisualStyleBackColor = true;
            // 
            // Current_Button
            // 
            this.Current_Button.Location = new System.Drawing.Point(96, 106);
            this.Current_Button.Name = "Current_Button";
            this.Current_Button.Size = new System.Drawing.Size(75, 31);
            this.Current_Button.TabIndex = 8;
            this.Current_Button.Tag = "0";
            this.Current_Button.Text = "功耗测试";
            this.Current_Button.UseVisualStyleBackColor = true;
            this.Current_Button.Click += new System.EventHandler(this.Button_Click);
            // 
            // ZeroBia_CheckBox
            // 
            this.ZeroBia_CheckBox.AutoSize = true;
            this.ZeroBia_CheckBox.Location = new System.Drawing.Point(17, 289);
            this.ZeroBia_CheckBox.Name = "ZeroBia_CheckBox";
            this.ZeroBia_CheckBox.Size = new System.Drawing.Size(72, 16);
            this.ZeroBia_CheckBox.TabIndex = 13;
            this.ZeroBia_CheckBox.Text = "零偏电压";
            this.ZeroBia_CheckBox.UseVisualStyleBackColor = true;
            // 
            // Reset_Button
            // 
            this.Reset_Button.Location = new System.Drawing.Point(96, 283);
            this.Reset_Button.Name = "Reset_Button";
            this.Reset_Button.Size = new System.Drawing.Size(75, 23);
            this.Reset_Button.TabIndex = 14;
            this.Reset_Button.Tag = "5";
            this.Reset_Button.Text = "复位";
            this.Reset_Button.UseVisualStyleBackColor = true;
            this.Reset_Button.Click += new System.EventHandler(this.Button_Click);
            // 
            // Key_Button
            // 
            this.Key_Button.Location = new System.Drawing.Point(96, 151);
            this.Key_Button.Name = "Key_Button";
            this.Key_Button.Size = new System.Drawing.Size(75, 31);
            this.Key_Button.TabIndex = 10;
            this.Key_Button.Tag = "1";
            this.Key_Button.Text = "按键测试";
            this.Key_Button.UseVisualStyleBackColor = true;
            this.Key_Button.Click += new System.EventHandler(this.Button_Click);
            // 
            // HeadWare_Button
            // 
            this.HeadWare_Button.Location = new System.Drawing.Point(96, 62);
            this.HeadWare_Button.Name = "HeadWare_Button";
            this.HeadWare_Button.Size = new System.Drawing.Size(75, 32);
            this.HeadWare_Button.TabIndex = 9;
            this.HeadWare_Button.Tag = "";
            this.HeadWare_Button.Text = "硬件测试";
            this.HeadWare_Button.UseVisualStyleBackColor = true;
            this.HeadWare_Button.Click += new System.EventHandler(this.HeadWare_Button_Click);
            // 
            // OpenValve_Button
            // 
            this.OpenValve_Button.Location = new System.Drawing.Point(96, 194);
            this.OpenValve_Button.Name = "OpenValve_Button";
            this.OpenValve_Button.Size = new System.Drawing.Size(75, 31);
            this.OpenValve_Button.TabIndex = 11;
            this.OpenValve_Button.Tag = "3";
            this.OpenValve_Button.Text = "开阀测试";
            this.OpenValve_Button.UseVisualStyleBackColor = true;
            this.OpenValve_Button.Click += new System.EventHandler(this.Button_Click);
            // 
            // CloseValve_Button
            // 
            this.CloseValve_Button.Location = new System.Drawing.Point(96, 239);
            this.CloseValve_Button.Name = "CloseValve_Button";
            this.CloseValve_Button.Size = new System.Drawing.Size(75, 31);
            this.CloseValve_Button.TabIndex = 12;
            this.CloseValve_Button.Tag = "4";
            this.CloseValve_Button.Text = "关阀测试";
            this.CloseValve_Button.UseVisualStyleBackColor = true;
            this.CloseValve_Button.Click += new System.EventHandler(this.Button_Click);
            // 
            // ClearReceDis_Button
            // 
            this.ClearReceDis_Button.Location = new System.Drawing.Point(536, 451);
            this.ClearReceDis_Button.Name = "ClearReceDis_Button";
            this.ClearReceDis_Button.Size = new System.Drawing.Size(71, 29);
            this.ClearReceDis_Button.TabIndex = 8;
            this.ClearReceDis_Button.Text = "清除接收";
            this.ClearReceDis_Button.UseVisualStyleBackColor = true;
            this.ClearReceDis_Button.Click += new System.EventHandler(this.ClearReceDis_Button_Click);
            // 
            // ClearSendData_Button
            // 
            this.ClearSendData_Button.Location = new System.Drawing.Point(475, 31);
            this.ClearSendData_Button.Name = "ClearSendData_Button";
            this.ClearSendData_Button.Size = new System.Drawing.Size(62, 23);
            this.ClearSendData_Button.TabIndex = 3;
            this.ClearSendData_Button.Text = "清除发送";
            this.ClearSendData_Button.UseVisualStyleBackColor = true;
            this.ClearSendData_Button.Click += new System.EventHandler(this.ClearSendData_Button_Click);
            // 
            // Chan0MaxValve_TextBox
            // 
            this.Chan0MaxValve_TextBox.Location = new System.Drawing.Point(37, 39);
            this.Chan0MaxValve_TextBox.Name = "Chan0MaxValve_TextBox";
            this.Chan0MaxValve_TextBox.Size = new System.Drawing.Size(79, 21);
            this.Chan0MaxValve_TextBox.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 14);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(83, 12);
            this.label3.TabIndex = 11;
            this.label3.Text = "通道a功耗范围";
            // 
            // Chan0MinValve_TextBox
            // 
            this.Chan0MinValve_TextBox.Location = new System.Drawing.Point(37, 66);
            this.Chan0MinValve_TextBox.Name = "Chan0MinValve_TextBox";
            this.Chan0MinValve_TextBox.Size = new System.Drawing.Size(79, 21);
            this.Chan0MinValve_TextBox.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(7, 45);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(23, 12);
            this.label4.TabIndex = 12;
            this.label4.Text = "MAX";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 69);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(23, 12);
            this.label5.TabIndex = 13;
            this.label5.Text = "MIN";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(203, 68);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(23, 12);
            this.label6.TabIndex = 18;
            this.label6.Text = "MIN";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(204, 44);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(23, 12);
            this.label7.TabIndex = 17;
            this.label7.Text = "MAX";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(204, 14);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(83, 12);
            this.label8.TabIndex = 16;
            this.label8.Text = "通道b功耗范围";
            // 
            // Chan1MinValve_TextBox
            // 
            this.Chan1MinValve_TextBox.Location = new System.Drawing.Point(234, 66);
            this.Chan1MinValve_TextBox.Name = "Chan1MinValve_TextBox";
            this.Chan1MinValve_TextBox.Size = new System.Drawing.Size(77, 21);
            this.Chan1MinValve_TextBox.TabIndex = 8;
            // 
            // Chan1MaxValve_TextBox
            // 
            this.Chan1MaxValve_TextBox.Location = new System.Drawing.Point(234, 38);
            this.Chan1MaxValve_TextBox.Name = "Chan1MaxValve_TextBox";
            this.Chan1MaxValve_TextBox.Size = new System.Drawing.Size(77, 21);
            this.Chan1MaxValve_TextBox.TabIndex = 7;
            // 
            // Chan0Cancel_Button
            // 
            this.Chan0Cancel_Button.Location = new System.Drawing.Point(144, 66);
            this.Chan0Cancel_Button.Name = "Chan0Cancel_Button";
            this.Chan0Cancel_Button.Size = new System.Drawing.Size(41, 23);
            this.Chan0Cancel_Button.TabIndex = 19;
            this.Chan0Cancel_Button.Tag = "1";
            this.Chan0Cancel_Button.Text = "取消";
            this.Chan0Cancel_Button.UseVisualStyleBackColor = true;
            this.Chan0Cancel_Button.Click += new System.EventHandler(this.ConfigButton_Click);
            // 
            // Chan0Confirm_Button
            // 
            this.Chan0Confirm_Button.Location = new System.Drawing.Point(144, 37);
            this.Chan0Confirm_Button.Name = "Chan0Confirm_Button";
            this.Chan0Confirm_Button.Size = new System.Drawing.Size(41, 23);
            this.Chan0Confirm_Button.TabIndex = 19;
            this.Chan0Confirm_Button.Tag = "0";
            this.Chan0Confirm_Button.Text = "确认";
            this.Chan0Confirm_Button.UseVisualStyleBackColor = true;
            this.Chan0Confirm_Button.Click += new System.EventHandler(this.ConfigButton_Click);
            // 
            // SendData_TextBox
            // 
            this.SendData_TextBox.Location = new System.Drawing.Point(6, 5);
            this.SendData_TextBox.Multiline = true;
            this.SendData_TextBox.Name = "SendData_TextBox";
            this.SendData_TextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.SendData_TextBox.Size = new System.Drawing.Size(453, 121);
            this.SendData_TextBox.TabIndex = 1;
            // 
            // Chan1Confirm_Button
            // 
            this.Chan1Confirm_Button.Location = new System.Drawing.Point(340, 36);
            this.Chan1Confirm_Button.Name = "Chan1Confirm_Button";
            this.Chan1Confirm_Button.Size = new System.Drawing.Size(41, 23);
            this.Chan1Confirm_Button.TabIndex = 20;
            this.Chan1Confirm_Button.Tag = "2";
            this.Chan1Confirm_Button.Text = "确认";
            this.Chan1Confirm_Button.UseVisualStyleBackColor = true;
            this.Chan1Confirm_Button.Click += new System.EventHandler(this.ConfigButton_Click);
            // 
            // Chan1Cancel_Button
            // 
            this.Chan1Cancel_Button.Location = new System.Drawing.Point(340, 66);
            this.Chan1Cancel_Button.Name = "Chan1Cancel_Button";
            this.Chan1Cancel_Button.Size = new System.Drawing.Size(41, 23);
            this.Chan1Cancel_Button.TabIndex = 21;
            this.Chan1Cancel_Button.Tag = "3";
            this.Chan1Cancel_Button.Text = "取消";
            this.Chan1Cancel_Button.UseVisualStyleBackColor = true;
            this.Chan1Cancel_Button.Click += new System.EventHandler(this.ConfigButton_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(12, 480);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(599, 158);
            this.tabControl1.TabIndex = 6;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.SendData_TextBox);
            this.tabPage1.Controls.Add(this.SendData_Button);
            this.tabPage1.Controls.Add(this.SendHex_CheckBox);
            this.tabPage1.Controls.Add(this.ClearSendData_Button);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(591, 132);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "发送数据";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.TableNumConfig_TextBox);
            this.tabPage2.Controls.Add(this.label19);
            this.tabPage2.Controls.Add(this.SystemTag_Lable);
            this.tabPage2.Controls.Add(this.label13);
            this.tabPage2.Controls.Add(this.label12);
            this.tabPage2.Controls.Add(this.label10);
            this.tabPage2.Controls.Add(this.label11);
            this.tabPage2.Controls.Add(this.label9);
            this.tabPage2.Controls.Add(this.label8);
            this.tabPage2.Controls.Add(this.TableNumConfig_Confirm_Button);
            this.tabPage2.Controls.Add(this.Chan1Confirm_Button);
            this.tabPage2.Controls.Add(this.label5);
            this.tabPage2.Controls.Add(this.TableNum_Cancel_Button);
            this.tabPage2.Controls.Add(this.Chan1Cancel_Button);
            this.tabPage2.Controls.Add(this.label4);
            this.tabPage2.Controls.Add(this.label3);
            this.tabPage2.Controls.Add(this.label6);
            this.tabPage2.Controls.Add(this.Chan1MaxValve_TextBox);
            this.tabPage2.Controls.Add(this.Chan0MinValve_TextBox);
            this.tabPage2.Controls.Add(this.Chan0Confirm_Button);
            this.tabPage2.Controls.Add(this.Chan1MinValve_TextBox);
            this.tabPage2.Controls.Add(this.Chan0MaxValve_TextBox);
            this.tabPage2.Controls.Add(this.label7);
            this.tabPage2.Controls.Add(this.Chan0Cancel_Button);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(591, 132);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "修改配置";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // TableNumConfig_TextBox
            // 
            this.TableNumConfig_TextBox.Location = new System.Drawing.Point(424, 38);
            this.TableNumConfig_TextBox.Name = "TableNumConfig_TextBox";
            this.TableNumConfig_TextBox.Size = new System.Drawing.Size(67, 21);
            this.TableNumConfig_TextBox.TabIndex = 28;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(422, 14);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(53, 12);
            this.label19.TabIndex = 27;
            this.label19.Text = "表号长度";
            // 
            // SystemTag_Lable
            // 
            this.SystemTag_Lable.AutoSize = true;
            this.SystemTag_Lable.Location = new System.Drawing.Point(47, 99);
            this.SystemTag_Lable.Name = "SystemTag_Lable";
            this.SystemTag_Lable.Size = new System.Drawing.Size(29, 12);
            this.SystemTag_Lable.TabIndex = 25;
            this.SystemTag_Lable.Text = "就绪";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(6, 99);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(35, 12);
            this.label13.TabIndex = 26;
            this.label13.Text = "状态:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(316, 71);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(17, 12);
            this.label12.TabIndex = 22;
            this.label12.Text = "uA";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(121, 69);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(17, 12);
            this.label10.TabIndex = 22;
            this.label10.Text = "mA";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(317, 47);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(17, 12);
            this.label11.TabIndex = 22;
            this.label11.Text = "uA";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(122, 45);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(17, 12);
            this.label9.TabIndex = 22;
            this.label9.Text = "mA";
            // 
            // TableNumConfig_Confirm_Button
            // 
            this.TableNumConfig_Confirm_Button.Location = new System.Drawing.Point(424, 63);
            this.TableNumConfig_Confirm_Button.Name = "TableNumConfig_Confirm_Button";
            this.TableNumConfig_Confirm_Button.Size = new System.Drawing.Size(41, 23);
            this.TableNumConfig_Confirm_Button.TabIndex = 20;
            this.TableNumConfig_Confirm_Button.Tag = "4";
            this.TableNumConfig_Confirm_Button.Text = "确认";
            this.TableNumConfig_Confirm_Button.UseVisualStyleBackColor = true;
            this.TableNumConfig_Confirm_Button.Click += new System.EventHandler(this.ConfigButton_Click);
            // 
            // TableNum_Cancel_Button
            // 
            this.TableNum_Cancel_Button.Location = new System.Drawing.Point(471, 63);
            this.TableNum_Cancel_Button.Name = "TableNum_Cancel_Button";
            this.TableNum_Cancel_Button.Size = new System.Drawing.Size(41, 23);
            this.TableNum_Cancel_Button.TabIndex = 21;
            this.TableNum_Cancel_Button.Tag = "5";
            this.TableNum_Cancel_Button.Text = "取消";
            this.TableNum_Cancel_Button.UseVisualStyleBackColor = true;
            this.TableNum_Cancel_Button.Click += new System.EventHandler(this.ConfigButton_Click);
            // 
            // CloseValve_PictureBox
            // 
            this.CloseValve_PictureBox.Image = global::serialPort_Bord.Properties.Resources.Wait;
            this.CloseValve_PictureBox.Location = new System.Drawing.Point(34, 240);
            this.CloseValve_PictureBox.Name = "CloseValve_PictureBox";
            this.CloseValve_PictureBox.Size = new System.Drawing.Size(30, 30);
            this.CloseValve_PictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.CloseValve_PictureBox.TabIndex = 23;
            this.CloseValve_PictureBox.TabStop = false;
            // 
            // OPenValve_PictureBox
            // 
            this.OPenValve_PictureBox.Image = global::serialPort_Bord.Properties.Resources.Wait;
            this.OPenValve_PictureBox.Location = new System.Drawing.Point(34, 196);
            this.OPenValve_PictureBox.Name = "OPenValve_PictureBox";
            this.OPenValve_PictureBox.Size = new System.Drawing.Size(30, 30);
            this.OPenValve_PictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.OPenValve_PictureBox.TabIndex = 23;
            this.OPenValve_PictureBox.TabStop = false;
            // 
            // HeadWare_PictureBox
            // 
            this.HeadWare_PictureBox.Image = global::serialPort_Bord.Properties.Resources.Wait;
            this.HeadWare_PictureBox.Location = new System.Drawing.Point(34, 64);
            this.HeadWare_PictureBox.Name = "HeadWare_PictureBox";
            this.HeadWare_PictureBox.Size = new System.Drawing.Size(30, 30);
            this.HeadWare_PictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.HeadWare_PictureBox.TabIndex = 23;
            this.HeadWare_PictureBox.TabStop = false;
            // 
            // Key_PictureBox
            // 
            this.Key_PictureBox.Image = global::serialPort_Bord.Properties.Resources.Wait;
            this.Key_PictureBox.Location = new System.Drawing.Point(34, 152);
            this.Key_PictureBox.Name = "Key_PictureBox";
            this.Key_PictureBox.Size = new System.Drawing.Size(30, 30);
            this.Key_PictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.Key_PictureBox.TabIndex = 23;
            this.Key_PictureBox.TabStop = false;
            // 
            // SerialPortState_PictureBox
            // 
            this.SerialPortState_PictureBox.Image = ((System.Drawing.Image)(resources.GetObject("SerialPortState_PictureBox.Image")));
            this.SerialPortState_PictureBox.Location = new System.Drawing.Point(686, 70);
            this.SerialPortState_PictureBox.Name = "SerialPortState_PictureBox";
            this.SerialPortState_PictureBox.Size = new System.Drawing.Size(20, 20);
            this.SerialPortState_PictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.SerialPortState_PictureBox.TabIndex = 23;
            this.SerialPortState_PictureBox.TabStop = false;
            // 
            // Current_PictureBox
            // 
            this.Current_PictureBox.Image = global::serialPort_Bord.Properties.Resources.Wait;
            this.Current_PictureBox.Location = new System.Drawing.Point(34, 108);
            this.Current_PictureBox.Name = "Current_PictureBox";
            this.Current_PictureBox.Size = new System.Drawing.Size(30, 30);
            this.Current_PictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.Current_PictureBox.TabIndex = 23;
            this.Current_PictureBox.TabStop = false;
            // 
            // Timer_StateUpdata
            // 
            this.Timer_StateUpdata.Enabled = true;
            this.Timer_StateUpdata.Interval = 1000;
            this.Timer_StateUpdata.Tick += new System.EventHandler(this.Timer_StateUpdata_Tick);
            // 
            // SerialPort_Update
            // 
            this.SerialPort_Update.Interval = 500;
            this.SerialPort_Update.Tick += new System.EventHandler(this.SerialPort_Update_Tick);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label14.Location = new System.Drawing.Point(9, 22);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(35, 14);
            this.label14.TabIndex = 24;
            this.label14.Text = "表号";
            // 
            // TableNumber_TextBox
            // 
            this.TableNumber_TextBox.Font = new System.Drawing.Font("幼圆", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TableNumber_TextBox.Location = new System.Drawing.Point(59, 19);
            this.TableNumber_TextBox.Multiline = true;
            this.TableNumber_TextBox.Name = "TableNumber_TextBox";
            this.TableNumber_TextBox.Size = new System.Drawing.Size(112, 21);
            this.TableNumber_TextBox.TabIndex = 3;
            // 
            // TableNnumber_Confirm_Button
            // 
            this.TableNnumber_Confirm_Button.Location = new System.Drawing.Point(111, 54);
            this.TableNnumber_Confirm_Button.Name = "TableNnumber_Confirm_Button";
            this.TableNnumber_Confirm_Button.Size = new System.Drawing.Size(60, 27);
            this.TableNnumber_Confirm_Button.TabIndex = 4;
            this.TableNnumber_Confirm_Button.Tag = "0";
            this.TableNnumber_Confirm_Button.Text = "确定";
            this.TableNnumber_Confirm_Button.UseVisualStyleBackColor = true;
            this.TableNnumber_Confirm_Button.Click += new System.EventHandler(this.TableNnumber_Confirm_Button_Click);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label15.Location = new System.Drawing.Point(9, 102);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(35, 14);
            this.label15.TabIndex = 24;
            this.label15.Text = "主IP";
            // 
            // IP_PORT_Confirm_Button
            // 
            this.IP_PORT_Confirm_Button.Location = new System.Drawing.Point(109, 191);
            this.IP_PORT_Confirm_Button.Name = "IP_PORT_Confirm_Button";
            this.IP_PORT_Confirm_Button.Size = new System.Drawing.Size(62, 29);
            this.IP_PORT_Confirm_Button.TabIndex = 8;
            this.IP_PORT_Confirm_Button.Tag = "0";
            this.IP_PORT_Confirm_Button.Text = "确定";
            this.IP_PORT_Confirm_Button.UseVisualStyleBackColor = true;
            this.IP_PORT_Confirm_Button.Click += new System.EventHandler(this.IP_PORT_Confirm_Button_Click);
            // 
            // Port_Num_TextBox
            // 
            this.Port_Num_TextBox.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Port_Num_TextBox.Location = new System.Drawing.Point(59, 157);
            this.Port_Num_TextBox.Multiline = true;
            this.Port_Num_TextBox.Name = "Port_Num_TextBox";
            this.Port_Num_TextBox.Size = new System.Drawing.Size(52, 23);
            this.Port_Num_TextBox.TabIndex = 7;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label16.Location = new System.Drawing.Point(9, 160);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(49, 14);
            this.label16.TabIndex = 24;
            this.label16.Text = "端口号";
            // 
            // TableNum_PictureBox
            // 
            this.TableNum_PictureBox.Image = global::serialPort_Bord.Properties.Resources.Wait;
            this.TableNum_PictureBox.Location = new System.Drawing.Point(63, 51);
            this.TableNum_PictureBox.Name = "TableNum_PictureBox";
            this.TableNum_PictureBox.Size = new System.Drawing.Size(30, 30);
            this.TableNum_PictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.TableNum_PictureBox.TabIndex = 23;
            this.TableNum_PictureBox.TabStop = false;
            // 
            // IP_Port_PictureBox
            // 
            this.IP_Port_PictureBox.Image = global::serialPort_Bord.Properties.Resources.Wait;
            this.IP_Port_PictureBox.Location = new System.Drawing.Point(63, 190);
            this.IP_Port_PictureBox.Name = "IP_Port_PictureBox";
            this.IP_Port_PictureBox.Size = new System.Drawing.Size(30, 30);
            this.IP_Port_PictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.IP_Port_PictureBox.TabIndex = 23;
            this.IP_Port_PictureBox.TabStop = false;
            // 
            // MainIPAddress_MaskedTextBox
            // 
            this.MainIPAddress_MaskedTextBox.Font = new System.Drawing.Font("幼圆", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.MainIPAddress_MaskedTextBox.Location = new System.Drawing.Point(59, 99);
            this.MainIPAddress_MaskedTextBox.Mask = "000.000.000.000";
            this.MainIPAddress_MaskedTextBox.Name = "MainIPAddress_MaskedTextBox";
            this.MainIPAddress_MaskedTextBox.PromptChar = ' ';
            this.MainIPAddress_MaskedTextBox.Size = new System.Drawing.Size(112, 23);
            this.MainIPAddress_MaskedTextBox.TabIndex = 5;
            this.MainIPAddress_MaskedTextBox.Tag = "10";
            this.MainIPAddress_MaskedTextBox.Click += new System.EventHandler(this.IPAddress_MaskedTextBox_Click);
            this.MainIPAddress_MaskedTextBox.KeyUp += new System.Windows.Forms.KeyEventHandler(this.IPAddress_MaskedTextBox_KeyUP);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.AutoAdd_CheckBox);
            this.groupBox1.Controls.Add(this.TableNumber_TextBox);
            this.groupBox1.Controls.Add(this.SubIPAddress_MaskedTextBox);
            this.groupBox1.Controls.Add(this.MainIPAddress_MaskedTextBox);
            this.groupBox1.Controls.Add(this.TableNum_PictureBox);
            this.groupBox1.Controls.Add(this.IP_PORT_Confirm_Button);
            this.groupBox1.Controls.Add(this.IP_Port_PictureBox);
            this.groupBox1.Controls.Add(this.TableNnumber_Confirm_Button);
            this.groupBox1.Controls.Add(this.label14);
            this.groupBox1.Controls.Add(this.Port_Num_TextBox);
            this.groupBox1.Controls.Add(this.label18);
            this.groupBox1.Controls.Add(this.label15);
            this.groupBox1.Controls.Add(this.label16);
            this.groupBox1.Location = new System.Drawing.Point(617, 96);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(177, 226);
            this.groupBox1.TabIndex = 27;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "配置区";
            // 
            // SubIPAddress_MaskedTextBox
            // 
            this.SubIPAddress_MaskedTextBox.Font = new System.Drawing.Font("幼圆", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SubIPAddress_MaskedTextBox.Location = new System.Drawing.Point(59, 128);
            this.SubIPAddress_MaskedTextBox.Mask = "000.000.000.000";
            this.SubIPAddress_MaskedTextBox.Name = "SubIPAddress_MaskedTextBox";
            this.SubIPAddress_MaskedTextBox.PromptChar = ' ';
            this.SubIPAddress_MaskedTextBox.Size = new System.Drawing.Size(112, 23);
            this.SubIPAddress_MaskedTextBox.TabIndex = 6;
            this.SubIPAddress_MaskedTextBox.Tag = "11";
            this.SubIPAddress_MaskedTextBox.Click += new System.EventHandler(this.IPAddress_MaskedTextBox_Click);
            this.SubIPAddress_MaskedTextBox.KeyUp += new System.Windows.Forms.KeyEventHandler(this.IPAddress_MaskedTextBox_KeyUP);
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label18.Location = new System.Drawing.Point(9, 131);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(49, 14);
            this.label18.TabIndex = 24;
            this.label18.Text = "备用IP";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.GetIP_PictureBox);
            this.groupBox2.Controls.Add(this.CloseValve_Button);
            this.groupBox2.Controls.Add(this.GetIP_Button);
            this.groupBox2.Controls.Add(this.Current_Button);
            this.groupBox2.Controls.Add(this.CloseValve_PictureBox);
            this.groupBox2.Controls.Add(this.Key_Button);
            this.groupBox2.Controls.Add(this.OPenValve_PictureBox);
            this.groupBox2.Controls.Add(this.HeadWare_Button);
            this.groupBox2.Controls.Add(this.HeadWare_PictureBox);
            this.groupBox2.Controls.Add(this.OpenValve_Button);
            this.groupBox2.Controls.Add(this.Key_PictureBox);
            this.groupBox2.Controls.Add(this.Reset_Button);
            this.groupBox2.Controls.Add(this.ZeroBia_CheckBox);
            this.groupBox2.Controls.Add(this.Current_PictureBox);
            this.groupBox2.Location = new System.Drawing.Point(617, 328);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(177, 319);
            this.groupBox2.TabIndex = 28;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "测试区";
            // 
            // GetIP_PictureBox
            // 
            this.GetIP_PictureBox.Image = global::serialPort_Bord.Properties.Resources.Wait;
            this.GetIP_PictureBox.Location = new System.Drawing.Point(34, 20);
            this.GetIP_PictureBox.Name = "GetIP_PictureBox";
            this.GetIP_PictureBox.Size = new System.Drawing.Size(30, 30);
            this.GetIP_PictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.GetIP_PictureBox.TabIndex = 24;
            this.GetIP_PictureBox.TabStop = false;
            // 
            // GetIP_Button
            // 
            this.GetIP_Button.Location = new System.Drawing.Point(96, 19);
            this.GetIP_Button.Name = "GetIP_Button";
            this.GetIP_Button.Size = new System.Drawing.Size(75, 31);
            this.GetIP_Button.TabIndex = 8;
            this.GetIP_Button.Tag = "6";
            this.GetIP_Button.Text = "获取IP";
            this.GetIP_Button.UseVisualStyleBackColor = true;
            this.GetIP_Button.Click += new System.EventHandler(this.GetIP_Button_Click);
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(405, 408);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(0, 12);
            this.label17.TabIndex = 29;
            // 
            // Rece_HexCheckBox
            // 
            this.Rece_HexCheckBox.AutoSize = true;
            this.Rece_HexCheckBox.Checked = true;
            this.Rece_HexCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Rece_HexCheckBox.Location = new System.Drawing.Point(491, 458);
            this.Rece_HexCheckBox.Name = "Rece_HexCheckBox";
            this.Rece_HexCheckBox.Size = new System.Drawing.Size(42, 16);
            this.Rece_HexCheckBox.TabIndex = 4;
            this.Rece_HexCheckBox.Text = "HEX";
            this.Rece_HexCheckBox.UseVisualStyleBackColor = true;
            // 
            // AutoAdd_CheckBox
            // 
            this.AutoAdd_CheckBox.AutoSize = true;
            this.AutoAdd_CheckBox.Location = new System.Drawing.Point(6, 54);
            this.AutoAdd_CheckBox.Name = "AutoAdd_CheckBox";
            this.AutoAdd_CheckBox.Size = new System.Drawing.Size(48, 28);
            this.AutoAdd_CheckBox.TabIndex = 25;
            this.AutoAdd_CheckBox.Text = "表号\r\n自增";
            this.AutoAdd_CheckBox.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(806, 654);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.Rece_HexCheckBox);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.SerialPortState_PictureBox);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.ClearReceDis_Button);
            this.Controls.Add(this.SerialOption_Button);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.BuadRate_ComboBox);
            this.Controls.Add(this.SerialNum_ComboBox);
            this.Controls.Add(this.Dis_Rece_TextBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "单板测试工装板助手";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CloseValve_PictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.OPenValve_PictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeadWare_PictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Key_PictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SerialPortState_PictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Current_PictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TableNum_PictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.IP_Port_PictureBox)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.GetIP_PictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox Dis_Rece_TextBox;
        private System.Windows.Forms.ComboBox SerialNum_ComboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button SerialOption_Button;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox BuadRate_ComboBox;
        private System.Windows.Forms.Button SendData_Button;
        private System.Windows.Forms.CheckBox SendHex_CheckBox;
        private System.Windows.Forms.Button Current_Button;
        private System.Windows.Forms.CheckBox ZeroBia_CheckBox;
        private System.Windows.Forms.Button Reset_Button;
        private System.Windows.Forms.Button Key_Button;
        private System.Windows.Forms.Button HeadWare_Button;
        private System.Windows.Forms.Button OpenValve_Button;
        private System.Windows.Forms.Button CloseValve_Button;
        private System.IO.Ports.SerialPort SerialPort_Entity;
        private System.Windows.Forms.Button ClearReceDis_Button;
        private System.Windows.Forms.Button ClearSendData_Button;
        private System.Windows.Forms.TextBox Chan0MaxValve_TextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox Chan0MinValve_TextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox Chan1MinValve_TextBox;
        private System.Windows.Forms.TextBox Chan1MaxValve_TextBox;
        private System.Windows.Forms.Button Chan0Cancel_Button;
        private System.Windows.Forms.Button Chan0Confirm_Button;
        private System.Windows.Forms.TextBox SendData_TextBox;
        private System.Windows.Forms.Button Chan1Confirm_Button;
        private System.Windows.Forms.Button Chan1Cancel_Button;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.PictureBox Current_PictureBox;
        private System.Windows.Forms.PictureBox Key_PictureBox;
        private System.Windows.Forms.PictureBox HeadWare_PictureBox;
        private System.Windows.Forms.PictureBox OPenValve_PictureBox;
        private System.Windows.Forms.PictureBox CloseValve_PictureBox;
        private System.Windows.Forms.PictureBox SerialPortState_PictureBox;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label SystemTag_Lable;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Timer Timer_StateUpdata;
        private System.Windows.Forms.Timer SerialPort_Update;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox TableNumber_TextBox;
        private System.Windows.Forms.Button TableNnumber_Confirm_Button;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Button IP_PORT_Confirm_Button;
        private System.Windows.Forms.TextBox Port_Num_TextBox;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.PictureBox TableNum_PictureBox;
        private System.Windows.Forms.PictureBox IP_Port_PictureBox;
        private System.Windows.Forms.MaskedTextBox MainIPAddress_MaskedTextBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.CheckBox Rece_HexCheckBox;
        private System.Windows.Forms.PictureBox GetIP_PictureBox;
        private System.Windows.Forms.Button GetIP_Button;
        private System.Windows.Forms.MaskedTextBox SubIPAddress_MaskedTextBox;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox TableNumConfig_TextBox;
        private System.Windows.Forms.Button TableNumConfig_Confirm_Button;
        private System.Windows.Forms.Button TableNum_Cancel_Button;
        private System.Windows.Forms.CheckBox AutoAdd_CheckBox;
    }
}

