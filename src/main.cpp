/*** 
 * @Author: Iccccy.xie
 * @Date: 2020-11-14 17:59:02
 * @LastEditTime: 2021-03-15 22:40:45
 * @LastEditors: Iccccy.xie(binicey@outlook.com)
 * @FilePath: \Mechanical _Arm\src\main.cpp
 */

#include <main.h>
int setupMod = 1;
void setup()
{

    BTsetup();
    Serial.begin(9600);
}
int signalMod = 0;
//0为串口，1为蓝牙
void loop()
{
    //主菜单入口
    command();
}