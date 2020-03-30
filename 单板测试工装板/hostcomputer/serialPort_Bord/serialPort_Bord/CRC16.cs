using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace serialPort_Bord
{
    class CRC16
    {
        /// <summary>
        /// 查表法校验表
        /// </summary>
        private readonly ushort[] CRC16R_A001_Table =
            {
            0x0000,0xC0C1,0xC181,0x0140,0xC301,0x03C0,0x0280,0xC241,0xC601,0x06C0,0x0780,0xC741,0x0500,0xC5C1,0xC481,0x0440,
            0xCC01,0x0CC0,0x0D80,0xCD41,0x0F00,0xCFC1,0xCE81,0x0E40,0x0A00,0xCAC1,0xCB81,0x0B40,0xC901,0x09C0,0x0880,0xC841,
            0xD801,0x18C0,0x1980,0xD941,0x1B00,0xDBC1,0xDA81,0x1A40,0x1E00,0xDEC1,0xDF81,0x1F40,0xDD01,0x1DC0,0x1C80,0xDC41,
            0x1400,0xD4C1,0xD581,0x1540,0xD701,0x17C0,0x1680,0xD641,0xD201,0x12C0,0x1380,0xD341,0x1100,0xD1C1,0xD081,0x1040,
            0xF001,0x30C0,0x3180,0xF141,0x3300,0xF3C1,0xF281,0x3240,0x3600,0xF6C1,0xF781,0x3740,0xF501,0x35C0,0x3480,0xF441,
            0x3C00,0xFCC1,0xFD81,0x3D40,0xFF01,0x3FC0,0x3E80,0xFE41,0xFA01,0x3AC0,0x3B80,0xFB41,0x3900,0xF9C1,0xF881,0x3840,
            0x2800,0xE8C1,0xE981,0x2940,0xEB01,0x2BC0,0x2A80,0xEA41,0xEE01,0x2EC0,0x2F80,0xEF41,0x2D00,0xEDC1,0xEC81,0x2C40,
            0xE401,0x24C0,0x2580,0xE541,0x2700,0xE7C1,0xE681,0x2640,0x2200,0xE2C1,0xE381,0x2340,0xE101,0x21C0,0x2080,0xE041,
            0xA001,0x60C0,0x6180,0xA141,0x6300,0xA3C1,0xA281,0x6240,0x6600,0xA6C1,0xA781,0x6740,0xA501,0x65C0,0x6480,0xA441,
            0x6C00,0xACC1,0xAD81,0x6D40,0xAF01,0x6FC0,0x6E80,0xAE41,0xAA01,0x6AC0,0x6B80,0xAB41,0x6900,0xA9C1,0xA881,0x6840,
            0x7800,0xB8C1,0xB981,0x7940,0xBB01,0x7BC0,0x7A80,0xBA41,0xBE01,0x7EC0,0x7F80,0xBF41,0x7D00,0xBDC1,0xBC81,0x7C40,
            0xB401,0x74C0,0x7580,0xB541,0x7700,0xB7C1,0xB681,0x7640,0x7200,0xB2C1,0xB381,0x7340,0xB101,0x71C0,0x7080,0xB041,
            0x5000,0x90C1,0x9181,0x5140,0x9301,0x53C0,0x5280,0x9241,0x9601,0x56C0,0x5780,0x9741,0x5500,0x95C1,0x9481,0x5440,
            0x9C01,0x5CC0,0x5D80,0x9D41,0x5F00,0x9FC1,0x9E81,0x5E40,0x5A00,0x9AC1,0x9B81,0x5B40,0x9901,0x59C0,0x5880,0x9841,
            0x8801,0x48C0,0x4980,0x8941,0x4B00,0x8BC1,0x8A81,0x4A40,0x4E00,0x8EC1,0x8F81,0x4F40,0x8D01,0x4DC0,0x4C80,0x8C41,
            0x4400,0x84C1,0x8581,0x4540,0x8701,0x47C0,0x4680,0x8641,0x8201,0x42C0,0x4380,0x8341,0x4100,0x81C1,0x8081,0x4040
        };
        /// <summary>
        /// 字符CRC校验
        /// </summary>
        /// <param name="data">校验数据</param>
        /// <returns>高低8位</returns>
        public static string CRCCalc(string data)
        {
            string[] datas = data.Split(' ');
            List<byte> bytedata = new List<byte>();

            foreach (string str in datas)
            {
                bytedata.Add(byte.Parse(str, System.Globalization.NumberStyles.AllowHexSpecifier));
            }
            byte[] crcbuf = bytedata.ToArray();
            //计算并填写CRC校验码
            int crc = 0xffff;
            int len = crcbuf.Length;
            for (int n = 0; n < len; n++)
            {
                byte i;
                crc ^= crcbuf[n];
                for (i = 0; i < 8; i++)
                {
                    int TT;
                    TT = crc & 1;
                    crc >>= 1;
                    crc &= 0x7fff;
                    if (TT == 1)
                    {
                        crc ^= 0xa001;
                    }
                    crc &= 0xffff;
                }

            }
            string[] redata = new string[2];
            redata[1] = Convert.ToString((byte)((crc >> 8) & 0xff), 16);
            redata[0] = Convert.ToString((byte)((crc & 0xff)), 16);
            return data + " " + redata[0] + " " + redata[1];
        }

        /// <summary>
        /// byte数组CRC校验
        /// </summary>
        /// <param name="bytes"></param>
        /// <returns></returns>
        public byte[] CRC16_Check(byte[] bytes)
        {
            //计算并填写CRC校验码
            int crc = 0xffff;
            int len = bytes.Length;
            for (int n = 0; n < len; n++)
            {
                byte i;
                crc ^= bytes[n];
                for (i = 0; i < 8; i++)
                {
                    int TT;
                    TT = crc & 1;
                    crc >>= 1;
                    crc &= 0x7fff;
                    if (TT == 1)
                    {
                        crc ^= 0xa001;
                    }
                    crc &= 0xffff;
                }
            }
            var nl = bytes.Length + 2;
            //生成的两位校验码
            byte[] redata = new byte[2];
            redata[0] = (byte)(crc & 0xff);
            redata[1] = (byte)((crc >> 8) & 0xff);
            //重新组织字节数组
            var newByte = new byte[nl];
            for (int i = 0; i < bytes.Length; i++)
            {
                newByte[i] = bytes[i];
            }
            newByte[nl - 2] = redata[0];
            newByte[nl - 1] = redata[1];
            return newByte;
        }


        /// <summary>
        /// 获取CRC16校验值
        /// </summary>
        /// <param name="crcBuff"></param>
        /// <param name="crcLen"></param>
        /// <returns></returns>
        public ushort GetCRC16(byte[] crcBuff, int crcLen)
        {
            uint i;
            ushort crc = 0xFFFF;//初值
            for (i = 0; i < crcLen; i++)
            {
                crc = Convert.ToUInt16((crc >> 8) ^ CRC16R_A001_Table[(crc & 0xFF) ^ crcBuff[i]]);
            }
            return crc;
        }

        /// <summary>
        /// CRC16_Check校验
        /// </summary>
        /// <param name="serArr"></param>原数组
        /// <returns>校验是否成功 true 成功 false 失败</returns>
        public bool CRC16_Check(byte[] serArr, int Len)
        {
            if (serArr[1] != Len)   // 判断数据长度是否正确
            {
                return false;       // 不正常则返回失败
            }
            byte[] temp = new byte[serArr[1] - 3];              // 创建比原数组小三字节大小的byte数组
            Array.Copy(serArr, temp, temp.Length);              // 将原数组复制到新数组中准备用于校验
            ushort CrcValve = GetCRC16(temp, temp.Length);      // 获取校验结果
            byte[] Check_Arr = new byte[2];                     // 创建2字节byte数组用于存放校验位
            Check_Arr[0] = Convert.ToByte(CrcValve >> 8);       // 获取校验位高8位
            Check_Arr[1] = Convert.ToByte(CrcValve & 0xFF);     // 获取校验位低8位

            // 判断校验位是否相等
            byte[] srcCheck_Arr = new byte[2];
            Array.Copy(serArr, Len - 3, srcCheck_Arr, 0, 2);
            if (Arr_Equals(srcCheck_Arr, Check_Arr) != true)
            {
                return false;
            }
            return true;    // 校验成功返回成功
        }
        /// <summary>
        /// 获取Crc16校验数据
        /// </summary>
        /// <param name="disArr"></param> 原数组
        public void GetCrc16(byte[] disArr)
        {
            disArr[1] = Convert.ToByte(disArr.Length);
            byte[] temp = new byte[disArr[1] - 3];
            Array.Copy(disArr, temp, disArr[1] - 3);
            ushort CrcValve = GetCRC16(temp, temp.Length);
            disArr[disArr.Length - 2] = Convert.ToByte(CrcValve >> 8);
            disArr[disArr.Length - 3] = Convert.ToByte(CrcValve & 0xff);
            disArr[disArr.Length - 1] = 0x16;
        }

        /// <summary>
        /// 将数据位和校验位存放到发送数组中
        /// </summary>
        /// <param name="srcArr"></param>
        /// <param name="disArr"></param>
        public void GetDataCrc16(byte[] srcArr, byte[] disArr)
        {
            int crcLen = srcArr.Length + 10;
            Array.Copy(srcArr, 0, disArr, 10, srcArr.Length);       // 先将原数组放到目标数组，此处的原数组表示的表号
            disArr[1] = Convert.ToByte(disArr.Length);              // 将数组长度放在目标数组的第1位
            ushort CrcValve = GetCRC16(disArr, crcLen);             // 获取CRC16校验值
            disArr[disArr.Length - 3] = Convert.ToByte(CrcValve & 0xff);    // 存放CRC16校验高位
            disArr[disArr.Length - 2] = Convert.ToByte(CrcValve >> 8);      // 存放CRC16校验低位
            disArr[disArr.Length - 1] = 0x16;                       // 存放最后一位数组
        }
        /// <summary>
        /// 判断数组内容是否一致
        /// </summary>
        /// <param name="ArrA"></param>
        /// <param name="ArrB"></param>
        /// <returns></returns>
        public bool Arr_Equals(byte[] ArrA, byte[] ArrB)
        {
            // 首先判断数组长度是否一致
            if (ArrA.Length != ArrB.Length)
            {
                return false;   // 不一致则直接返回不相等
            }
            for (int i = 0; i < ArrA.Length; i++)   // 让数组A与数组B进行比较
            {
                if (ArrA[i] != ArrB[i])
                {
                    return false;   // 某一位不相等则直接返回不相等
                }
            }
            return true;
        }
        /// <summary>
        /// uint类型转成byte类型
        /// </summary>
        /// <param name="uintArr"></param> 需要转换的数组
        /// <returns></returns> 转换后的数组
        public byte[] UintToByte(uint[] uintArr)
        {
            ushort Len = Convert.ToUInt16(uintArr.Length);
            byte[] buf = new byte[Len];
            for (int i = 0; i < Len; i++)
            {
                buf[i] = Convert.ToByte(uintArr[Len - 1 - i]);
            }
            return buf;
        }

        /// <summary>
        /// 寻找字符串的中的数字(包括小数)
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public double GetStrOnDig(string str)
        {
            try
            {
                string doublNumber = Regex.Replace(str, @"[^0-9,.]+", "");  // 正则表达式寻找
                return Convert.ToDouble(doublNumber);       // 转换为双精度浮点数
            }
            catch (Exception)
            {
                return -1;   // 寻找失败则输返回-1
            }
        }
        /// <summary>
        /// 判断字符串是否为空，
        /// </summary>
        /// <param name="str"></param> 需要判断的字符串
        /// <returns>true 字符串为空 false 字符串不为空 </returns>
        public bool Str_IsEmpty(string str)
        {
            string str_temp = str.Replace(".", "").Replace(" ", "");    // 去除文本中的空格和.
            if (str_temp != "")
            {
                return false;
            }
            return true;
        }
    }
}
