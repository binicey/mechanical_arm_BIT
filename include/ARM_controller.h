/*
 * @Author: Iccccy.xie(binicey@outlook.com) 
 * @Date: 2020-11-14 17:59:11 
 * @Last Modified by:   Iccccy.xie(binicey@outlook.com) 
 * @Last Modified time: 2020-11-14 17:59:11 
 */
//设置电机引脚
#include <AccelStepper.h>
const int enablePin = 8;
//x与y电机加有减速器减速比1：20
const int stepper_de = 20;
const int Stepper_x_direction = 10;
const int Stepper_x = 8;
const int Stepper_y_direction = 0;
const int Stepper_y = 0;
//z电机为带轮减速，减速比为1：4
const int stepper_de_z = 0;
const int Stepper_z_direction = 0;
const int Stepper_z = 0;
const int SERVO = 0;
//外部函数声明
extern void BT_ERROR(int Error_NUM);
// 建立电机对象
AccelStepper stepperX(8, 8, 10, 9, 11);
// AccelStepper stepperX(8, Stepper_x, Stepper_x_direction);
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
void ARM_setted_mod(int data)
{
    Serial.println(data);
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
    int One_step = 1;
    if (data > 0)
    {
        Serial.println(stepperX.currentPosition());
        stepperX.moveTo(data);
        stepperX.setAcceleration(500.0);
        stepperX.setSpeed(2000.0);
        while (stepperX.currentPosition() != data)
        {
            // Serial.println(stepperX.currentPosition());
            stepperX.run();
        }
            Serial.println(stepperX.currentPosition());
    }
}
//上下运动
void ARM_UpAndDown_move(int data)
{
    // 参数检验
    if (data == 1)
    {
    }
    Serial.println(data);
}
//左右转动
void ARM_RightAndLeft_move(int data)
{
    Serial.println(data);
}
//钳爪控制函数集合
void armClaw(int data)
{
    //0为张开
    //1为加紧
    if (data == 1)
    {
        Serial.println("Claw close");
    }
    else if (data == 0)
    {
        Serial.println("Claw open");
    }
    else
    {
        ARMError();
    }
}
