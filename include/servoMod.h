// /*** 
//  * @Author: Iccccy.xie
//  * @Date: 2021-03-13 23:10:26
//  * @LastEditTime: 2021-03-16 15:03:40
//  * @LastEditors: Iccccy.xie(binicey@outlook.com)
//  * @FilePath: \Mechanical _Arm\include\servoMod.h
//  */
// //servoMod改编自太极创客
// /*
// MeArm机械臂控制程序-6
// by 太极创客 (2017-06-02)
// www.taichi-maker.com
 
// 本程序用于太极创客《零基础入门学用Arduino教程 - MeArm篇》。
// 1   使用串口获得电机数据,设置机械臂动作
//     将串口指令解读改写为函数,加入状态汇报函数reportStatus
// 2   加入servoCmd函数控制电机速度
// 3   加入判断人类指令是否超出舵机限值
// 4   MeArm执行一系列动作(执行程序) armIniPos - 1 （一维数组）
// 5   MeArm执行一系列动作(执行程序) armIniPos - 2 （二维数组）
// 6   加入手柄控制模式
//     加入机器判断：人类输入信息错误检查
 
// 如需要获得具体电路连接细节，请查阅太极创客制作的
// 《零基础入门学用Arduino教程 - MeArm篇》页面。
 
// */
// #include <Servo.h>            //使用servo库
// Servo base, fArm, rArm, claw; //创建4个servo对象

// //存储电机极限值(const指定该数值为常量,常量数值在程序运行中不能改变)
// const int baseMin = 0;
// const int baseMax = 180;
// const int rArmMin = 0;
// const int rArmMax = 180;
// const int fArmMin = 0;
// const int fArmMax = 180;
// const int clawMin = 0;
// const int clawMax = 60;

// int DSD = 15;     //Default Servo Delay (默认电机运动延迟时间)
//                   //此变量用于控制电机运行速度.增大此变量数值将
//                   //降低电机运行速度从而控制机械臂动作速度。
// int moveStep = 3; // 每一次按下手柄按键，舵机移动量（仅适用于手柄模式）

// // void initReturn(int xPos, int yPos, int zPos, int cPos)
// // {
// //     base.write(zPos);
// //     delay(10);
// //     fArm.write(yPos);
// //     delay(10);
// //     rArm.write(xPos);
// //     delay(10);
// //     claw.write(cPos);
// //     delay(10);
// // }
// void initArm()
// {
//     base.write(90);
//     delay(10);
//     fArm.write(90);
//     delay(10);
//     rArm.write(90);
//     delay(10);
//     claw.write(0);
//     delay(10);
// }
// void servoInitArm()
// {
//     base.attach(11); // base 伺服舵机连接引脚11 舵机代号'b'
//     delay(200);      // 稳定性等待
//     rArm.attach(10); // rArm 伺服舵机连接引脚10 舵机代号'r'
//     delay(200);      // 稳定性等待
//     fArm.attach(9);  // fArm 伺服舵机连接引脚9  舵机代号'f'
//     delay(200);      // 稳定性等待
//     claw.attach(6);  // claw 伺服舵机连接引脚6  舵机代号'c'
//     delay(200);      // 稳定性等待
//     initArm();
// }

// // void armDataCmd(char serialCmd){ //Arduino根据串行指令执行相应操作
// //                                  //指令示例：b45 底盘转到45度角度位置
// //                                  //          o 输出机械臂舵机状态信息
// //   //判断人类是否因搞错模式而输入错误的指令信息（指令模式下输入手柄按键信息）
// //   if (   serialCmd == 'w' || serialCmd == 's' || serialCmd == 'a' || serialCmd == 'd'
// //       || serialCmd == '5' || serialCmd == '4' || serialCmd == '6' || serialCmd == '8' ){
// //     Serial.println("+Warning: Robot in Instruction Mode...");
// //     delay(100);
// //     while(Serial.available()>0) char wrongCommand = Serial.read();  //清除串口缓存的错误指令
// //     return;
// //   }

// //   if (serialCmd == 'b' || serialCmd == 'c' || serialCmd == 'f' || serialCmd == 'r'){
// //     int servoData = Serial.parseInt();
// //     servoCmd(serialCmd, servoData, DSD);  // 机械臂舵机运行函数（参数：舵机名，目标角度，延迟/速度）
// //   } else {
// //     switch(serialCmd){

// //       case 'm' :   //切换至手柄模式
// //         mode = 0;
// //         Serial.println("Command: Switch to Joy-Stick Mode.");
// //         break;

// //       case 'o':  // 输出舵机状态信息
// //         reportStatus();
// //         break;

// //       case 'i':
// //         armIniPos();
// //         break;

// //       default:  //未知指令反馈
// //         Serial.println("Unknown Command.");
// //     }
// //   }
// // }

// int baseJoyPos;
// int rArmJoyPos;
// int fArmJoyPos;
// int clawJoyPos;
// void servoCmd(char servoName, int toPos, int servoDelay);
// void servo_armLeft()
// {
//     Serial.println("Received Command: Base Turn Left");
//     baseJoyPos = base.read() - moveStep;
//     servoCmd('b', baseJoyPos, DSD);
// }

// void servo_armRight()
// {

//     Serial.println("Received Command: Base Turn Right");
//     baseJoyPos = base.read() + moveStep;
//     servoCmd('b', baseJoyPos, DSD);
// }

// void servo_armDown()
// {

//     Serial.println("Received Command: Rear Arm Down");
//     rArmJoyPos = rArm.read() + moveStep;
//     servoCmd('r', rArmJoyPos, DSD);
// }
// void servo_armUp()
// {
//     Serial.println("Received Command: Rear Arm Up");
//     rArmJoyPos = rArm.read() - moveStep;
//     servoCmd('r', rArmJoyPos, DSD);
// }

// void servo_armForward()
// {
//     Serial.println("Received Command: Front Arm Up");
//     fArmJoyPos = fArm.read() + moveStep;
//     servoCmd('f', fArmJoyPos, DSD);
// }

// void servo_armBack()
// {
//     Serial.println("Received Command: Front Arm Down");
//     fArmJoyPos = fArm.read() - moveStep;
//     servoCmd('f', fArmJoyPos, DSD);
// }

// void servo_armClawOff()
// {
//     Serial.println("Received Command: Claw Close Down");
//     clawJoyPos = claw.read() + moveStep;
//     servoCmd('c', clawJoyPos, DSD);
// }

// void servo_armClawOn()
// {
//     Serial.println("Received Command: Claw Open Up");
//     clawJoyPos = claw.read() - moveStep;
//     servoCmd('c', clawJoyPos, DSD);
// }

// //指令操作函数定义
// void servo_armForwardAndBack(int data)
// {
//     servoCmd('f', data, DSD);
// }
// void servo_armleftAndRight(int data)
// {
//     servoCmd('b', data, DSD);
// }
// void servo_armUpAndDown(int data)
// {
//     servoCmd('r', rArmJoyPos, DSD);
// }

// void servo_armClaw(int data)
// {
//     servoCmd('c', data, DSD);
// }

// void servoCmd(char servoName, int toPos, int servoDelay)
// {
//     Servo servo2go; //创建servo对象

//     //串口监视器输出接收指令信息
//     Serial.println("");
//     Serial.print("+Command: Servo ");
//     Serial.print(servoName);
//     Serial.print(" to ");
//     Serial.print(toPos);
//     Serial.print(" at servoDelay value ");
//     Serial.print(servoDelay);
//     Serial.println(".");
//     Serial.println("");

//     int fromPos; //建立变量，存储电机起始运动角度值

//     switch (servoName)
//     {
//     case 'b':
//         if (toPos >= baseMin && toPos <= baseMax)
//         {
//             servo2go = base;
//             fromPos = base.read(); // 获取当前电机角度值用于“电机运动起始角度值”
//             break;
//         }
//         else
//         {
//             Serial.println("+Warning: Base Servo Value Out Of Limit!");
//             return;
//         }

//     case 'c':
//         if (toPos >= clawMin && toPos <= clawMax)
//         {
//             servo2go = claw;
//             fromPos = claw.read(); // 获取当前电机角度值用于“电机运动起始角度值”
//             break;
//         }
//         else
//         {
//             Serial.println("+Warning: Claw Servo Value Out Of Limit!");
//             return;
//         }

//     case 'f':
//         if (toPos >= fArmMin && toPos <= fArmMax)
//         {
//             servo2go = fArm;
//             fromPos = fArm.read(); // 获取当前电机角度值用于“电机运动起始角度值”
//             break;
//         }
//         else
//         {
//             Serial.println("+Warning: fArm Servo Value Out Of Limit!");
//             return;
//         }

//     case 'r':
//         if (toPos >= rArmMin && toPos <= rArmMax)
//         {
//             servo2go = rArm;
//             fromPos = rArm.read(); // 获取当前电机角度值用于“电机运动起始角度值”
//             break;
//         }
//         else
//         {
//             Serial.println("+Warning: rArm Servo Value Out Of Limit!");
//             return;
//         }
//     }

//     //指挥电机运行
//     if (fromPos <= toPos)
//     { //如果“起始角度值”小于“目标角度值”
//         for (int i = fromPos; i <= toPos; i++)
//         {
//             servo2go.write(i);
//             delay(servoDelay);
//         }
//     }
//     else
//     { //否则“起始角度值”大于“目标角度值”
//         for (int i = fromPos; i >= toPos; i--)
//         {
//             servo2go.write(i);
//             delay(servoDelay);
//         }
//     }
// }


// // extern int xPos;
// // extern int yPos;
// // extern int zPos;
// // extern int cPos;


// // void servo_initCon()
// // {
// //     xPos = rArm.read();
// //     yPos = fArm.read();
// //     zPos = base.read();
// //     cPos = claw.read();
// // }
// void reportStatus()
// { //舵机状态信息
//     Serial.println("");
//     Serial.println("");
//     Serial.println("+ Robot-Arm Status Report +");
//     Serial.print("Claw Position: ");
//     Serial.println(claw.read());
//     Serial.print("Base Position: ");
//     Serial.println(base.read());
//     Serial.print("Rear  Arm Position:");
//     Serial.println(rArm.read());
//     Serial.print("Front Arm Position:");
//     Serial.println(fArm.read());
//     Serial.println("++++++++++++++++++++++++++");
//     Serial.println("");
// }

// void armIniPos()
// {
//     Serial.println("+Command: Restore Initial Position.");
//     int robotIniPosArray[4][3] = {
//         {'b', 90, DSD},
//         {'r', 90, DSD},
//         {'f', 90, DSD},
//         {'c', 90, DSD}};

//     for (int i = 0; i < 4; i++)
//     {
//         servoCmd(robotIniPosArray[i][0], robotIniPosArray[i][1], robotIniPosArray[i][2]);
//     }
// }