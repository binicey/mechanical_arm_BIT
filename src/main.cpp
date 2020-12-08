/*
 * @Author: Iccccy.xie(binicey@outlook.com) 
 * @Date: 2020-11-14 17:59:02 
 * @Last Modified by:   Iccccy.xie(binicey@outlook.com) 
 * @Last Modified time: 2020-11-14 17:59:02 
 */

#include <main.h>
extern void BTsetup();
extern void BT_main();
extern AccelStepper stepperX;
// BTsetup(BT_RX,BT_TX);
void setup()
{
    pinMode(7,OUTPUT);
    // initialize digital pin LED_BUILTIN as an output.
    BTsetup();
    Serial.begin(9600);
}
// the loop function runs over and over again forever
void loop()
{ // wait for a second
    BT_main();
}