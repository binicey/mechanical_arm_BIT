/*
 * @Author: Iccccy.xie(binicey@outlook.com) 
 * @Date: 2020-11-14 17:59:02 
 * @Last Modified by:   Iccccy.xie(binicey@outlook.com) 
 * @Last Modified time: 2020-11-14 17:59:02 
 */

#include<main.h>
// BTsetup(BT_RX,BT_TX);
void setup()
{
    // initialize digital pin LED_BUILTIN as an output.
    BTsetup();
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}
// the loop function runs over and over again forever
void loop()
{
    // char a = Serial.read();
    Serial.println(BT_TX);
    BTsetup();
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(1000);                     // wait for a second
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    delay(1000);                     // wait for a second
}