using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;

namespace serialPort_Bord
{
    class SerialPortHelper
    {
        public enum SendData_Typedef        // 发送数据返回状态
        {
            SendError,      // 发送错误
            SendComp,       // 发送完成
            SendNull,       // 发送值为空
            PortError       // 串口错误
        }
        public SendData_Typedef SendHex(SerialPort serialPort, byte[] hexArr)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    byte[] data = new byte[1];      // 存放需要写入串口的数据
                    for (int i = 0; i < hexArr.Length - 1; i++)
                    {
                        data[0] = hexArr[i];    // 将数据数组转换为二进制数据
                        serialPort.Write(data, 0, 1);               // 发送数据
                    }
                    if (hexArr.Length % 2 != 0)  // 单独处理最后一位
                    {
                        data[0] = hexArr[hexArr.Length - 1];    // 发送最后一位
                        serialPort.Write(data, 0, 1);           
                    }
                    return SendData_Typedef.SendComp;
                }
                catch (Exception)
                {
                    return SendData_Typedef.SendError;
                }
            }
            else
            {
                MessageBox.Show("串口未打开", "ERROR");
                return SendData_Typedef.PortError;
            }
        }
        /// <summary>
        /// 获取串口号
        /// </summary>
        /// <param name="comboBox">串口号填写的下拉框控件</param>
        public void GetSerialName(ComboBox comboBox)
        {

            string[] portNames = SerialPort.GetPortNames();     // 获取串口名
            foreach (string name in portNames)  // 将获取到的串口名称加到串口名称下拉框中
            {
                comboBox.Items.Add(name);
            }
            if ((comboBox.Items.Count != 0) && (comboBox.Text == ""))    // 如果串口下拉框中存在串口名称则将第一个串口名设置为串口下拉框的默认text属性
            {
                comboBox.Text = (string)comboBox.Items[0];
            }
            else  // 没有则为空
            {
                comboBox.Text = "";
            }
        }
        /// <summary>
        /// 大小端转换
        /// </summary>
        /// <param name="old_data"></param>
        /// 需要被转换的数组
        /// <param name="new_data"></param>
        /// 目标数组
        /// <param name="len">长度</param>
        /// 转换长度
        public void ReverStr(byte[] old_data, byte[] new_data, int len)
        {
            for (int i = 0; i < len; i++)
            {
                new_data[i] = old_data[len - i - 1];
            }
        }

        /// <summary>
        /// 发送字符串
        /// </summary>
        /// <param name="serialPort">需要发送的串口名称</param>
        /// <param name="textBox">需要发送数据的文本框</param>
        /// <returns></returns>
        public SendData_Typedef SendStr(SerialPort serialPort, TextBox textBox)
        {
            try
            {
                Encoding encoding = System.Text.Encoding.GetEncoding("GB2312");
                byte[] bytes = encoding.GetBytes(textBox.Text);
                serialPort.Write(bytes, 0, bytes.Length);
                return SendData_Typedef.SendComp;
            }
            catch (Exception)
            {
                return SendData_Typedef.SendError;
            }
        }

        /// <summary>
        /// 将字符串模式的byte数组转换为实际意义的byte数组
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static byte[] HexStringToByteArray(string str)
        {
            str = str.Replace(" ", "");                 //先替换其中的空格等
            byte[] buffer = new byte[str.Length / 2];   //新建一个byte数组用来保存，长度是字符串长度的一半
            for (int i = 0; i < str.Length; i += 2)     //循环遍历字符串来赋值给byte数组
            {
                buffer[i / 2] = (byte)Convert.ToByte(str.Substring(i, 2), 16);  //按2位来截取转换为byte数据
            }
            return buffer;//返回转换之后的byte数组
        }

        /// <summary>
        /// 将数字转换成BCD码
        /// </summary>
        /// <param name="num"></param>
        /// <param name="arr"></param>
        public uint[] ConverBCD(uint num)
        {
            uint bit = num;
            uint t = 100;
            byte Len = NumLength(bit);
            if (Len % 2 == 0)
            {
                uint[] Arr = new uint[Len / 2];
                string[] tempArr = new string[Len / 2];
                uint[] arr = new uint[Len / 2];
                for (int i = 0; i < Len / 2; i++)
                {
                    Arr[i] = bit % t;
                    tempArr[i] = Convert.ToString(Arr[i]);                   
                    arr[i] = Convert.ToUInt16(tempArr[i], 16);
                    bit /= t;
                }
                return arr;
            }
            else
            {
                uint[] Arr = new uint[Len / 2 + 1];
                string[] tempArr = new string[Len / 2 + 1];
                uint[] arr = new uint[Len / 2 + 1];
                for (int i = 0; i < Len / 2 + 1; i++)
                {
                    Arr[i] = bit % t;
                    tempArr[i] = Convert.ToString(Arr[i]);                    
                    arr[i] = Convert.ToUInt16(tempArr[i], 16);
                    bit /= t;
                }
                return arr;
            }
        }
        /// <summary>
        /// 获取uint型数字的位数
        /// </summary>
        /// <param name="num"></param>
        /// <returns></returns>
        public byte NumLength(uint num)
        {
            byte bit = 0;
            while (num > 0)
            {
                num /= 10;
                bit++;
            }
            return bit;
        }

        /// <summary>
        /// 在文本框中打印byte字符(纯数字)(IP地址)
        /// </summary>
        /// <param name="Arr"></param>  需要输出的数组
        /// <param name="textBox"></param>  输出的位置
        public void PrintIP(byte[] Arr, TextBox textBox)
        {
            for (int i = 0; i < Arr.Length; i++)
            {
                textBox.AppendText(Convert.ToString(Arr[i]));   // 将数据转换成字符串并输出到文本框中 
                if (i < 3)
                {
                    textBox.AppendText(".");    // IP中的点
                }
            }
            textBox.AppendText("\r\n");     // 输出换行
        }

        /// <summary>
        /// 将字符串转为BCD码
        /// </summary>
        /// <param name="asc"></param>
        /// <returns></returns>
        public byte[] Str2Bcd(string asc)
        {
            int len = asc.Length;
            int mod = len % 2;

            if (mod != 0)
            {
                asc = "0" + asc;
                len = asc.Length;
            }

            byte[] abt = new byte[len];
            if (len >= 2)
            {
                len /= 2;
            }

            byte[] bbt = new byte[len];
            abt = Encoding.ASCII.GetBytes(asc);
            int j, k;

            for (int p = 0; p < asc.Length / 2; p++)
            {
                if ((abt[2 * p] >= '0') && (abt[2 * p] <= '9'))
                {
                    j = abt[2 * p] - '0';
                }
                else if ((abt[2 * p] >= 'a') && (abt[2 * p] <= 'z'))
                {
                    j = abt[2 * p] - 'a' + 0x0a;
                }
                else
                {
                    j = abt[2 * p] - 'A' + 0x0a;
                }

                if ((abt[2 * p + 1] >= '0') && (abt[2 * p + 1] <= '9'))
                {
                    k = abt[2 * p + 1] - '0';
                }
                else if ((abt[2 * p + 1] >= 'a') && (abt[2 * p + 1] <= 'z'))
                {
                    k = abt[2 * p + 1] - 'a' + 0x0a;
                }
                else
                {
                    k = abt[2 * p + 1] - 'A' + 0x0a;
                }

                int a = (j << 4) + k;
                byte b = (byte)a;
                bbt[p] = b;
            }
            return bbt;
        }
        /// <summary>
        /// BCD码转成字符串
        /// </summary>
        /// <param name="bcdNum">BCD码数组</param>
        /// <returns></returns>
        public string BCDToString(byte[] bcdNum)
        {
            StringBuilder temp = new StringBuilder(bcdNum.Length * 2);

            for (int i = 0; i < bcdNum.Length; i++)
            {
                temp.Append((byte)((bcdNum[i] & 0xf0) >> 4));
                temp.Append((byte)(bcdNum[i] & 0x0f));
            }
            return temp.ToString().Substring(0, 1).Equals("0") ? temp.ToString().Substring(1) : temp.ToString();
        }
    }
}
