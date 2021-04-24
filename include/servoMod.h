// /*** 
//  * @Author: Iccccy.xie
//  * @Date: 2021-03-13 23:10:26
//  * @LastEditTime: 2021-03-16 15:03:40
//  * @LastEditors: Iccccy.xie(binicey@outlook.com)
//  * @FilePath: \Mechanical _Arm\include\servoMod.h
//  */
// //servoMod�ı���̫������
// /*
// MeArm��е�ۿ��Ƴ���-6
// by ̫������ (2017-06-02)
// www.taichi-maker.com
 
// ����������̫�����͡����������ѧ��Arduino�̳� - MeArmƪ����
// 1   ʹ�ô��ڻ�õ������,���û�е�۶���
//     ������ָ������дΪ����,����״̬�㱨����reportStatus
// 2   ����servoCmd�������Ƶ���ٶ�
// 3   �����ж�����ָ���Ƿ񳬳������ֵ
// 4   MeArmִ��һϵ�ж���(ִ�г���) armIniPos - 1 ��һά���飩
// 5   MeArmִ��һϵ�ж���(ִ�г���) armIniPos - 2 ����ά���飩
// 6   �����ֱ�����ģʽ
//     ��������жϣ�����������Ϣ������
 
// ����Ҫ��þ����·����ϸ�ڣ������̫������������
// �����������ѧ��Arduino�̳� - MeArmƪ��ҳ�档
 
// */
// #include <Servo.h>            //ʹ��servo��
// Servo base, fArm, rArm, claw; //����4��servo����

// //�洢�������ֵ(constָ������ֵΪ����,������ֵ�ڳ��������в��ܸı�)
// const int baseMin = 0;
// const int baseMax = 180;
// const int rArmMin = 0;
// const int rArmMax = 180;
// const int fArmMin = 0;
// const int fArmMax = 180;
// const int clawMin = 0;
// const int clawMax = 60;

// int DSD = 15;     //Default Servo Delay (Ĭ�ϵ���˶��ӳ�ʱ��)
//                   //�˱������ڿ��Ƶ�������ٶ�.����˱�����ֵ��
//                   //���͵�������ٶȴӶ����ƻ�е�۶����ٶȡ�
// int moveStep = 3; // ÿһ�ΰ����ֱ�����������ƶ��������������ֱ�ģʽ��

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
//     base.attach(11); // base �ŷ������������11 �������'b'
//     delay(200);      // �ȶ��Եȴ�
//     rArm.attach(10); // rArm �ŷ������������10 �������'r'
//     delay(200);      // �ȶ��Եȴ�
//     fArm.attach(9);  // fArm �ŷ������������9  �������'f'
//     delay(200);      // �ȶ��Եȴ�
//     claw.attach(6);  // claw �ŷ������������6  �������'c'
//     delay(200);      // �ȶ��Եȴ�
//     initArm();
// }

// // void armDataCmd(char serialCmd){ //Arduino���ݴ���ָ��ִ����Ӧ����
// //                                  //ָ��ʾ����b45 ����ת��45�ȽǶ�λ��
// //                                  //          o �����е�۶��״̬��Ϣ
// //   //�ж������Ƿ�����ģʽ����������ָ����Ϣ��ָ��ģʽ�������ֱ�������Ϣ��
// //   if (   serialCmd == 'w' || serialCmd == 's' || serialCmd == 'a' || serialCmd == 'd'
// //       || serialCmd == '5' || serialCmd == '4' || serialCmd == '6' || serialCmd == '8' ){
// //     Serial.println("+Warning: Robot in Instruction Mode...");
// //     delay(100);
// //     while(Serial.available()>0) char wrongCommand = Serial.read();  //������ڻ���Ĵ���ָ��
// //     return;
// //   }

// //   if (serialCmd == 'b' || serialCmd == 'c' || serialCmd == 'f' || serialCmd == 'r'){
// //     int servoData = Serial.parseInt();
// //     servoCmd(serialCmd, servoData, DSD);  // ��е�۶�����к������������������Ŀ��Ƕȣ��ӳ�/�ٶȣ�
// //   } else {
// //     switch(serialCmd){

// //       case 'm' :   //�л����ֱ�ģʽ
// //         mode = 0;
// //         Serial.println("Command: Switch to Joy-Stick Mode.");
// //         break;

// //       case 'o':  // ������״̬��Ϣ
// //         reportStatus();
// //         break;

// //       case 'i':
// //         armIniPos();
// //         break;

// //       default:  //δָ֪���
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

// //ָ�������������
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
//     Servo servo2go; //����servo����

//     //���ڼ������������ָ����Ϣ
//     Serial.println("");
//     Serial.print("+Command: Servo ");
//     Serial.print(servoName);
//     Serial.print(" to ");
//     Serial.print(toPos);
//     Serial.print(" at servoDelay value ");
//     Serial.print(servoDelay);
//     Serial.println(".");
//     Serial.println("");

//     int fromPos; //�����������洢�����ʼ�˶��Ƕ�ֵ

//     switch (servoName)
//     {
//     case 'b':
//         if (toPos >= baseMin && toPos <= baseMax)
//         {
//             servo2go = base;
//             fromPos = base.read(); // ��ȡ��ǰ����Ƕ�ֵ���ڡ�����˶���ʼ�Ƕ�ֵ��
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
//             fromPos = claw.read(); // ��ȡ��ǰ����Ƕ�ֵ���ڡ�����˶���ʼ�Ƕ�ֵ��
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
//             fromPos = fArm.read(); // ��ȡ��ǰ����Ƕ�ֵ���ڡ�����˶���ʼ�Ƕ�ֵ��
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
//             fromPos = rArm.read(); // ��ȡ��ǰ����Ƕ�ֵ���ڡ�����˶���ʼ�Ƕ�ֵ��
//             break;
//         }
//         else
//         {
//             Serial.println("+Warning: rArm Servo Value Out Of Limit!");
//             return;
//         }
//     }

//     //ָ�ӵ������
//     if (fromPos <= toPos)
//     { //�������ʼ�Ƕ�ֵ��С�ڡ�Ŀ��Ƕ�ֵ��
//         for (int i = fromPos; i <= toPos; i++)
//         {
//             servo2go.write(i);
//             delay(servoDelay);
//         }
//     }
//     else
//     { //������ʼ�Ƕ�ֵ�����ڡ�Ŀ��Ƕ�ֵ��
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
// { //���״̬��Ϣ
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