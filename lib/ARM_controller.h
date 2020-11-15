/*
 * @Author: Iccccy.xie(binicey@outlook.com) 
 * @Date: 2020-11-14 17:59:11 
 * @Last Modified by:   Iccccy.xie(binicey@outlook.com) 
 * @Last Modified time: 2020-11-14 17:59:11 
 */
#include<AccelStepper.h>
#include<setup.h>
int SEPPER_X=1;
int SEPPER_F=2;
int STPPER_W=3;
int SERVO=4;
void ARM_UP_move(int data)
{
    Serial.println(data);
}
void ARM_DOWN_move(int data)
{
    Serial.println(data);
}
void ARM_RIGHT_move(int data)
{
    Serial.println(data);
}
void ARM_LEFT_move(int data)
{
    Serial.println(data);
}