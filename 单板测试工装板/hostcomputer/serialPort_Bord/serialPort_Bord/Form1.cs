using System;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Text.RegularExpressions;
using serialPort_Bord.Properties;
using System.Configuration;
using System.Net;
using System.Diagnostics;

namespace serialPort_Bord
{
    public partial class Form1 : Form
    {
        public struct CurrentTestRangeTypeDef   // 电流测试范围值结构体
        {
            public double Chan0MaxValve;        // 通道0最大值(显示为通道a)
            public double Chan0MinValve;        // 通道0最小值
            public double Chan1MaxValve;        // 通道1最大值(显示为通道b)
            public double Chan1MinValve;        // 通道1最小值
            public bool CurrentTestDet;         // 电流测试指令(判断当前接收的内容是否为电流值)
        }

        const byte ConfigTableNum   = 0XFB;     // 配置表号
        const byte ConfigIPAndPort  = 0XFA;     // 配置IP和端口
        const byte GetIPAndPortDet  = 0XFC;     // 获取IP和端口
        const byte ReturnSuccess    = 0XFF;     // 返回成功
        const byte FrameTail        = 0X16;     // 帧尾
        const byte HeadWareDet      = 0XFD;     // 测试硬件(按键和阀门)


        CurrentTestRangeTypeDef CurrentTestStruct;  // 实例化电流测试结构体
        readonly CRC16 Crc16 = new CRC16();              // 实例化Cre16校验类
        readonly SerialPortHelper SerialPortHelper = new SerialPortHelper();
        byte TableNumBitLength = 0;
        /// <summary>
        /// 初始化UI
        /// </summary>
        public Form1()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
        }

        /// <summary>
        /// 页面初始配置
        /// </summary>
        private void FormInit()
        {
            // 常用串口波特率
            string[] BuadRate = { "1200", "2400", "4800", "9600", "14400", "19200", "38400", "56000", "115200", "128000", "230400", "460800" };
            foreach (var item in BuadRate)      // 将波特率添加到波特率下拉框中
            {
                BuadRate_ComboBox.Items.Add(item);
            }
            BuadRate_ComboBox.SelectedIndex = 1;    // 选择默认串口波特
            SerialPort_Entity.DataReceived += new SerialDataReceivedEventHandler(Port_ReceData);    // 创建串口接收事件
            LoadApp_CurrentConfig();                // 配置基本数据

            CurrentTestStruct.CurrentTestDet = false;   // 将电流检测标志位设置为false


            // 现在只有功耗测试功能，暂时先关闭其他按键
            HeadWare_Button.Enabled = false;
            Key_Button.Enabled = false;
            OpenValve_Button.Enabled = false;
            CloseValve_Button.Enabled = false;

        }
        /// <summary>
        /// 串口接收事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Port_ReceData(object sender, EventArgs e)
        {
            SerialPort_Entity.Encoding = System.Text.Encoding.GetEncoding("GB2312");        // 将串口数据编码格式修改为GB2312
            if(!Rece_HexCheckBox.Checked)       // 判断当前接收是否为接收16进制
            { 
                string str = SerialPort_Entity.ReadExisting();      // 读取串口数据并存储到str字符串中
                Dis_Rece_TextBox.AppendText(str);                   // 添加展示到接收框中
                if (CurrentTestStruct.CurrentTestDet == true)       
                {
                    JudgeCurrentValve(str);                 // 判段电流是否在指定范围内
                }
            }
            else
            {
                Port_Rece_HexData(SerialPort_Entity);       // 接收16进制数据
            }
        }

        public byte[] ReceBuffer = new byte[100];           // 创建缓存集合
        int BuffPtr = 0;                                    // 数据长度

        /// <summary>
        /// 串口接收16进制数据
        /// </summary>
        /// <param name="serialPort"></param>串口名
        public void Port_Rece_HexData(SerialPort serialPort)    
        {
            int len = serialPort.BytesToRead;       //获取可以读取的字节数
            byte[] buff = new byte[len];            //创建缓存数据数组
            serialPort.Read(buff, 0, len);          //把数据读取到buff数组
            try
            {
                lock (ReceBuffer)
                {
                    Array.Copy(buff, 0, ReceBuffer, BuffPtr, len);  // 将当前串口收内容存到缓存区
                    BuffPtr += len;
                }
                if(buff.Length != 0)
                { 
                    if (buff[buff.Length - 1] == FrameTail)      // 判断最后一个字节是否为0x16
                    {
                        Check_Data();       // 校验数据
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(Convert.ToString(ex));
                MessageBox.Show("表端配置不正确，请检查表端是否为配置模式", "ERROR");
            }
        }
        /// <summary>
        /// 数据校验
        /// </summary>
        public void Check_Data()
        {
            lock(ReceBuffer)        // 锁住该数组，保证数组在使用时不会被再次使用
            {
                for (int i = 0; i < BuffPtr; i++)   // 输出接收到的数据
                {
                    Dis_Rece_TextBox.AppendText(string.Format("{0:X2} ", ReceBuffer[i]));
                }
                Dis_Rece_TextBox.AppendText("\r\n");    // 输出换行

                if (Crc16.CRC16_Check(ReceBuffer, BuffPtr) == false)      // 判断校验数据是否成功
                {
                    Dis_Rece_TextBox.AppendText("校验数据错误，请重试\r\n");
                }
                else
                {
                    if (ReceBuffer[9] == ConfigTableNum)      // 修改表号
                    {
                        if (ReceBuffer[10] == ReturnSuccess) // 解析指令结果
                        {
                            byte TableLen = 0;
                            if(TableNumBitLength % 2 == 0)
                            {
                                TableLen = (byte)(TableNumBitLength / 2);
                            }
                            else
                            {
                                TableLen = (byte)(TableNumBitLength / 2 + 1);
                            }
                            byte[] temp = new byte[TableLen];
                            Array.Copy(ReceBuffer, TableLen, temp, 0, TableLen);
                            TableNum_PictureBox.Image = Resources.Acces;
                            string TableNumStr = SerialPortHelper.BCDToString(temp);
                            Dis_Rece_TextBox.AppendText("表号修改成功,表号为: " + TableNumStr + "\r\n");
                        }
                        else
                        {
                            Dis_Rece_TextBox.AppendText("表号修改失败\r\n");
                            TableNum_PictureBox.Image = Resources.Error;
                        }
                    }
                    else if (ReceBuffer[9] == ConfigIPAndPort) // 修改IP和端口号
                    {
                        if (ReceBuffer[10] == ReturnSuccess) // 解析指令结果
                        {
                            Dis_Rece_TextBox.AppendText("IP和端口号修改成功\r\n");
                            IP_Port_PictureBox.Image = Resources.Acces;
                        }
                        else
                        {
                            Dis_Rece_TextBox.AppendText("IP和端口号修改失败\r\n");
                            IP_Port_PictureBox.Image = Resources.Error;
                        }
                    }
                    else if (ReceBuffer[9] == GetIPAndPortDet) // 获取IP地址和端口号
                    {
                        GetIPAndPort(ReceBuffer);
                        GetIP_PictureBox.Image = Resources.Acces;
                    }
                    else if (ReceBuffer[9] == HeadWareDet)  // 校验按键和阀门
                    {
                        //
                    }
                }
                Array.Clear(ReceBuffer, 0, BuffPtr);
                BuffPtr = 0;
            }
        }
        /// <summary>
        /// 在数组中获取IP地址和端口号并做输出
        /// </summary>
        /// <param name="Arr"></param> 被读取的IP地址数组
        public void GetIPAndPort(byte[] Arr)
        {
            byte[] MainIP = new byte[4];            // 主IP
            byte[] SubIP  = new byte[4];            // 备用IP
            byte[] PortNumArr = new byte[2];        // 端口号
            Array.Copy(Arr, 10, MainIP, 0, 4);      // 获取主IP
            Array.Copy(Arr, 14, SubIP, 0, 4);       // 获取备用IP
            Array.Copy(Arr, 18, PortNumArr, 0, 2);  // 获取端口号

            Dis_Rece_TextBox.AppendText("主IP地址为   :");
            SerialPortHelper.PrintIP(MainIP, Dis_Rece_TextBox);      // 输出主IP地址

            Dis_Rece_TextBox.AppendText("备用IP地址为:");
            SerialPortHelper.PrintIP(SubIP, Dis_Rece_TextBox);       // 输出备用IP地址

            ushort PortNum = BitConverter.ToUInt16(PortNumArr, 0);          // 将端口号数组转换成十进制数据
            Dis_Rece_TextBox.AppendText("端口号为" + PortNum + "\r\n");     // 在文本框中输出端口号
            
        }

        /// <summary>
        /// 判断电流是否超过阀值
        /// </summary>
        /// <param name="str"></param>
        public void JudgeCurrentValve(string str)
        {
            double CurrentValve = Crc16.GetStrOnDig(str); // 获取电流值
            if (CurrentValve == -1)  // 无电流值直接退出函数
            {
                return;
            }
            int tag = str.IndexOf("a"); // 寻找a字符
            if (tag != -1)  // 判断是否存在a字符，存在则进入判断， 即寻找通道
            {
                // 判断当前值是否大于或小于正常值
                if (CurrentValve >= CurrentTestStruct.Chan0MaxValve)
                {
                    Dis_Rece_TextBox.AppendText("功耗测试未通过,电流过大!!!\r\n");
                    Current_PictureBox.Image = Resources.Error;
                }
                else if (CurrentValve < CurrentTestStruct.Chan0MinValve)
                {
                    Dis_Rece_TextBox.AppendText("功耗测试未通过,电流过小!!!\r\n");
                    Current_PictureBox.Image = Resources.Error;
                }
                else
                {
                    Dis_Rece_TextBox.AppendText("功耗测试通过,电流正常!!!\r\n");
                    Current_PictureBox.Image = Resources.Acces;
                }
            }
            else // 不存在则继续寻找b字符，寻找通道1
            {
                tag = str.IndexOf("b");
                if (tag != -1)
                {
                    if (CurrentValve >= CurrentTestStruct.Chan1MaxValve)
                    {
                        Dis_Rece_TextBox.AppendText("功耗测试未通过,电流过大!!!\r\n");
                        Current_PictureBox.Image = Resources.Error;
                    }
                    else if (CurrentValve < CurrentTestStruct.Chan1MinValve)
                    {
                        Dis_Rece_TextBox.AppendText("功耗测试未通过,电流过小!!!\r\n");
                        Current_PictureBox.Image = Resources.Error;
                    }
                    else
                    {
                        Dis_Rece_TextBox.AppendText("功耗测试通过,电流正常!!!\r\n");
                        Current_PictureBox.Image = Resources.Acces;
                    }
                }
            }
            Dis_Rece_TextBox.AppendText("---------------------------------\r\n");
            CurrentTestStruct.CurrentTestDet = false;
        }

        

        /// <summary>
        /// 串口配置写入
        /// </summary>
        /// <param name="serialPort"></param>
        private void SerialConfig(SerialPort serialPort)
        {
            serialPort.PortName = SerialNum_ComboBox.Text;                      // 配置串口名称
            serialPort.BaudRate = Convert.ToInt32(BuadRate_ComboBox.Text);      // 配置串口波特率
            serialPort.DataBits = 8;            // 8位数据位        // 配置串口数据位
            serialPort.StopBits = (StopBits)1;  // 1位停止位        // 配置串口停止位
            serialPort.Parity = 0;              // 无校验位         // 配置串口校验位
        }
        /// <summary>
        /// 窗口加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            FormInit();
            SerialPortHelper.GetSerialName(SerialNum_ComboBox);
        }
        /// <summary>
        /// 串口开关按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SerialOption_Button_Click(object sender, EventArgs e)
        {
            if (SerialNum_ComboBox.Text == "")
            {
                MessageBox.Show("串口名称未选择", "ERROR");
                return;
            }
            // 判断串口是否被打开
            if (!SerialPort_Entity.IsOpen)
            {
                try
                {
                    SerialPort_Entity.Close();
                    SerialConfig(SerialPort_Entity);
                    SerialPort_Entity.Open();
                    SerialOption_Button.Text = "关闭串口";
                    SerialPort_Update.Start();
                    SerialPortState_PictureBox.Image = Resources.connect;
                    SerialNum_ComboBox.Enabled = false;
                    BuadRate_ComboBox.Enabled = false;
                }
                catch (Exception)
                {
                    if (SerialPort_Entity.IsOpen)
                    {
                        SerialPort_Entity.Close();
                        SerialOption_Button.Text = "打开串口";
                        SerialNum_ComboBox.Enabled = true;
                        BuadRate_ComboBox.Enabled = true;
                        SerialPortState_PictureBox.Image = Resources.notConnect;
                    }
                    else
                    {
                        MessageBox.Show("串口打开失败，可能端口已被占用", "提示");
                        SerialOption_Button.Text = "打开串口";
                        SerialPortState_PictureBox.Image = Resources.notConnect;
                    }
                }
            }
            else if (SerialPort_Entity.IsOpen)
            {
                try
                {
                    SerialPort_Entity.Close();
                    SerialOption_Button.Text = "打开串口";
                    SerialNum_ComboBox.Enabled = true;
                    BuadRate_ComboBox.Enabled = true;
                    SerialPortState_PictureBox.Image = Resources.notConnect;

                }
                catch (Exception)
                {
                    MessageBox.Show("关闭串口失败,请重试", "提示");
                }

            }
        }
        /// <summary>
        /// 串口名称下拉框点击事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SerialNum_ComboBox_Click(object sender, EventArgs e)
        {
            SerialNum_ComboBox.Items.Clear();       
            SerialPortHelper.GetSerialName(SerialNum_ComboBox);
        }

        /// <summary>
        /// 测试按钮事件，通过tag属性区分按键
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click(object sender, EventArgs e)
        {
            Button MyButton = (Button)(sender);
            int Flag = Convert.ToInt32(MyButton.Tag);
            byte[] TestDetArr = { 0XAF, 0X00, 0X00, 0X5F, 0X68 };
            switch (Flag)
            {
                case 0:
                    TestDetArr[1] = 0XBC;
                    CurrentTestStruct.CurrentTestDet = true;
                    break;
                case 1:
                    TestDetArr[1] = 0XDF;
                    break;
                case 3:
                    TestDetArr[1] = 0XB1;
                    break;
                case 4:
                    TestDetArr[1] = 0XB2;
                    break;
                case 5:
                    TestDetArr[1] = 0XCC;
                    if (ZeroBia_CheckBox.Checked)
                    {
                        TestDetArr[2] = 0X01;
                    }
                    ZeroBia_CheckBox.Checked = false;
                    break;
            }
            Rece_HexCheckBox.Checked = false;
            SerialPortHelper.SendHex(SerialPort_Entity, TestDetArr);
        }
        

        

        /// <summary>
        /// 清除接收区内容
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ClearReceDis_Button_Click(object sender, EventArgs e)
        {
            Dis_Rece_TextBox.Clear();
            if (Current_PictureBox.Image != Resources.Wait)
            {
                Current_PictureBox.Image = Resources.Wait;
            }
            if (Key_PictureBox.Image != Resources.Wait)
            {
                Key_PictureBox.Image = Resources.Wait;
            }
            if (HeadWare_PictureBox.Image != Resources.Wait)
            {
                HeadWare_PictureBox.Image = Resources.Wait;
            }
            if (OPenValve_PictureBox.Image != Resources.Wait)
            {
                OPenValve_PictureBox.Image = Resources.Wait;
            }
            if (CloseValve_PictureBox.Image != Resources.Wait)
            {
                CloseValve_PictureBox.Image = Resources.Wait;
            }
            if(TableNum_PictureBox.Image != Resources.Wait)
            {
                TableNum_PictureBox.Image = Resources.Wait;
            }
            if(IP_Port_PictureBox.Image != Resources.Wait)
            {
                IP_Port_PictureBox.Image = Resources.Wait;
            }
            if(GetIP_PictureBox.Image != Resources.Wait)
            {
                GetIP_PictureBox.Image = Resources.Wait;
            }
        }

        /// <summary>
        /// 发送数据按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SendData_Button_Click(object sender, EventArgs e)
        {
            if (SerialPort_Entity.IsOpen)
            {
                try
                {
                    if (!SendHex_CheckBox.Checked)
                    {
                        SerialPortHelper.SendStr(SerialPort_Entity, SendData_TextBox);
                    }
                    else
                    {
                        byte[] HexArr = SerialPortHelper.HexStringToByteArray(SendData_TextBox.Text);
                        SerialPortHelper.SendHex(SerialPort_Entity, HexArr);
                    }
                }
                catch (Exception)
                {

                    MessageBox.Show("请输入数据内容", "提示");
                }
            }
            else
            {
                MessageBox.Show("未打开串口", "提示");
            }
        }
        
        /// <summary>
        /// 清除发送数据文本框的内容
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ClearSendData_Button_Click(object sender, EventArgs e)
        {
            SendData_TextBox.Clear();
        }
        /// <summary>
        /// 状态更新计时器
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Timer_StateUpdata_Tick(object sender, EventArgs e)
        {
            Timer_StateUpdata.Stop();
            if (SystemTag_Lable.Text != "就绪")
            {
                SystemTag_Lable.Text = "就绪";
            }

        }
       

        /// <summary>
        /// 串口状态更新定时器
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SerialPort_Update_Tick(object sender, EventArgs e)
        {
            if (SerialOption_Button.Text == "关闭串口")
            {
                string[] portNames = SerialPort.GetPortNames();     // 获取串口名
                if (Array.IndexOf(portNames, SerialNum_ComboBox.Text) == -1)
                {
                    SerialPort_Entity.Close();
                    SerialOption_Button.Text = "打开串口";
                    SerialPortState_PictureBox.Image = Resources.notConnect;
                    SerialNum_ComboBox_Click(sender, e);
                    Dis_Rece_TextBox.AppendText("\r\n串口断开,请重新连接\r\n");
                    SerialPort_Update.Stop();
                    SerialNum_ComboBox.Enabled = true;
                    BuadRate_ComboBox.Enabled = true;
                }
            }
        }
        /// <summary>
        /// 写入默认数据
        /// </summary>
        /// <param name="Arr"></param>
        public void ConDefValve(byte[] Arr)
        {
            byte[] tempArr = { 0X68, 0X00, 0XE1, 0XA1, 0XAA, 0XAA, 0XAA, 0XAA, 0XAA };
            for (int i = 0; i < tempArr.Length; i++)
            {
                Arr[i] = tempArr[i];
            }
        }

        /// <summary>
        /// 表号设置按钮点击事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TableNnumber_Confirm_Button_Click(object sender, EventArgs e)
        {     
            try
            {
                uint temp = Convert.ToUInt32(TableNumber_TextBox.Text);   // 这一句是为了试错，保证输入的标号为纯数字，不是数字直接跳到catch中
                if (SerialPortHelper.NumLength(temp) != TableNumBitLength)  // 判断当前输入长度是否于需要配置的表号长度一致
                {
                    Dis_Rece_TextBox.AppendText("本批产品配置的表号为" + Convert.ToString(TableNumBitLength) + "位, 请检查输入表号是否正确\r\n");
                    return;
                }
                byte[] TableNumber = SerialPortHelper.Str2Bcd(TableNumber_TextBox.Text);    // 将字符串转成BCD码
                byte[] ConfTabNum = new byte[13+ TableNumber.Length];  // 根据表号的长度定义数组的长度      
                ConDefValve(ConfTabNum);        // 写入默认数据
                ConfTabNum[9] = ConfigTableNum;           // 写入设置表号指令
                Crc16.GetDataCrc16(TableNumber, ConfTabNum);             // 获取数据和CRC16校验
                Rece_HexCheckBox.Checked = true;    // 将接收16进制勾选框选上。
                SerialPortHelper.SendHex(SerialPort_Entity, ConfTabNum); // 发送数据
            }
            catch (Exception)
            {
                MessageBox.Show("请输入正确的表号", "ERROR");
            }
        }
        /// <summary>
        /// 发送获取IP地址命令按钮点击事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void GetIP_Button_Click(object sender, EventArgs e)
        {
            byte[] GetIp_Arr = new byte[13];
            ConDefValve(GetIp_Arr);
            GetIp_Arr[9] = GetIPAndPortDet;
            Crc16.GetCrc16(GetIp_Arr);
            Rece_HexCheckBox.Checked = true;
            SerialPortHelper.SendHex(SerialPort_Entity, GetIp_Arr);
        }
        private void HeadWare_Button_Click(object sender, EventArgs e)
        {
            // 硬件检测
        }
        /// <summary>
        /// 获取并判断字符串中的内容是否是IP地址
        /// </summary>
        /// <param name="IPAdd"></param>    IP地址字符串
        /// <param name="IP_Arr"></param>   需要存放的IP地址的数组
        /// <param name="index"></param>    索引值
        /// <returns></returns>
        public bool GetIPAddress(string IPAdd, byte[] IP_Arr, int index)
        {
            try
            {
                IPAdd = IPAdd.Replace(" ", "");          // 去除IP地址字符串中的 " "
                IPAddress IPAddress_temp = IPAddress.Parse(IPAdd);      // 将IP地址获取出来，如果获取到的IP地址不在合理范围内容，会跳到catch中提示IP地址不在正确范围内
                byte[] temp = IPAddress_temp.GetAddressBytes();         // 将IP地址依次放到数组中
                Array.Copy(temp, 0, IP_Arr, index, temp.Length);        // 将主IP地址
                return true;
            }
            catch (Exception)
            {

                IP_Port_PictureBox.Image = Resources.Error;
                MessageBox.Show("IP地址错误,不在正确IP地址范围内，请重新输入", "ERROR");
                return false;
            }
        }

        /// <summary>
        /// IP和端口确认按键确认Click方法
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void IP_PORT_Confirm_Button_Click(object sender, EventArgs e)
        {                                                                                   //主IP0  IP1   IP2   IP3  副IP0  IP1   IP2   IP3  PORT_h PORT_l
            byte[] IP_Port_Arr = { 0X68, 0X00, 0XE1, 0XA1, 0XAA, 0XAA, 0XAA, 0XAA, 0XAA, 0XFA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16 };
            string MainIpAddress = MainIPAddress_MaskedTextBox.Text;            // 获取主IP地址
            string SubIpAddrss = SubIPAddress_MaskedTextBox.Text;               // 获取副IP地址

            if ((Crc16.Str_IsEmpty(MainIpAddress) == true) && (Crc16.Str_IsEmpty(SubIpAddrss) == true))  // 判断主副IP地址是否都为空，若为空则提示需要任意输入一个IP地址
            {
                MessageBox.Show("修改IP请至少输入主IP或备用IP中任意一个", "ERROR");
                return;
            }
            else
            { 
                if (Crc16.Str_IsEmpty(MainIpAddress) != true)     // 判断主IP地址是否为空，为空则跳过
                {
                    // 判断获取IP地址是否成功
                    if (GetIPAddress(MainIpAddress, IP_Port_Arr, 10) == false)      // 判断该字符串内有没有类似于IP地址的内容，如果有则将其分为四个字节并放到输出数组中，
                    {
                        return;
                    }
                }
                if (Crc16.Str_IsEmpty(SubIpAddrss) != true)
                {
                    if (GetIPAddress(SubIpAddrss, IP_Port_Arr, 14) == false)
                    {
                        return;
                    }
                }
            }
            try
            {
                ushort PortNum = Convert.ToUInt16(Port_Num_TextBox.Text);   // 获取端口号
                if (PortNum > 65535 || PortNum < 0)                         // 判断端口号是否超过范围
                {
                    IP_Port_PictureBox.Image = Resources.Error;
                    MessageBox.Show("端口号超出范围(0-65535)，请重新输入", "ERROR");     // 错误提示
                    return;
                }
                IP_Port_Arr[18] = Convert.ToByte(PortNum & 0xFF);
                IP_Port_Arr[19] = Convert.ToByte(PortNum >> 8);
            }
            catch (Exception)
            {
                IP_Port_PictureBox.Image = Resources.Error;
                MessageBox.Show("端口号不能为空或负数", "ERROR");        // 若端口号位或为负数时进行提示
                return;
            }
            Crc16.GetCrc16(IP_Port_Arr);        // 获取Crc16校验结果
            Rece_HexCheckBox.Checked = true;
            SerialPortHelper.SendHex(SerialPort_Entity, IP_Port_Arr);   // 发送16进制数据数组
            //foreach (var item in IP_Port_Arr)
            //    Trace.Write(string.Format("{0:X2} ", item));
            //Trace.Write("\n");
        }
        /// <summary>
        /// ip地址输入框点击事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void IPAddress_MaskedTextBox_Click(object sender, EventArgs e)
        {
            MaskedTextBox maskedTextBox = (MaskedTextBox)sender;
            
            if (Crc16.Str_IsEmpty(maskedTextBox.Text) == true)       // 如果字符串为空，则将当前光标移到开始处
            {
                maskedTextBox.SelectionStart = 0;
            }
        }
        /// <summary>
        /// IP地址输入框按键检测事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void IPAddress_MaskedTextBox_KeyUP(object sender, KeyEventArgs e)
        {
            MaskedTextBox maskedTextBox = (MaskedTextBox)sender;
            switch (e.KeyCode)
            {
                case Keys.Decimal:

                    int pos = maskedTextBox.SelectionStart;
                    int max = (maskedTextBox.MaskedTextProvider.Length - maskedTextBox.MaskedTextProvider.EditPositionCount);
                    int nextField = 0;
                    for (int i = 0; i < maskedTextBox.MaskedTextProvider.Length; i++)
                    {
                        if (!maskedTextBox.MaskedTextProvider.IsEditPosition(i) && (pos + max) >= i)
                            nextField = i;
                    }
                    nextField += 1;
                    maskedTextBox.SelectionStart = nextField;
                    break;
                default:
                    break;
            }
        }
        /// <summary>
        /// 配置按键修改，修改电流测试阀值
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ConfigButton_Click(object sender, EventArgs e)
        {
            Button MyButton = (Button)sender;
            int flag = Convert.ToInt32(MyButton.Tag);
            try
            {
                switch (flag)
                {
                    case 0:
                        // 将通道0的最大，最小值写到全局变量中
                        CurrentTestStruct.Chan0MaxValve = Convert.ToDouble(Chan0MaxValve_TextBox.Text);
                        CurrentTestStruct.Chan0MinValve = Convert.ToDouble(Chan0MinValve_TextBox.Text);
                        if (CurrentTestStruct.Chan0MaxValve < CurrentTestStruct.Chan0MinValve)
                        {
                            SystemTag_Lable.Text = "修改失败";
                            MessageBox.Show("最大值不能比最小值小", "ERROR");
                            CurrentTestStruct.Chan0MaxValve = Convert.ToDouble(ConfigurationManager.AppSettings["SystemSettingConfig_Chan0MaxValve"]);
                            CurrentTestStruct.Chan0MinValve = Convert.ToDouble(ConfigurationManager.AppSettings["SystemSettingConfig_Chan0MinValve"]);
                            Chan0MaxValve_TextBox.Text = Convert.ToString(CurrentTestStruct.Chan0MaxValve);
                            Chan0MinValve_TextBox.Text = Convert.ToString(CurrentTestStruct.Chan0MinValve);
                            return;
                        }
                        AddUpdateAppSetting("SystemSettingConfig_Chan0MaxValve", Chan0MaxValve_TextBox.Text);
                        AddUpdateAppSetting("SystemSettingConfig_Chan0MinValve", Chan0MinValve_TextBox.Text);
                        SystemTag_Lable.Text = "修改成功";
                        break;
                    case 1:
                        // 将当前通道0的值写入该文本框
                        Chan0MaxValve_TextBox.Text = ConfigurationManager.AppSettings["SystemSettingConfig_Chan0MaxValve"];
                        Chan0MinValve_TextBox.Text = ConfigurationManager.AppSettings["SystemSettingConfig_Chan0MinValve"];
                        break;
                    case 2:
                        // 将通道1的最大，最小值写到全局变量中
                        CurrentTestStruct.Chan1MaxValve = Convert.ToDouble(Chan1MaxValve_TextBox.Text);
                        CurrentTestStruct.Chan1MinValve = Convert.ToDouble(Chan1MinValve_TextBox.Text);
                        
                        if (CurrentTestStruct.Chan1MaxValve < CurrentTestStruct.Chan1MinValve)
                        {
                            SystemTag_Lable.Text = "修改失败";
                            MessageBox.Show("最大值不能比最小值小", "ERROR");
                            CurrentTestStruct.Chan0MaxValve = Convert.ToDouble(ConfigurationManager.AppSettings["SystemSettingConfig_Chan1MaxValve"]);
                            CurrentTestStruct.Chan0MinValve = Convert.ToDouble(ConfigurationManager.AppSettings["SystemSettingConfig_Chan1MinValve"]);
                            Chan0MaxValve_TextBox.Text = Convert.ToString(CurrentTestStruct.Chan1MaxValve);
                            Chan0MinValve_TextBox.Text = Convert.ToString(CurrentTestStruct.Chan1MinValve);
                            return;
                        }
                        AddUpdateAppSetting("SystemSettingConfig_Chan1MaxValve", Chan0MaxValve_TextBox.Text);
                        AddUpdateAppSetting("SystemSettingConfig_Chan1MinValve", Chan0MinValve_TextBox.Text);
                        SystemTag_Lable.Text = "修改成功";
                        break;
                    case 3:
                        // 将当前通道0的值写入该文本框
                        Chan1MaxValve_TextBox.Text = ConfigurationManager.AppSettings["SystemSettingConfig_Chan1MaxValve"];
                        Chan1MinValve_TextBox.Text = ConfigurationManager.AppSettings["SystemSettingConfig_Chan1MinValve"];
                        break;

                    case 4: // 将表号配置位数写入存档
                        TableNumBitLength = Convert.ToByte(TableNumConfig_TextBox.Text);
                        if(TableNumBitLength <= 0)
                        {
                            SystemTag_Lable.Text = "修改失败";
                            MessageBox.Show("表号位数必须大于0", "ERROR");
                            TableNumBitLength = Convert.ToByte(ConfigurationManager.AppSettings["TableNumDefault"]);
                            TableNumConfig_TextBox.Text = Convert.ToString(TableNumBitLength);
                            return;
                        }
                        SystemTag_Lable.Text = "修改成功";
                        AddUpdateAppSetting("TableNumDefault", TableNumConfig_TextBox.Text);
                        break;
                    case 5:
                        TableNumConfig_TextBox.Text = ConfigurationManager.AppSettings["TableNumDefault"];
                        break;
                }
            }
            catch (Exception)
            {
                SystemTag_Lable.Text = "修改失败";
                MessageBox.Show("请输入整数或者小数，不能出现字母和汉字", "ERROR");
            }
            Timer_StateUpdata.Start();
        }
        /// <summary>
        /// 添加更新程序设置
        /// </summary>
        /// <param name="key"></param>
        /// 键
        /// <param name="valve"></param>
        /// 值
        private void AddUpdateAppSetting(string key, string valve)
        {
            try
            {
                var configFile = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
                var settings = configFile.AppSettings.Settings;
                if (settings[key] == null)
                {
                    settings.Add(key, valve);
                }
                else
                {
                    settings[key].Value = valve;
                }
                configFile.Save(ConfigurationSaveMode.Modified);
                ConfigurationManager.RefreshSection(configFile.AppSettings.SectionInformation.Name);
            }
            catch (Exception)
            {
                MessageBox.Show("保存失败, 请重试", "ERROR");
            }
        }
        /// <summary>
        /// 加载数据
        /// </summary>
        private void LoadApp_CurrentConfig()
        {
            try
            {
                Chan0MaxValve_TextBox.Text = ConfigurationManager.AppSettings["SystemSettingConfig_Chan0MaxValve"];
                Chan0MinValve_TextBox.Text = ConfigurationManager.AppSettings["SystemSettingConfig_Chan0MinValve"];
                Chan1MaxValve_TextBox.Text = ConfigurationManager.AppSettings["SystemSettingConfig_Chan1MaxValve"];
                Chan1MinValve_TextBox.Text = ConfigurationManager.AppSettings["SystemSettingConfig_Chan1MinValve"];
                TableNumConfig_TextBox.Text = ConfigurationManager.AppSettings["TableNumDefault"];

                CurrentTestStruct.Chan0MaxValve = Convert.ToDouble(Chan0MaxValve_TextBox.Text);
                CurrentTestStruct.Chan0MinValve = Convert.ToDouble(Chan0MinValve_TextBox.Text);
                CurrentTestStruct.Chan1MaxValve = Convert.ToDouble(Chan1MaxValve_TextBox.Text);
                CurrentTestStruct.Chan1MinValve = Convert.ToDouble(Chan1MinValve_TextBox.Text);
                TableNumBitLength = Convert.ToByte(TableNumConfig_TextBox.Text);
            }
            catch (Exception)       // 如果没有配置文件，则会在这里写入默认初始值
            {
                CurrentTestStruct.Chan0MaxValve = 30f;
                CurrentTestStruct.Chan0MinValve = 0;
                CurrentTestStruct.Chan1MaxValve = 60f;
                CurrentTestStruct.Chan1MinValve = 0;
                TableNumBitLength = 8;

                WriteInitialValve();
            }
        }
        /// <summary>
        /// 写入初始值
        /// </summary>
        private void WriteInitialValve()
        {
            Chan0MaxValve_TextBox.Text = Convert.ToString(CurrentTestStruct.Chan0MaxValve);
            AddUpdateAppSetting("SystemSettingConfig_Chan0MaxValve", Chan0MaxValve_TextBox.Text);

            Chan0MinValve_TextBox.Text = Convert.ToString(CurrentTestStruct.Chan0MinValve);
            AddUpdateAppSetting("SystemSettingConfig_Chan0MinValve", Chan0MinValve_TextBox.Text);

            Chan1MaxValve_TextBox.Text = Convert.ToString(CurrentTestStruct.Chan1MaxValve);
            AddUpdateAppSetting("SystemSettingConfig_Chan1MaxValve", Chan1MaxValve_TextBox.Text);

            Chan1MinValve_TextBox.Text = Convert.ToString(CurrentTestStruct.Chan1MinValve);
            AddUpdateAppSetting("SystemSettingConfig_Chan1MinValve", Chan1MinValve_TextBox.Text);

            TableNumber_TextBox.Text = Convert.ToString(TableNumBitLength);
            AddUpdateAppSetting("TableNumDefault", TableNumConfig_TextBox.Text);
        }
    }
}
