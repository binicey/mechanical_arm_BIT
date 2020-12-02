/*
 * @Author: Iccccy.xie(binicey@outlook.com) 
 * @Date: 2020-11-14 17:59:11 
 * @Last Modified by:   Iccccy.xie(binicey@outlook.com) 
 * @Last Modified time: 2020-11-14 17:59:11 
 */
//设置电机引脚
int SEPPER_X = 1;
int SEPPER_F = 2;
int STPPER_W = 3;
int SERVO = 4;
// 机械臂初始位置的确定

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

// 手动操控模式函数集合
//向上运动
void ARM_UP_move(int data)
{
    // 参数检验

    Serial.println(data);
}
//向下
void ARM_DOWN_move(int data)
{
    Serial.println(data);
}
//向右转动
void ARM_RIGHT_move(int data)
{
    Serial.println(data);
}
//向左转动
void ARM_LEFT_move(int data)
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
// 预设运动模式
// 对应5个位置有个参数
