#ifndef __NBIotBC95__H
#define __NBIotBC95__H

#include "stm8l15x.h"
#include "usart.h"
#include "Delay.h"
#include "string.h"
#include "McuConfig.h"

#define UE_LOCAL_UDP_PORT           "3005"
#define SERVER_HOST_UDP_IP          "219.235.15.234"
#define SERVER_HOST_UDP_PORT        "5002"
#define NB_AT_REBOOT                "AT+NRB\r\n"    //复位终端
#define NB_AT                       "AT\r\n"
#define NB_ACK_OK                   "OK"
#define NB_AT_BAND                  "AT+NBAND?\r\n"
#define NB_AT_BAND_5                "AT+NBAND=5\r\n"  //设置频段
#define NB_AT_BAND_8                "AT+NBAND=8\r\n"
#define NB_ACK_BAND                 "+NBAND:5"
#define NB_AT_NCSEARFCN             "AT+NCSEARFCN\r\n"
#define NB_AT_CONNECT_MODE          "AT+NCONFIG?\r\n"
#define NB_AT_AUTOCONNECT           "AT+NCONFIG=AUTOCONNECT,TRUE\r\n"
#define NB_AT_MANUALCONNECT         "AT+NCONFIG=AUTOCONNECT,FALSE\r\n"
#define NB_AT_NCDP_SET              "AT+NCDP=117.60.157.137,5683\r\n" 
#define NB_AT_NCDP_SET1             "AT+NCDP=180.101.147.115,5683\r\n"
#define NB_ACK_NCDP                 "117.60.157.137"
#define NB_ACK_NCDP1                "180.101.147.115"
#define NB_AT_NCDP                  "AT+NCDP?\r\n"
#define NB_AT_FUNC                  "AT+CFUN?\r\n"
#define NB_AT_FUNC_0                "AT+CFUN=0\r\n"
#define NB_AT_FUNC_1                "AT+CFUN=1\r\n" //”开启功能开关。
#define NB_AT_CGSN                  "AT+CGSN=1\r\n"//获取设备号
#define NB_AT_CSQ                   "AT+CSQ\r\n"
#define NB_AT_CGATT                 "AT+CGATT?\r\n"
#define NB_ACK_CGATT                "+CGATT:1"
#define NB_AT_CGATT_1               "AT+CGATT=1\r\n" //终端入网
#define NB_AT_CEREG                 "AT+CEREG?\r\n"
#define NB_ACK_CEREG                "+CEREG:0,1"

#define NB_AT_EREG_STATS             "AT+CEREG?\r\n"
#define NB_ACK_EREGISTERING_STATS    "+CEREG:0,2"
#define NB_ACK_EREGISTERED_STATS     "+CEREG:0,1"
#define NB_AT_EREG_1                 "AT+CEREG=1\r\n"

#define NB_AT_SCCON_STATS           "AT+CSCON?\r\n"
#define NB_ACK_SCCON_1              "AT+CSCON=1"
#define NB_ACK_CSCON                "+CSCON:0,1"
#define NB_AT_CIMI                  "AT+CIMI\r\n"
#define NB_AT_NNMI_1                "AT+NNMI=1\r\n"  ///设置下行数据通知功能
#define NB_AT_NNMI_2                "AT+NNMI=2\r\n"  ///设置下行数据通知功能
#define NB_AT_SEND_DATE             "AT+NMGS=\r\n"//发送数据 AT+NMGS=6,010412345678
#define NB_AT_CGPADDR               "AT+CGPADDR\r\n"  //查询终端是否获取到核心网分配的IP地址
#define NB_AT_CMEE                  "AT+CMEE=1\r\n"    //查询故障代码
#define NB_AT_NCCID                 "AT+NCCID\r\n"  //卡片识别
#define NB_ACK_NCCID                "+NCCID:"
#define NB_AT_CGDCONT               "AT+CGDCONT=1,\"IP\",\"CTNB\"\r\r"  //定义一个 PDP 上下文
#define NB_AT_NUESTATS              "AT+NUESTATS=CELL\r\n"   //查询ECL  及其他相关信息


//NB Iot Power
#define NB_POWER_ON  GPIO_SetBits(GPIOE,GPIO_Pin_6)
#define NB_POWER_OFF GPIO_ResetBits(GPIOE,GPIO_Pin_6)

#define NB_POWERKEY_ON  GPIO_SetBits(GPIOE,GPIO_Pin_7)
#define NB_POWERKEY_OFF GPIO_ResetBits(GPIOE,GPIO_Pin_7)


//NB模块状态
typedef struct
{
  
    unsigned char NBNss[4];          //NB网络信号强度
    unsigned char ECLL[1];           //ECL覆盖等级
    unsigned char Cellid[6];         //CellID
    unsigned char REAL_Point[2];     //实际接入频点
    unsigned char NBICCID[20];       //ICCID
    unsigned char IMEI[15];          //IMEI号

}NBState_Typ;

extern void Wait_Time(void);

extern NBState_Typ nbs;





#endif
