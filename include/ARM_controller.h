/*** 
 * @Author: Iccccy.xie
 * @Date: 2020-11-14 16:00:26
 * @LastEditTime: 2021-01-08 14:26:07
 * @LastEditors: Iccccy.xie(binicey@outlook.com)
 * @FilePath: \Mechanical _Arm\include\ARM_controller.h
 */
//设置电机引脚
#include <AccelStepper.h>
#include <servo.h>
const int enablePin = 8;
//x与y电机加有减速器减速比1：20
const int stepper_de = 1;
const int Stepper_x_direction = 5;
const int Stepper_x = 2;
const int Stepper_y_direction = 6;
const int Stepper_y = 3;
//z电机为带轮减速，减速比为1：4
const int stepper_de_z = 4 * 20;
const int Stepper_z_direction = 7;
const int Stepper_z = 4;
const int SERVO = 11;
Servo myservo;
//外部函数声明
extern void BT_ERROR(int Error_NUM);
// 建立电机对象
// AccelStepper stepperX(8, 8, 10, 9, 11);
AccelStepper stepperX(1, Stepper_x, Stepper_x_direction);
AccelStepper stepperY(1, Stepper_y, Stepper_y_direction);
AccelStepper stepperZ(1, Stepper_z, Stepper_z_direction);
// 控制电机引脚的初始化
void stepperStup()
{
    // 电机引脚
    pinMode(Stepper_x, OUTPUT);
    pinMode(Stepper_y, OUTPUT);
    pinMode(Stepper_z, OUTPUT);
    pinMode(Stepper_x_direction, OUTPUT);
    pinMode(Stepper_z_direction, OUTPUT);
    pinMode(Stepper_z_direction, OUTPUT);
    // 开关引脚
    pinMode(enablePin, OUTPUT);
    //设置电机速度
    stepperX.setAcceleration(5000.0);
    stepperX.setSpeed(50000.0);
    stepperY.setAcceleration(5000.0);
    stepperY.setSpeed(50000.0);
    stepperZ.setAcceleration(5000.0);
    stepperZ.setSpeed(50000.0);
}
//电机控制板开关
void adminControl(bool data)
{
    if (data == true)
    {
        digitalWrite(enablePin, LOW);
    }
    else
    {
        digitalWrite(enablePin, HIGH);
    }
}

// 机械臂初始位置的确定
void initPosition(int stepperNUM, int data)
{
    if (data == -1)
    {

        switch (stepperNUM)
        {
        case 1:
            stepperX.setCurrentPosition(stepperX.currentPosition());
            break;
        case 2:
            stepperY.setCurrentPosition(stepperY.currentPosition());
            break;
        case 3:
            stepperZ.setCurrentPosition(stepperZ.currentPosition());
            break;
        case 4:
            stepperX.setCurrentPosition(stepperX.currentPosition());
            stepperY.setCurrentPosition(stepperY.currentPosition());
            stepperZ.setCurrentPosition(stepperZ.currentPosition());
        default:
            BT_ERROR(1);
            break;
        }
    }
    else
    {
        switch (stepperNUM)
        {
        case 1:
            stepperX.setCurrentPosition(data);
            break;
        case 2:
            stepperY.setCurrentPosition(data);
            break;
        case 3:
            stepperZ.setCurrentPosition(data);
            break;
        case 4:
            stepperX.setCurrentPosition(data);
            stepperY.setCurrentPosition(data);
            stepperZ.setCurrentPosition(data);
        default:
            BT_ERROR(1);
            break;
        }
    }
}
// 错误与运动检测
void ARMError()
{
    String ErrorMessage = "Invalid Argument!";
    Serial.println(ErrorMessage);
}

// 调用预设离线模式
// 离线模式参数的设定
void ARM_setted_mod()
{
    Serial.println("setedMod ON");
    //参数与步骤输入
    int commend[1] = {1};
    int data[1] = {1};
    int time[1] = {1};
    //x,y,z分别对应三个电机的旋转输入参数为转角
    // 正数为正转，负数为逆转（考虑坐标系参数输入）
    // k为夹爪控制命令
    // 1为加紧，0为松开

    for (int i = 0; i < sizeof(commend) / sizeof(int); i++)
    {
        switch (commend[i])
        {
        case 'x':
            /* code */
            break;
        case 'y':
            /* code */
            break;
        case 'z':
            /* code */
            break;
        case 'k':
            /* code */
            break;
        default:
            ARMError();
            break;
        }
    }
}

// 手动操控模式函数集合列举
// moveto(绝对位置)
// move(相对位置)
// setMaxSpeed(speed)
// 上述speed单位是步/分钟
// targetPosition()
// distanceToGo()

//前后运动
void ARM_ForwordAndBack_move(int data)
{
    int One_step = data * stepper_de;
    if (data < 0)
    {
        int step = stepperX.currentPosition() + One_step;
        // Serial.println(stepperX.currentPosition());
        stepperX.moveTo(step);
        stepperY.moveTo(step);
        stepperZ.moveTo(step);
        while (stepperX.currentPosition() != step)
        {
            // Serial.println(stepperX.currentPosition());
            stepperX.run();
            stepperY.run();
            stepperZ.run();
        }
        // Serial.println(stepperX.currentPosition());
    }
    else if (data > 0)
    {
        int step = stepperX.currentPosition() - One_step;
        // Serial.println(stepperX.currentPosition());
        stepperX.moveTo(step);
        stepperY.moveTo(step);
        stepperZ.moveTo(step);
        while (stepperX.currentPosition() != step)
        {
            // Serial.println(stepperX.currentPosition());
            stepperX.run();
            stepperY.run();
            stepperZ.run();
        }
        // Serial.println(stepperX.currentPosition());
    }
    else
    {
        ARMError();
    }
}
//上下运动
void ARM_UpAndDown_move(int data)
{
    Serial.println(data);
    int One_step = 10;
    if (data == 0)
    {
        int step = stepperY.currentPosition() + One_step;
        Serial.println(stepperY.currentPosition());
        stepperY.setAcceleration(500.0);
        stepperY.setSpeed(000.0);
        while (stepperY.currentPosition() != step)
        {
            // Serial.println(stepperY.currentPosition());
            stepperY.runSpeed();
        }
        Serial.println(stepperY.currentPosition());
    }
    else if (data == 1)
    {
        int step = stepperY.currentPosition() - One_step;
        Serial.println(stepperY.currentPosition());
        stepperY.setAcceleration(500.0);
        stepperY.setSpeed(000.0);
        while (stepperY.currentPosition() != step)
        {
            // Serial.println(stepperY.currentPosition());
            stepperY.runSpeed();
        }
        Serial.println(stepperY.currentPosition());
    }
    else
    {
        ARMError();
    }
}
//左右转动
void ARM_RightAndLeft_move(int data)
{

    // 参数检验
    Serial.println(data);
    int One_step = 10;
    if (data == 0)
    {
        int step = stepperZ.currentPosition() + One_step;
        Serial.println(stepperZ.currentPosition());
        stepperZ.setAcceleration(500.0);
        stepperZ.setSpeed(000.0);
        while (stepperZ.currentPosition() != step)
        {
            // Serial.println(stepperZ.currentPosition());
            stepperZ.runSpeed();
        }
        Serial.println(stepperZ.currentPosition());
    }
    else if (data == 1)
    {
        int step = stepperZ.currentPosition() - One_step;
        Serial.println(stepperZ.currentPosition());
        stepperZ.setAcceleration(500.0);
        stepperZ.setSpeed(000.0);
        while (stepperZ.currentPosition() != step)
        {
            // Serial.println(stepperZ.currentPosition());
            stepperZ.runSpeed();
        }
        Serial.println(stepperZ.currentPosition());
    }
    else
    {
        ARMError();
    }
}
//舵机控制函数
void armClawSetup()
{
    myservo.attach(SERVO); // Servo对象连接在9号引脚
    myservo.write(0);
}
//contributed by HuanMu
void armClaw(int data)
{
    int limitation = 70;
    // int pos=0;
    //0为张开
    //1为加紧
    if (data == 1)
    {
        Serial.print("data=");
        Serial.println(myservo.read());
        if (myservo.read() == limitation)
        {
            ARMError();
            return;
        }
        Serial.println("Claw close");
        for (int pos = 0; pos <= limitation; pos += 5)
        { // 0度转到70度
            // 每一步增加1度
            myservo.write(pos); // 告诉伺服电机达到'pos'变量的角度
            // Serial.println(pos);
            delay(100);
        }
    }
    else if (data == 0)
    {
        if (myservo.read() == 0)
        {
            ARMError();
            return;
        }
        Serial.println("Claw open");
        for (int pos = limitation; pos >= 0; pos -= 5)
        {                       // 70度转到0度
            myservo.write(pos); // 告诉伺服电机达到'pos'变量的角度
            // Serial.println(pos);
            delay(100);
        }
    }
    else
    {
        ARMError();
    }
}

void testfun()
{
    int moveSteps = 2000;
    stepperX.setMaxSpeed(3000.0); // 设置电机最大速度300
    stepperX.setAcceleration(200.0);
    // 控制步进电机往复运动
    stepperX.moveTo(moveSteps);
    while (stepperX.currentPosition() != moveSteps)
    {
        Serial.println("runing");
        stepperX.run(); // 1号电机运行
    }
    Serial.println("finish");
}