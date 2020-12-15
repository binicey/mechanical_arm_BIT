/*** 
 * @Author: Iccccy.xie
 * @Date: 2020-11-14 16:00:26
 * @LastEditTime: 2020-12-15 10:08:23
 * @LastEditors: Iccccy.xie(binicey@outlook.com)
 * @FilePath: \Mechanical _Arm\include\ARM_controller.h
 */
//���õ������
#include <AccelStepper.h>
#include <servo.h>
const int enablePin = 8;
//x��y������м��������ٱ�1��20
const int stepper_de = 20;
const int Stepper_x_direction = 10;
const int Stepper_x = 8;
const int Stepper_y_direction = 0;
const int Stepper_y = 0;
//z���Ϊ���ּ��٣����ٱ�Ϊ1��4
const int stepper_de_z = 0;
const int Stepper_z_direction = 0;
const int Stepper_z = 0;
const int SERVO = 12;
Servo myservo;
//�ⲿ��������
extern void BT_ERROR(int Error_NUM);
// �����������
AccelStepper stepperX(8, 8, 10, 9, 11);
// AccelStepper stepperX(8, Stepper_x, Stepper_x_direction);
AccelStepper stepperY(1, Stepper_y, Stepper_y_direction);
AccelStepper stepperZ(1, Stepper_z, Stepper_z_direction);
// ���Ƶ�����ŵĳ�ʼ��
void stepperStup()
{
    // �������
    pinMode(Stepper_x, OUTPUT);
    pinMode(Stepper_y, OUTPUT);
    pinMode(Stepper_z, OUTPUT);
    pinMode(Stepper_x_direction, OUTPUT);
    pinMode(Stepper_z_direction, OUTPUT);
    pinMode(Stepper_z_direction, OUTPUT);
    // ��������
    pinMode(enablePin, OUTPUT);
}
//������ư忪��
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

// ��е�۳�ʼλ�õ�ȷ��
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
// �������˶����
void ARMError()
{
    String ErrorMessage = "Invalid Argument!";
    Serial.println(ErrorMessage);
}

// ����Ԥ������ģʽ
// ����ģʽ�������趨
void ARM_setted_mod()
{
    Serial.println("setedMod ON");
    //�����벽������
    int commend[1] = {1};
    int data[1] = {1};
    int time[1] = {1};
    //x,y,z�ֱ��Ӧ�����������ת�������Ϊת��
    // ����Ϊ��ת������Ϊ��ת����������ϵ�������룩
    // kΪ��צ��������
    // 1Ϊ�ӽ���0Ϊ�ɿ�

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

// �ֶ��ٿ�ģʽ���������о�
// moveto(����λ��)
// move(���λ��)
// setMaxSpeed(speed)
// ����speed��λ�ǲ�/����
// targetPosition()
// distanceToGo()

//ǰ���˶�
void ARM_ForwordAndBack_move(int data)
{
    int One_step = 10;
    if (data == 0)
    {
        int step = stepperX.currentPosition() + One_step;
        Serial.println(stepperX.currentPosition());
        stepperX.setAcceleration(500.0);
        stepperX.setSpeed(000.0);
        while (stepperX.currentPosition() != step)
        {
            // Serial.println(stepperX.currentPosition());
            stepperX.runSpeed();
        }
        Serial.println(stepperX.currentPosition());
    }
    else if (data == 1)
    {
        int step = stepperX.currentPosition() - One_step;
        Serial.println(stepperX.currentPosition());
        stepperX.setAcceleration(500.0);
        stepperX.setSpeed(000.0);
        while (stepperX.currentPosition() != step)
        {
            // Serial.println(stepperX.currentPosition());
            stepperX.runSpeed();
        }
        Serial.println(stepperX.currentPosition());
    }
    else
    {
        ARMError();
    }
}
//�����˶�
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
//����ת��
void ARM_RightAndLeft_move(int data)
{

    // ��������
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
//������ƺ���
void armClawSetup()
{
    myservo.attach(SERVO); // Servo����������9������
    myservo.write(0);
}
//contributed by HuanMu
void armClaw(int data)
{
    int limitation = 70;
    // int pos=0;
    //0Ϊ�ſ�
    //1Ϊ�ӽ�
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
        { // 0��ת��70��
            // ÿһ������1��
            myservo.write(pos); // �����ŷ�����ﵽ'pos'�����ĽǶ�
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
        {                       // 70��ת��0��
            myservo.write(pos); // �����ŷ�����ﵽ'pos'�����ĽǶ�
            // Serial.println(pos);
            delay(100);
        }
    }
    else
    {
        ARMError();
    }
}
