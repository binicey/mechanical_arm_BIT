/*** 
 * @Author: Iccccy.xie
 * @Date: 2020-11-14 16:00:26
 * @LastEditTime: 2021-04-07 18:36:14
 * @LastEditors: Iccccy.xie(binicey@outlook.com)
 * @FilePath: \Mechanical _Arm\include\stepperMod.h
 */
#include <AccelStepper.h>
#include <servo.h>
extern void servoInitArm();
extern void commandPrint(String a);
//Ӳ���汾
extern int setupMod;

//�洢�������ֵ(constָ������ֵΪ����,������ֵ�ڳ��������в��ܸı�)
//2000��Ϊ90�ȣ�һ��Ϊ23��
//���õ������
const int enablePin = 1;
//x��y������м��������ٱ�1��20
const int stepper_de = 23;
const int Stepper_x_direction = 5;
const int Stepper_x = 2;
const int Stepper_y_direction = 7;
const int Stepper_y = 4;
//z���Ϊ���ּ��٣����ٱ�Ϊ1��4
const int stepper_de_z = 4 * 2;
const int Stepper_z_direction = 6;
const int Stepper_z = 3;
const int SERVO = 9;
// int servo_output=11;
Servo claw;
//�ⲿ��������
extern void BT_ERROR(int Error3_NUM);
// �����������
// AccelStepper stepperX(8, 8, 10, 9, 11);
AccelStepper stepperX(1, Stepper_x, Stepper_x_direction);
AccelStepper stepperY(1, Stepper_y, Stepper_y_direction);
AccelStepper stepperZ(1, Stepper_z, Stepper_z_direction);
//������ٶȶ���
int stepperSpeed = 500;
int stepperAccel = 200;
int stepperSpeedZ = 500;
int stepperAccelZ = 200;
//�������ٶȶ���

// ���Ƶ�����ŵĳ�ʼ��
const int clawMin = 0;
const int clawMax = 120;

void stepperSetup(int setupMod)
{

    // �������
    pinMode(Stepper_x, OUTPUT);
    pinMode(Stepper_y, OUTPUT);
    pinMode(Stepper_z, OUTPUT);
    pinMode(Stepper_x_direction, OUTPUT);
    pinMode(Stepper_z_direction, OUTPUT);
    pinMode(Stepper_z_direction, OUTPUT);
    pinMode(SERVO, OUTPUT);
    // pinMode(servo_output,OUTPUT);
    // digitalWrite(servo_output,HIGH);
    // ��������
    pinMode(enablePin, OUTPUT);
    //���õ���ٶ�
    stepperX.setAcceleration(stepperSpeed);
    stepperX.setSpeed(stepperAccel);
    stepperY.setAcceleration(stepperSpeed);
    stepperY.setSpeed(stepperAccel);
    stepperZ.setAcceleration(stepperSpeedZ);
    stepperZ.setSpeed(stepperAccelZ);
    //���ö������
    claw.attach(SERVO);
    claw.write(clawMin);
    delay(1000);
    // stepperX.runToNewPosition(2000);

    // stepperY.runToNewPosition(2000);

    // stepperZ.runToNewPosition(2000);
    // commandPrint("success\n");
    delay(1000);
    // stepArmInit();
}
//������������
long int baseMin = -38000; //����
long int baseMax = 38000;
const int rArmMin = -2500; //����
const int rArmMax = 2500;
const int fArmMin = -2500; //����
const int fArmMax = 2500;

int DSD = 15;

int moveStep = 44 * 1;
int baseJoyPos;
int rArmJoyPos;
int fArmJoyPos;
int clawJoyPos;
void servoCmd(char servoName, long int toPos, int servoDelay);
void servo_armLeft()
{
    Serial.println("Received Command: Base Turn Left");
    baseJoyPos = stepperZ.currentPosition() - moveStep * 4;

    servoCmd('b', baseJoyPos, DSD);
}

void servo_armRight()
{

    Serial.println("Received Command: Base Turn Right");
    baseJoyPos = stepperZ.currentPosition() + moveStep * 4;
    // commandPrint(String(stepperZ.currentPosition()));
    servoCmd('b', baseJoyPos, DSD);
}

void servo_armDown()
{

    Serial.println("Received Command: Rear Arm Down");
    rArmJoyPos = stepperY.currentPosition() + moveStep;
    servoCmd('r', rArmJoyPos, DSD);
}
void servo_armUp()
{
    Serial.println("Received Command: Rear Arm Up");
    rArmJoyPos = stepperY.currentPosition() - moveStep;
    servoCmd('r', rArmJoyPos, DSD);
}

void servo_armForward()
{
    Serial.println("Received Command: Front Arm Up");
    fArmJoyPos = stepperX.currentPosition() + moveStep;
    servoCmd('f', fArmJoyPos, DSD);
}

void servo_armBack()
{
    Serial.println("Received Command: Front Arm Down");
    fArmJoyPos = stepperX.currentPosition() - moveStep;
    servoCmd('f', fArmJoyPos, DSD);
}
int clawMoveStep = 3;
void servo_armClawOff()
{
    Serial.println("Received Command: Claw Close Down");
    clawJoyPos = claw.read() + clawMoveStep;
    servoCmd('c', clawJoyPos, DSD);
}

void servo_armClawOn()
{
    Serial.println("Received Command: Claw Open Up");
    clawJoyPos = claw.read() - clawMoveStep;
    servoCmd('c', clawJoyPos, DSD);
}

//ָ�������������
void servo_armForwardAndBack(int data)
{
    servoCmd('f', data, DSD);
}
void servo_armleftAndRight(long int data)
{
    servoCmd('b', data, DSD);
}
void servo_armUpAndDown(int data)
{
    servoCmd('r', data, DSD);
}

void servo_armClaw(int data)
{
    servoCmd('c', data, DSD);
}

//�������������
void servoCmd(char servoName, long toPos, int servoDelay)
{
    // AccelStepper servo2go; //����servo����

    //���ڼ������������ָ����Ϣ
    Serial.println("");
    Serial.print("+Command: Servo ");
    Serial.print(servoName);
    Serial.print(" to ");
    Serial.print(toPos);
    Serial.print(" at servoDelay value ");
    Serial.print(servoDelay);
    Serial.println(".");
    Serial.println("");

    int fromPos; //�����������洢�����ʼ�˶��Ƕ�ֵ

    switch (servoName)
    {
    case 'b':
        if (toPos >= baseMin && toPos <= baseMax)
        {
            // servo2go = stepperZ;
            // fromPos = stepperZ.currentPosition(); // ��ȡ��ǰ����Ƕ�ֵ���ڡ�����˶���ʼ�Ƕ�ֵ��
            stepperZ.runToNewPosition(toPos);
            break;
        }
        else
        {
            Serial.println("+Warning: stepperZ Value Out Of Limit!");
            return;
        }

    case 'c':
        if (toPos >= clawMin && toPos <= clawMax)
        {
            Servo servo2go;
            servo2go = claw;
            fromPos = claw.read(); // ��ȡ��ǰ����Ƕ�ֵ���ڡ�����˶���ʼ�Ƕ�ֵ��
            //ָ�ӵ������
            if (fromPos <= toPos)
            { //�������ʼ�Ƕ�ֵ��С�ڡ�Ŀ��Ƕ�ֵ��
                for (int i = fromPos; i <= toPos; i++)
                {
                    servo2go.write(i);
                    delay(servoDelay);
                }
            }
            else
            { //������ʼ�Ƕ�ֵ�����ڡ�Ŀ��Ƕ�ֵ��
                for (int i = fromPos; i >= toPos; i--)
                {
                    servo2go.write(i);
                    delay(servoDelay);
                }
            }
            return;
        }
        else
        {
            Serial.println("+Warning: Claw Servo Value Out Of Limit!");
            return;
        }

    case 'f':
        if (toPos >= fArmMin && toPos <= fArmMax)
        {
            // servo2go = stepperX;
            // fromPos = stepperX.currentPosition(); // ��ȡ��ǰ����Ƕ�ֵ���ڡ�����˶���ʼ�Ƕ�ֵ��
            stepperX.runToNewPosition(toPos);
            // commandPrint("success\n");
            break;
        }
        else
        {
            Serial.println("+Warning: stepperX Value Out Of Limit!");
            return;
        }

    case 'r':
        if (toPos >= rArmMin && toPos <= rArmMax)
        {
            // servo2go = stepperY;
            // fromPos = stepperY.currentPosition(); // ��ȡ��ǰ����Ƕ�ֵ���ڡ�����˶���ʼ�Ƕ�ֵ��
            stepperY.runToNewPosition(toPos);
            // Serial.println(String(toPos));
            break;
        }
        else
        {
            Serial.println("+Warning: stepperY Value Out Of Limit!");
            return;
        }
    }

    //ָ�ӵ������
    // servo2go.runToNewPosition(toPos);

    // while (1)
    // {
    //     servo2go.run();
    //     if (servo2go.currentPosition() == toPos)
    //         break;
    // }
    // commandPrint(String(servo2go.currentPosition()));
}

// //������ư忪��
// void adminControl(bool data)
// {
//     if (data == true)
//     {
//         digitalWrite(enablePin, LOW);
//     }
//     else
//     {
//         digitalWrite(enablePin, HIGH);
//     }
// }

// ��е�۳�ʼλ�õ�ȷ��
extern void commandError();

void initPosition(int stepperNUM, int data)
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
        commandPrint("Init Success!\n");
        break;
    default:
        commandError();
        break;
    }
}
// // �������˶����
// void ARMError()
// {
//     String ErrorMessage = "Invalid Argument!";
//     Serial.println(ErrorMessage);
//     // BT.println(ErrorMessage);
// }

// // ����Ԥ������ģʽ
// // ����ģʽ�������趨
// void ARM_setted_mod()
// {
//     Serial.println("setedMod ON");
//     //�����벽������
//     int commend[1] = {1};
//     int data[1] = {1};
//     int time[1] = {1};
//     //x,y,z�ֱ��Ӧ�����������ת�������Ϊת��
//     // ����Ϊ��ת������Ϊ��ת����������ϵ�������룩
//     // kΪ��צ��������
//     // 1Ϊ�ӽ���0Ϊ�ɿ�

//     for (int i = 0; i < sizeof(commend) / sizeof(int); i++)
//     {
//         switch (commend[i])
//         {
//         case 'x':
//             /* code */
//             break;
//         case 'y':
//             /* code */
//             break;
//         case 'z':
//             /* code */
//             break;
//         case 'k':
//             /* code */
//             break;
//         default:
//             ARMError();
//             break;
//         }
//     }
// }

void reportStatus()
{ //���״̬��Ϣ
    Serial.println("");
    Serial.println("");
    Serial.println("+ Robot-Arm Status Report +");
    Serial.print("Claw Position: ");
    Serial.println(claw.read());
    Serial.print("Base Position: ");
    Serial.println(stepperZ.currentPosition());
    Serial.print("Rear  Arm Position:");
    Serial.println(stepperY.currentPosition());
    Serial.print("Front Arm Position:");
    Serial.println(stepperX.currentPosition());
    Serial.println("++++++++++++++++++++++++++");
    Serial.println("");
}
//���в���
void part1()
{
    long robotIniPosArray2[40][2] = {
        //ץȡ�ڶ�������
        {'b', 2600},
        {'r', -290},
        {'f', 1850},
        {'r', 50},
        {'f', 1900},
        {'r', 20},
        {'f', 1982},
        {'c', 100},
        {'f', 0},
        {'r', -1000},
        {'b', 29165},
        {'r', -50},
        {'f', 1912},
        {'c', 0},
        {'r', -290},
        {'f', 1824},
        {'r', -264},
        {'f', 1850},
        {'f', 0},
        {'r', -1000},
        //ץȡ����������
        {'b', 0},
        {'f', 1500},
        {'r', -100},
        {'f', 1750},
        {'r', 0},
        {'c', 90},
        {'f', 0},
        {'r', -1000},
        {'b', 32000},
        {'r', 90},
        {'f', 1750},
        {'r', 0},
        {'c', 20},
        {'f', 1500},
        {'r', -100},
        {'f', 0},
        {'r', -1000},
    };
    for (int i = 0; i < 40; i++)
    {
        servoCmd(robotIniPosArray2[i][0], robotIniPosArray2[i][1], 15);
    };
}
void part2()
{
    long robotIniPosArray3[44][3] = {
        // //ץȡ���ĸ�����
        {'b', -5250},
        {'r', -264},
        {'f', 2024},
        {'r', -350},
        {'f', 2100},
        {'r', -166},
        {'f', 2200},
        {'c', 100},
        {'f', 0},
        {'r', -1000},
        {'b', -26650},
        {'r', -166},
        {'f', 2332},
        {'c', 0},
        {'r', -350},
        {'f', 2100},
        {'r', -264},
        {'f', 2024},
        {'f', 0},
        {'r', -1000},
        //ץȡ���������
        {'b', -2800},
        {'r', -290},
        {'f', 1850},
        {'r', -100},
        {'f', 1900},
        {'r', 20},
        {'f', 1982},
        {'c', 100},
        {'f', 0},
        {'r', -1000},
        {'b', -29165},
        {'r', -50},
        {'f', 1912},
        {'c', 0},
        {'r', -290},
        {'f', 1824},
        {'r', -264},
        {'f', 1850},
        {'f', 0},
        {'r', -1000},
        //�ظ���ʼ״̬
        {'f', 0},
        {'r', 0},
        {'c', 0},
        {'b', 0},
    };
    for (int i = 0; i < 44; i++)
    {
        servoCmd(robotIniPosArray3[i][0], robotIniPosArray3[i][1], 15);
    }
}
void part0()
{
    long robotIniPosArray1[24][3] = {
        //�ظ���ʼ״̬
        {'f', 0},
        {'r', 0},
        {'c', 20},
        {'b', 0},
        //ץȡ��һ������
        {'b', 5174},
        {'r', -264},
        {'f', 2024},
        {'r', -350},
        {'f', 2100},
        {'r', -166},
        {'f', 2332},
        {'c', 100},
        {'f', 0},
        {'r', -1000},
        {'b', 26650},
        {'r', -166},
        {'f', 2332},
        {'c', 0},
        {'r', -350},
        {'f', 2100},
        {'r', -264},
        {'f', 2024},
        {'f', 0},
        {'r', -1000}};

    for (int i = 0; i < 24; i++)
    {
        servoCmd(robotIniPosArray1[i][0], robotIniPosArray1[i][1], 15);
    }
}
int armSetedMod()
{
    Serial.println("+Command:settedMod ON");
    part0();
    part1();
    part2();

    return 0;
}
void initArm()
{
    servoCmd('b', 0, 0);
    servoCmd('r', 0, 0);
    servoCmd('f', 0, 0);
    servoCmd('c', 0, 15);
}
// // �ֶ��ٿ�ģʽ���������о�
// // moveto(����λ��)
// // move(���λ��)
// // setMaxSpeed(speed)
// // ����speed��λ�ǲ�/����
// // targetPosition()
// // distanceToGo()

// void stepperAllInOne(int dataX, int dataY, int dataZ)
// {
//     //data���ýǶ�����
//     int stepX = stepperX.currentPosition() + int(200 * stepper_de * dataX);
//     int stepY = stepperY.currentPosition() + int(200 * stepper_de * dataY);
//     int stepZ = stepperZ.currentPosition() + int(200 * stepper_de_z * dataZ);

//     stepperX.moveTo(stepX);
//     stepperY.moveTo(stepY);
//     stepperZ.moveTo(stepZ);
//     while (stepperX.currentPosition() != stepX || stepperY.currentPosition() != stepY || stepperZ.currentPosition() != stepZ)
//     {
//         // Serial.println(stepperX.currentPosition());
//         // if (stepperX.currentPosition() != stepX)
//         stepperX.run();
//         // if (stepperY.currentPosition() != stepY)
//         stepperY.run();
//         // if (stepperZ.currentPosition() != stepZ)
//         stepperZ.run();
//     }
// }

// //ǰ���˶�
// void ARM_ForwordAndBack_move(int data)
// {
//     int One_step = 20;
//     if (data == 0)
//     {

//         int step = stepperX.currentPosition() + One_step;
//         stepperX.moveTo(step);
//         while (stepperX.currentPosition() != step)
//         {
//             // Serial.println(stepperY.currentPosition());
//             stepperX.run();
//         }
//         // Serial.println(stepperY.currentPosition());
//     }
//     else if (data == 1)
//     {
//         int step = stepperX.currentPosition() - One_step;
//         stepperX.moveTo(step);
//         while (stepperX.currentPosition() != step)
//         {
//             // Serial.println(stepperY.currentPosition());
//             stepperX.run();
//         }
//         // Serial.println(stepperX.currentPosition());
//     }
//     else
//     {
//         ARMError();
//     }
// }
// //�����˶�
// void ARM_UpAndDown_move(int data)
// {
//     int One_step = 20;
//     if (data == 0)
//     {

//         int step = stepperY.currentPosition() + One_step;
//         stepperY.moveTo(step);
//         while (stepperY.currentPosition() != step)
//         {
//             // Serial.println(stepperY.currentPosition());
//             stepperY.run();
//         }
//         // Serial.println(stepperY.currentPosition());
//     }
//     else if (data == 1)
//     {
//         int step = stepperY.currentPosition() - One_step;
//         stepperX.moveTo(step);
//         while (stepperY.currentPosition() != step)
//         {
//             // Serial.println(stepperY.currentPosition());
//             stepperY.run();
//         }
//         // Serial.println(stepperX.currentPosition());
//     }
//     else
//     {
//         ARMError();
//     }
// }
// //����ת��
// void ARM_RightAndLeft_move(int data)
// {
//     int One_step = 20;
//     if (data == 0)
//     {

//         int step = stepperZ.currentPosition() + One_step;
//         stepperZ.moveTo(step);
//         while (stepperZ.currentPosition() != step)
//         {
//             // Serial.println(stepperY.currentPosition());
//             stepperZ.run();
//         }
//         // Serial.println(stepperY.currentPosition());
//     }
//     else if (data == 1)
//     {
//         int step = stepperZ.currentPosition() - One_step;
//         stepperZ.moveTo(step);
//         while (stepperZ.currentPosition() != step)
//         {
//             // Serial.println(stepperY.currentPosition());
//             stepperZ.run();
//         }
//         // Serial.println(stepperX.currentPosition());
//     }
//     else
//     {
//         ARMError();
//     }
// }
// //������ƺ���
// //contributed by HuanMu
// void armClaw(int data)
// {
//     int limitation = 70;
//     // int pos=0;
//     //0Ϊ�ſ�
//     //1Ϊ�ӽ�
//     if (data == 1)
//     {
//         Serial.print("data=");
//         Serial.println(myservo.read());
//         if (myservo.read() == limitation)
//         {
//             ARMError();
//             return;
//         }
//         Serial.println("Claw close");
//         // for (int pos = 0; pos <= limitation; pos += 5)
//         // { // 0��ת��70��
//         //     // ÿһ������1��
//         //     myservo.write(pos); // �����ŷ�����ﵽ'pos'�����ĽǶ�
//         //     // Serial.println(pos);
//         //     delay(100);
//         // }
//         myservo.write(0);
//         delay(1000);
//     }
//     else if (data == 0)
//     {
//         Serial.println("Claw open");
//         Serial.print("data=");
//         Serial.println(myservo.read());
//         if (myservo.read() == 0)
//         {
//             ARMError();
//             return;
//         }

//         // for (int pos = limitation; pos >= 0; pos -= 5)
//         // {                       // 70��ת��0��
//         //     myservo.write(pos); // �����ŷ�����ﵽ'pos'�����ĽǶ�
//         //     // Serial.println(pos);
//         //     delay(100);
//         // }
//         myservo.write(limitation);
//         delay(1000);
//     }
//     else
//     {
//         ARMError();
//     }
// }

// void testfun()
// {
//     int data[4] = {50, -50, 50, -50};
//     for (int i = 0; i < 4; i++)
//     {
//         stepperAllInOne(data[i], data[i], data[i]);
//     }
// }
// void testfun1()
// {
//     myservo.write(0);
//     Serial.print("data=");
//     Serial.println(myservo.read());
// }
