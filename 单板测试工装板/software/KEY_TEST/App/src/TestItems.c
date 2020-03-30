// ���ļ������������幤װ���԰�Ĳ��Դ���

//����ͷ�ļ�
#include "TestItems.h"

// ����ȫ�ֱ���
Global_Flag_TypeDef MyFlagSturct = {0};

bool Flag_PA3 = FALSE;


//*****************************************************************************/
//*������ :void Wait_Implement(void)
//*˵��   :�ȴ���λ���·������ݣ��ж�ָ��λ�����ݣ�����ָ���ĺ���ִ��
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Wait_Implement(void)
{
    
    if(USART_3.Falg != FALSE)   // �ж��Ƿ��������յ�,�жϴ���3���ձ�־λ��ֵ
    {
        
        if(USART_3.USART_Date[2] == CHECKDET)       // �ж�У��λ
        {
           
            switch(USART_3.USART_Date[1]) // ѡ����Ҫִ�еĺ���
            {   
            case LORACOM:
               
                LoRa_Test();    // ����LoRa���Ժ���
                break;
                
            case CURRENTDET:    // �������Ժ�����Ӳ��ȱʧ
                
                break;
            case KEYDET:
               
                Key_Test();     // IOͨ�ϲ��Ժ���
                break;
            case RSCOMDET:
               
                RS485_Test();   // RS485ͨ�Ų��Ժ���
                break;
                    
            default:
               
                ReturnTestDet(ERRORCOM); // ���Ѷ���Ĳ���ָ��
                break;
                    
            }
        }      
    }
    if(MyFlagSturct.FunKeyFlag == 1)
    {
        MyFlagSturct.FunKeyFlag = 0;
        LED_Off(4);
        memset(USART_3.USART_Date, 0, sizeof(USART_3.USART_Date));
        memset(USART_2.USART_Date, 0, sizeof(USART_2.USART_Date));
        USART_3.Falg = 0;
        USART_2.Falg = 0;
        USART_3.Length = 0;
        USART_2.Length = 0;
        USART_3.USART_Halt_Falg = 0;
        USART_3.USART_Halt_Falg = 0;
    }
    
}

//*****************************************************************************/
//*������ :void ReturnTestDet(u8 det)
//*˵��   :�ϴ����Խ��
//*˵��   :����λΪУ��λ��Ĭ��0x00
//*����   :Det    ���Խ��ָ��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void ReturnTestDet(u8 Det)
{
    
    u8 UploadDetArr[4] = {0};       // �����ϴ�����,4������
    UploadDetArr[0] = UPDATACOM;    // �ϴ����ݿ�ʼλ
    UploadDetArr[3] = UPCONFIR;     // �ϴ����ݽ���λ   
    UploadDetArr[1] = Det;          // ʵ�ʵĲ�������ָ��   
    UsartSend(USART3, UploadDetArr, 4);
//    UsartSend(USART3, "\r\n", 2);
    
}


//*****************************************************************************/
//*������ :void LoRa_Test(void)
//*˵��   :LoRaģ����Ժ���
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void LoRa_Test(void)
{ 
//    // ������ʾ����
//    u8 LoRa_Str1[] = {"LoRa Initialization successful!\r\n"};
//    u8 LoRa_Str2[] = {"LoRa Startup failure!\r\n"};
//    u8 LoRa_Send_DataArr[5] = {0x01, 0x03, 0x05, 0x07, 0x09};   // LoRa������������   
//    if(MyFlagSturct.LoRaInitFlag == FALSE)
//    {
//        if(RF1278_Init(2, 2))
//        {
//            MyFlagSturct.LoRaInitFlag = TRUE;   // LoRa��Ƶ��ʼ����־λ��1
//            UsartSend(USART3, LoRa_Str1, 34);
//        }
//        else
//        {           
//            UsartSend(USART3, LoRa_Str2, 23);             // �����������LoRaģ���ʼ��ʧ��,LoRa���Խ���
//        }      
//    }
//    
//    if(MyFlagSturct.LoRaInitFlag == TRUE)       // �жϳ�ʼ���Ƿ�ɹ�
//    {        
//        RF1278_SendPacket(LoRa_Send_DataArr, 5);   
//        
//        Rf1278_ModeSet(50);     // ��������       
//        TIM3_Cmd(ENABLE);   // ������ʱ��4
//        MsCount = 0;      // ��λ������
//        while(MsCount < COUNTNUM)     // �ȴ����룬��������
//        {
//            if(MyFlagSturct.LoRaRXFlag == 1)
//            {
//                Rece_DataCheck(LORACOM);
//                if(MyFlagSturct.ReceDataFlag == 5)    // ���յ����ݺ��ж����ݵ���ȷ�� 
//                {
//                    MyFlagSturct.LoRaTestFlag = LORACOM;
//                    MyFlagSturct.LoRaRXFlag = 0;
//                    LED0_L();
//                }
//                else
//                {
//                    MyFlagSturct.LoRaTestFlag = LORAERRDET;
//                    MyFlagSturct.LoRaRXFlag = 0;
//                }
//                
//                ReturnTestDet(MyFlagSturct.LoRaTestFlag);   // �ϴ�LORA���ԵĽ��
//                memset(USART_3.USART_Date,0,sizeof(USART_3.USART_Date));                // �������3���ݻ�����                
//                TIM3_Cmd(DISABLE);  // �رն�ʱ��2
//                MsCount = 0;      // ����ʱ���־λ��0
//                break;
//            }
//        } 
//        if(MsCount == COUNTNUM)
//        {
//            MsCount = 0;
//            MyFlagSturct.LoRaTestFlag = LORAERRDET;
//            MyFlagSturct.LoRaRXFlag = 0;
//            ReturnTestDet(MyFlagSturct.LoRaTestFlag);   // �ϴ�LORA���ԵĽ��
//            memset(USART_3.USART_Date,0,sizeof(USART_3.USART_Date));                // �������3���ݻ�����                
//            TIM3_Cmd(DISABLE);  // �رն�ʱ��2
//        }
////        if(MyFlagSturct.LoRaRXFlag == 0)
////        {
////            TIM3_Cmd(DISABLE);
////            MsCount = 0;
////            
////        }
//    }    
}
//*****************************************************************************/
//*������ :void _Rece_DataCheck(u8 Mode)
//*˵��   :��������У�麯��
//*����   :mode    ѡ�����ģʽ
//*����ֵ :DataVar У��ɹ�����(0-5֮��)
//*����   :
//*****************************************************************************/
void Rece_DataCheck(u8 Mode)
{
    u8 Data_Array[] = {0xff, 0xfe, 0xfd, 0xfc, 0xfb};   // ���رȽ�����                        
    
    u8 Rece_DataArr[5] = {0};   // LoRa������������
        
    u8 DataVar; // ����ѭ������
    if(Mode == LORACOM) // LoRa
    {
        
//        RF1278_RecePacket(Rece_DataArr, 5);// ����LoRa�������ݺ���
    }
    else if(Mode == RSCOMDET)   // RS485
    {
        for(DataVar = 0; DataVar < 5; DataVar++)
        {
            Rece_DataArr[DataVar] = USART_2.USART_Date[DataVar];
        }
    }
    
    for(DataVar = 0; DataVar < 5; DataVar++)    // �뱾��������5�αȽ�
    {
        
         if(Rece_DataArr[DataVar] != Data_Array[DataVar])   // �жϱ�����������յ������Ƿ����
         {  
             break;// �������ֱ�ӽ�������LoRa����
         }
         
    }
    MyFlagSturct.ReceDataFlag = DataVar; 
    
}

//*****************************************************************************/
//*������ :void RS485_Test(void)
//*˵��   :RS485���Ժ���, ����һ�����ݣ�Ȼ��ȴ�����
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void RS485_Test(void)
{
    
    // ��������
    u8 RS_SendArr[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee};
    // ��������
    RS485_Send(RS_SendArr, 5);
    // ������ʱ��2
    TIM3_Cmd(ENABLE);
    // �ȴ����룬��������
    while(MsCount < COUNTNUM)
    {
        if(USART_2.Length != 0)
        {
            Rece_DataCheck(RSCOMDET);
            
           if(MyFlagSturct.ReceDataFlag == 5)
           {
               MyFlagSturct.RS485TestFlag = RSCOMDET;
               LED1_L();
           }
           else
           {
               MyFlagSturct.RS485TestFlag = DETERROR;
           }
           ReturnTestDet(MyFlagSturct.RS485TestFlag);
           memset(USART_2.USART_Date,0,sizeof(USART_2.USART_Date));       // �������2 
           TIM3_Cmd(DISABLE);// �رն�ʱ��1
           MsCount = 0;
           break;      
        }
    } 
    if(MsCount == COUNTNUM)
    {
        MsCount = 0;
        TIM3_Cmd(DISABLE);
        memset(USART_2.USART_Date, 0, sizeof(USART_2.USART_Date));
    }
}


//*****************************************************************************/
//*������ :void Key_Test(void)
//*˵��   :IOͨ�ϲ���
//*����   :��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void Key_Test(void)
{
    u8 ReturnDat = 0x00; 
    Key_Init(0);    // ��������ʼ��Ϊ�������ж�����
    ReturnDat = Key_Scan();
//    if(ReturnDat != 0)
//    {
        USART_3.Length = 0;
        memset(USART_3.USART_Date,0,sizeof(USART_3.USART_Date));       // �������2 
        USART_3.Falg = 0;
//    }
    LED1_L();
    if(ReturnDat != 0)
    {
        if(MyFlagSturct.Key1Flag != 0)
        {
            ReturnTestDet(MyFlagSturct.Key1Flag);
        }
        if(MyFlagSturct.Key2Flag != 0)
        {
            ReturnTestDet(MyFlagSturct.Key2Flag);
        }
        if(MyFlagSturct.Key3Flag != 0)
        {
            ReturnTestDet(MyFlagSturct.Key3Flag);
        }
        if(MyFlagSturct.Key4Flag != 0)
        {
            ReturnTestDet(MyFlagSturct.Key4Flag);
        }
    }
    else
    {
        ReturnTestDet(ReturnDat);
    }
}

//*****************************************************************************/
//*������ :u8 Key_Scan(void)
//*˵��   :������⺯����������������ʱ��LED�ƻ����𣬰����ɿ���LED��Ϩ��
//*����   :��
//*����ֵ :Count   ����IOͨ�ϲ����ܴ���
//*����   :
//*****************************************************************************/
u8 Key_Scan(void)
{
    // ͨ�ϴ���ͳ��
    u8 Count = 0X00;
    u16 CurrentTime;
    MsCount = 0;
    // ��λ������־λ
    MyFlagSturct.Key1Flag = 0;
    MyFlagSturct.Key2Flag = 0;
    MyFlagSturct.Key3Flag = 0;
    MyFlagSturct.Key4Flag = 0;
    TIM3_Cmd(ENABLE);
    
    while(MsCount <= COUNTNUM)
    {
        CurrentTime = MsCount;
        if(READ_KEY1() == RESET)
        {
            
            if((MsCount >= (CurrentTime+1)) && (READ_KEY1() == RESET))
            {                
                MyFlagSturct.Key1Flag++;
                Count = 1;
                while(READ_KEY1() == RESET);                 
            }
        }        
        else if(READ_KEY2()  == RESET)
        {
            
            if((MsCount >= (CurrentTime+1)) && (READ_KEY2() == RESET))
            {
                MyFlagSturct.Key2Flag++;
                Count = 1;
                while(READ_KEY2() == RESET);
            }
        }
        
        else if(READ_KEY3()  == RESET)
        {
            
            if((MsCount >= (CurrentTime+1)) && (READ_KEY3() == RESET))
            {
               
                MyFlagSturct.Key3Flag++;
                Count = 1;
                while(READ_KEY3() == RESET);
                 
            }
        }
        else if(READ_KEY4()  == RESET)
        {
            
            if((MsCount >= (CurrentTime+1)) && (READ_KEY4() == RESET))
            {
                MyFlagSturct.Key4Flag++;
                Count = 1;
                while(READ_KEY4() == RESET);
            }
        }
    }
    return Count;
}


void RS485_Rece(void)
{
    u8 RS_Arr[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee};
    u8 RSDataLen = 0;
    RS_EN_RX();
    if(USART_2.Length != 0)
    {
        for(;RSDataLen < USART_2.Length; RSDataLen++)
        {
            if(RS_Arr[RSDataLen] != USART_2.USART_Date[RSDataLen])
            {
                break;
            }
        }
        
//        ReturnTestDet(MyFlagSturct.RS485TestFlag);
        
    }
    if((RSDataLen == USART_2.Length) && (RSDataLen != 0))
        {
//            MyFlagSturct.RS485TestFlag = RSCOMDET;
            RS485_Send(RS_Arr, 6);
            LED2_L();
        }
        else
        {
            MyFlagSturct.RS485TestFlag = RSERRDET;
        }
    if(USART_2.Length != 0)
    {
        USART_2.Length = 0;
        memset(USART_2.USART_Date, 0, sizeof(USART_2.USART_Date));
    }
    
}