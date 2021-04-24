/*** 
 * @Author: Iccccy.xie
 * @Date: 2020-11-14 17:59:53
 * @LastEditTime: 2021-04-07 12:39:24
 * @LastEditors: Iccccy.xie(binicey@outlook.com)
 * @FilePath: \Mechanical _Arm\include\Command.h
 */

#include "stepperMod.h"
#include <SoftwareSerial.h>
extern int setupMod;
extern void servo_armForwardAndBack();
//通用操作函数
void armForward()
{
    if (setupMod == 1)
    {
        servo_armForward();
    }
    // else if (setupMod == 0)
    // {
    //     // step_armForward();
    // }
}
void armBack()
{

    if (setupMod == 1)
    {
        servo_armBack();
    }
    // else if (setupMod == 0)
    // {
    //     // step_armBack();
    // }
}
void armLeft()
{
    if (setupMod == 1)
    {
        servo_armLeft();
    }
    // else if (setupMod == 0)
    // {
    //     // step_armLeft();
    // }
}
void armRight()
{
    if (setupMod == 1)
    {
        servo_armRight();
    }
    // else if (setupMod == 0)
    // {
    //     // step_armRight();
    // }
}
void armUp()
{
    if (setupMod == 1)
    {
        servo_armUp();
    }
    // else if (setupMod == 0)
    // {
    //     // step_armUp();
    // }
}
void armDown()
{
    if (setupMod == 1)
    {
        servo_armDown();
    }
    // else if (setupMod == 0)
    // {
    //     // step_armDown();
    // }
}
void armClawOn()
{
    if (setupMod == 1)
    {
        servo_armClawOn();
    }
    // else if (setupMod == 0)
    // {
    //     // step_armClawOn();
    // }
}
void armClawOff()
{
    if (setupMod == 1)
    {
        servo_armClawOff();
    }
    // else if (setupMod == 0)
    // {
    //     // step_armClawOff();
    // }
}
//指令操作函数
void armForwardAndBack(int data)
{
    if (setupMod == 1)
    {
        servo_armForwardAndBack(data);
    }
    // else if (setupMod == 0)
    // {
    //     // step_armForwardAndBack();
    // }
}
extern void servo_armleftAndRight(long int data);
void armleftAndRight(int data)
{
    if (setupMod == 1)
    {
        servo_armleftAndRight(data);
    }
    // else if (setupMod == 0)
    // {
    //     // step_armleftAndRight();
    // }
}
extern void servo_armUpAndDown(int data);
void armUpAndDown(int data)
{
    if (setupMod == 1)
    {
        servo_armUpAndDown(data);
    }
    // else if (setupMod == 0)
    // {
    //     // step_armUpAndDown();
    // }
}
extern void servo_armClaw(int data);
void armClaw(int data)
{
    if (setupMod == 1)
    {
        servo_armClaw(data);
    }
    // else if (setupMod == 0)
    // {
    //     // step_armClaw();
    // }
}

//蓝牙模块部分
// 蓝牙参数的初始化
int BT_RX = 14;
int BT_TX = 15;
SoftwareSerial BT = SoftwareSerial(BT_RX, BT_TX);
// 初始化蓝牙串口
void BTsetup()
{
    BT.begin(9600);
    BT.println("online");
}

void commandPrint(String outdata);
void commandError();
int commandClean();
char commandRead();
int cmdControlMod()
{

    //CMD操作模式
    commandPrint("[CMD Control mod]\n");
    // commandPrint("f:Forward b:Back\n");
    // commandPrint("l:Left    r:Right\n");
    // commandPrint("u:Up      d:Down\n");
    // commandPrint("c:Claw On o:Claw Off\n");
    // commandPrint("e:Return to Main Menu\n");
    // commandPrint("i:set InitPosition\n");
    // commandPrint("p:report Position\n");
    delay(100);
    while (1)
    {
        char Cmd = commandRead();
        if (Cmd == 'e')
        {
            return 1;
        }
        if (Cmd == 0)
        {
            continue;
        }
        if (!(Cmd == 'm' || Cmd == 'p' || Cmd == 'i' || Cmd == 'f' || Cmd == 'b' || Cmd == 'l' || Cmd == 'r' || Cmd == 'u' || Cmd == 'd' || Cmd == 'c' || Cmd == 'o'))
        {
            commandError();
            commandClean();
            continue;
        }
        commandClean();
        switch (Cmd)
        {
        case 'm':
            initArm();
            break;
        case 'f':
            armForward();
            break;
        case 'b':
            armBack();
            break;
        case 'l':
            armLeft();
            break;
        case 'r':
            armRight();
            break;
        case 'u':
            armUp();
            break;
        case 'd':
            armDown();
            break;
        case 'c':
            armClawOn();
            break;
        case 'o':
            armClawOff();
            break;
        case 'i':
            initPosition(4, 0);
            break;
        case 'p':
            reportStatus();
            break;
        default:
            break;
        }
    }
}
long int commandDataRead(char *cmd);
int dataControlMod()
{
    // DATA操作模式
    commandPrint("[DATA Control mod]\n");
    // commandPrint("x:Forward and Back\n");
    // commandPrint("y:Left and Right\n");
    // commandPrint("z:Up and Down\n");
    // commandPrint("c:Claw On And Off\n");
    // commandPrint("(X Y Z Commands Should follow with data)\n");

    delay(100);
    while (1)
    {
        char Cmd = 0;
        long int data = -1;
        data = commandDataRead(&Cmd);
        if (Cmd == 'e')
        {
            return 1;
        }
        if (Cmd == 0)
        {
            continue;
        }
        if (!(Cmd == 'x' || Cmd == 'y' || Cmd == 'z' || Cmd == 'c'))
        {
            commandError();
            commandClean();
            continue;
        }
        commandClean();
        commandPrint("InputData:");
        commandPrint(String(data));
        commandPrint("\n");
        if (data != -1)
        {

            switch (Cmd)
            {
            case 'x':
                armForwardAndBack(data);
                break;
            case 'z':
                armleftAndRight(data);
                break;
            case 'y':
                armUpAndDown(data);
                break;
            case 'c':
                armClaw(data);
                break;
            }
        }
    }
}
//遥感操作
int X = A5;
int Y = A4;
int Z = A2;
int C = A3;
int xData = 0;
int yData = 0;
int zData = 0;
int cData = 0;
int ABControlMod()
{
    // //定义输入引脚

    // commandPrint("[Action Bars Control mod]\n");
    // // commandPrint("You can use Action Bars to control the Arm\n");
    // // commandPrint("e:Return to Main Menu\n");
    // delay(100);
    // while (1)
    // {
    //     char Cmd = 0;
    //     Cmd = commandRead();
    //     if (Cmd == 'e')
    //         return 0;
    //     xData = analogRead(X);
    //     yData = analogRead(Y);
    //     zData = analogRead(Z);
    //     cData = analogRead(C);
    //     // Serial.println(String(xData));
    //     // Serial.println(String(yData));
    //     // Serial.println(String(zData));
    //     // Serial.println(String(cData));
    //     // delay(100);
    //     if (xData <= 100)
    //         armBack();
    //     if (xData >= 900)
    //         armForward();
    //     if (yData <= 100)
    //         armDown();
    //     if (yData >= 900)
    //         armUp();
    //     if (zData <= 100)
    //         armRight();
    //     if (zData >= 900)
    //         armLeft();
    //     if (cData <= 100)
    //         armClawOff();
    //     if (cData >= 900)
    //         armClawOn();
    // }
}

// 记录和复现操作
char step[200] = "";
char *p = step;
void copyMod(char Cmd)
{
    // if (p == step)
    // {
    // }
    // *p = Cmd;
    // p++;
    // if (p - 200 == step)
    // {
    //     commandPrint("Memory Fulled!\n");
    //     return;
    // }
}

void copyPlay()
{
    // initArm();
    // Serial.print(step);
    // while (*p != '\0')
    // {
    //     // armJoyCmd(*p);
    //     p++;
    //     delay(100);
    // }
    // p = step;
}
//总体框架搭建
char commandRead()
{
    if (Serial.available() > 0)
    {

        return Serial.read();
    }
    if (BT.available() > 0)
    {
        return BT.read();
    }
    return 0;
}

long int commandDataRead(char *cmd)
{
    if (Serial.available() > 0)
    {
        *cmd = Serial.read();
        // Serial.println(*cmd);
        long int data = -1;
        data = Serial.parseInt();
        // Serial.println(String(data));
        return data;
    }
    if (BT.available() > 0)
    {
        *cmd = BT.read();
        // Serial.println(*cmd);
        long int data = -1;
        data = BT.parseInt();
        // Serial.println(String(data));
        return data;
    }

    return 0;
}

void commandPrint(String outdata)
{
    Serial.print(outdata);
    BT.print(outdata);
}

int commandClean()
{
    while (BT.available())
    {
        BT.read();
    }
    while (Serial.available())
    {
        Serial.read();
    }
    return 1;
}
void commandError()
{
    commandPrint("Command Error\n");
}
int armSetedMod();
//主菜单操作模式的选择
int commandPlayMainMenu()
{
    // commandPrint("Welcome to BIT ARM Control System!\n");
    // commandPrint("++++++++++++Main Memu+++++++++++++\n");
    // commandPrint("Please input Your Option.\n");
    // commandPrint("[CMD Control Mod]:c\n");
    // commandPrint("[Action Bars Control Mod]:a\n");
    // commandPrint("[Data Control Mod]:d\n");
    // commandPrint("[Seted Mod]:s\n");
    // commandPrint("MORE FUCNCTION WILL COMING SOON!");
    while (1)
    {
        /* code */
        int backCon = 0;
        char Cmd = 'y';
        Cmd = commandRead();
        if (Cmd == 'c')
        {
            backCon = cmdControlMod();
        }
        else if (Cmd == 'a')
        {
            backCon = ABControlMod();
        }
        else if (Cmd == 'd')
        {
            backCon = dataControlMod();
        }
        else if (Cmd == 's')
        {
            backCon = armSetedMod();
        }
        else if (Cmd == 0)
        {
            continue;
        }
        else
        {
            commandError();
        }
        if (backCon)
        {
            // commandPrint("Welcome to BIT ARM Control System!\n");
            commandPrint("++++++++++++Main Memu+++++++++++++\n");
            // commandPrint("Please input Your Option.\n");
            // commandPrint("[CMD Control Mod]:c\n");
            // commandPrint("[Action Bars Control Mod]:a\n");
            // commandPrint("[Data Control Mod]:d\n");
            // commandPrint("[Seted Mod]:s\n");
            // commandPrint("MORE FUCNCTION WILL COMING SOON!");
        }
    }
}
void initarm();
int command()
{
    //添加一个调零环节
    initarm();
    commandPlayMainMenu();
    return 0;
}
void initarm()
{
    stepperSetup(setupMod);
}
