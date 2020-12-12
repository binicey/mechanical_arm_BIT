/*** 
 * @Author: Iccccy.xie
 * @Date: 2020-11-14 17:59:53
 * @LastEditTime: 2020-12-12 23:39:58
 * @LastEditors: Iccccy.xie(binicey@outlook.com)
 * @FilePath: \Mechanical _Arm\include\BT_commond.h
 */

#include <ARM_controller.h>
#include <SoftwareSerial.h>
void BTsetup();
void BT_ERROR(int Error_NUM);
void BT_main();

//蓝牙指令模式

// 蓝牙参数的初始化
int BT_RX = 6;
int BT_TX = 5;
SoftwareSerial BT = SoftwareSerial(BT_RX, BT_TX);
// 初始化蓝牙串口
void BTsetup()
{
    BT.begin(9600);
    BT.print("online");
}

// 指令读取报错
void BT_ERROR(int Error_NUM)
{
    switch (Error_NUM)
    {
    case 0:
        BT.println("Invalid Commond");
        delay(100);
        break;
    case 1:
        BT.println("Init Stepper Position Failed!");
        delay(100);
    default:
        break;
    }
}
//清空缓存数据
void btCacheClear()
{
    while (BT.available())
    {
        BT.read();
    }
}

void BT_main()
{

    //读取指令模式
    // BT.listen();
    // BT.print("online");
    BT.print("BT commond mod");
    delay(100);
    while (1)
    {
        char BT_commond = 'n';
        if (BT.available())
        {
            BT_commond = BT.read();
            Serial.println(BT_commond);
        }
        if (BT_commond == 'n')
            continue;
        if (!(BT_commond == 'c' || BT_commond == 'u' || BT_commond == 'd' || BT_commond == 'r' || BT_commond == 'l' || BT_commond == 'S'))
        {
            BT_ERROR(0);
            btCacheClear();
            continue;
        }
        int BT_data = BT.parseInt();
        btCacheClear();
        Serial.println(String(BT_data));
        switch (BT_commond)
        {
        case 'u':
            ARM_ForwordAndBack_move(BT_data);
            break;
        case 'd':
            ARM_ForwordAndBack_move(-BT_data);
            break;
        case 'r':
            ARM_RightAndLeft_move(BT_data);
            break;
        case 'l':
            ARM_RightAndLeft_move(-BT_data);
        case 'c':
            armClaw(BT_data);
            break;
        case 'S':
            ARM_setted_mod(BT_data);
            break;
        }
    }
}
