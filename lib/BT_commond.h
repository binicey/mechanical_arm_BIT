/*
 * @Author: Iccccy.xie(binicey@outlook.com) 
 * @Date: 2020-11-14 17:59:53 
 * @Last Modified by:   Iccccy.xie(binicey@outlook.com) 
 * @Last Modified time: 2020-11-14 17:59:53 
 */

//蓝牙指令模式
#include<SoftwareSerial.h>
#include<setup.h>
#include<ARM_controller.h>
int BT_RX=4;
int BT_TX=5;
SoftwareSerial BT=SoftwareSerial(1,1);
void BTsetup()
{
    BT=SoftwareSerial(BT_RX,BT_TX);
    Serial.println(BT_RX);
}
//读取指令模式
char BT_commond='n';
int BT_data=0;


void BT_ERROR(int Error_NUM)
{
    switch (Error_NUM)
    {
    case 1:
        BT.println("Invalid Commond");
        break;
    
    default:
        break;
    }
}

void BT_main()
{
    BT_commond=BT.read();
    BT_data=BT.parseInt();
    switch (BT_commond)
    {
    case 'u':
        ARM_UP_move(BT_data);
        break;
    case 'd':
        ARM_DOWN_move(BT_data);
    case 'r':
        ARM_RIGHT_move(BT_data);
    case 'l':
        ARM_LEFT_move(BT_data);
    default:
        BT_ERROR(0);
        break;
    }
}
