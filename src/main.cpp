/*** 
 * @Author: Iccccy.xie
 * @Date: 2020-11-14 17:59:02
 * @LastEditTime: 2021-01-06 20:52:05
 * @LastEditors: Iccccy.xie(binicey@outlook.com)
 * @FilePath: \Mechanical _Arm\src\main.cpp
 */

#include <main.h>
extern void BTsetup();
extern void BT_main();
extern AccelStepper stepperX;
// BTsetup(BT_RX,BT_TX);
void setup()
{
    stepperStup();
    pinMode(7,OUTPUT);
    // initialize digital pin LED_BUILTIN as an output.
    BTsetup();
    armClawSetup();
    Serial.begin(9600);
}
// the loop function runs over and over again forever
void loop()
{ // wait for a second
    BT_main();
}