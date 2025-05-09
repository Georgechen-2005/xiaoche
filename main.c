#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "pid.h"
#include "Motor.h"
#include "OLED.h"
#include "Key.h"
#include "Encoder.h"
#include "PWM.h"
#include "math.h"
uint8_t KeyNum;
int8_t Speed;

PID_t wheel1;
PID_t wheel2;
PID_t wheel3;

static PID_t wheel1 = {
	.Target = 0,
  .Kp = 8,
	.Ki = 3,
	.Kd = 3,
  .OutMax = 1000,
  .OutMin = -1000,
};

static PID_t wheel2 = {
	.Target = 0,
  .Kp = 8,
	.Ki = 3,
	.Kd = 3,
  .OutMax = 1000,
  .OutMin = -1000,
};

static PID_t wheel3 = {
	.Target = 0,
  .Kp = 8,
	.Ki = 3,
	.Kd = 3,
  .OutMax = 1000,
  .OutMin = -1000,
};

int main(void)
{
	
	extern void pid_update(PID_t wheel);
	float wheel1speed,wheel2speed,wheel3speed;
		
	int side =1;

	OLED_Init();
	PWM_Init();
	Motor_Init();

	while (1)
	{
		Encoder1_Init();
		wheel1.Actual  = GETEncoderspeed1();
		Encoder2_Init();
		wheel2.Actual  = GETEncoderspeed2();
		Encoder3_Init(); 
		wheel3.Actual  = GETEncoderspeed3();

		
			if(side ==1){
				wheel1speed=500;
				wheel2speed=0;
				wheel3speed=-500;
      wheel1.Target =wheel1speed ;
			wheel2.Target =wheel2speed ;
			wheel3.Target =wheel3speed ;
			PID_Update(&wheel1);
			PID_Update(&wheel2);
			PID_Update(&wheel3);
			Motor_SetSpeed1(wheel1.Out);
			Motor_SetSpeed2(wheel2.Out);
			Motor_SetSpeed3(wheel3.Out);

							Delay_s(2);
				side++;
			}
			if (side==2){
				wheel2speed=500;
			wheel2.Target =wheel2speed ;
			PID_Update(&wheel2);
			Motor_SetSpeed1(-50);
			Motor_SetSpeed2(wheel2.Out);
			Motor_SetSpeed3(-50);		
					Delay_s(2);
				side++;
			}
				if (side==3){
				wheel1speed=-500;
				wheel2speed=0;
				wheel3speed=500;
      wheel1.Target =wheel1speed ;
			wheel2.Target =wheel2speed ;
			wheel3.Target =wheel3speed ;
			PID_Update(&wheel1);
			PID_Update(&wheel2);
			PID_Update(&wheel3);
			Motor_SetSpeed1(wheel1.Out);
			Motor_SetSpeed2(wheel2.Out);
			Motor_SetSpeed3(wheel3.Out);

						Delay_s(2);
				side++;
			}
				if(side==4) {
				wheel2speed=-500;
			wheel2.Target =wheel2speed ;
			PID_Update(&wheel2);
			Motor_SetSpeed1(50);
			Motor_SetSpeed2(wheel2.Out);
			Motor_SetSpeed3(50);
						Delay_s(2);
			side++;
				}
			if(side == 5)
			{
			Motor_SetSpeed1(0);
			Motor_SetSpeed2(0);
			Motor_SetSpeed3(0);
				Delay_s(2);
				side++;
			}


		
	//三角形
			if(side ==6)
			{
				wheel1speed=-50;
				wheel2speed=500;
				wheel3speed=-50;
			wheel2.Target =wheel2speed ;
			PID_Update(&wheel2);
			Motor_SetSpeed1(-50);
			Motor_SetSpeed2(wheel2.Out);
			Motor_SetSpeed3(-50);
				Delay_s(2);
				side++;
			}
			if(side==7)
			{
				wheel1speed =500;
				wheel1.Target =wheel1speed ;
			PID_Update(&wheel1);
			Motor_SetSpeed1(wheel1.Out);
			Motor_SetSpeed2(-50);
			Motor_SetSpeed3(-50);
				Delay_s(2);
				side++;
			}
			if(side==8)
			{
				wheel3speed=500;
			wheel3.Target =wheel3speed ;
			PID_Update(&wheel3);
			Motor_SetSpeed1(-50);
			Motor_SetSpeed2(-50);
			Motor_SetSpeed3(wheel3.Out);
				Delay_s(2);
				side++;				
			}
		if(side == 9)
			{
			Motor_SetSpeed1(0);
			Motor_SetSpeed2(0);
			Motor_SetSpeed3(0);
									Delay_s(2);
				side++;
			}

			if(side == 10)
			{
			float vx;  //圆
    float vy;
    float w=1;
    float l=1;
      wheel1speed = -vx*0.5-vy*sqrt(3)*0.5+w*l;
			wheel2speed =vx+w*l;
			wheel3speed = vy*sqrt(3)*0.5-vx*0.5+w*l;

      float p=0;
			float v=50;
//			float vx,vy;
			vx = v*cos(p);
			vy=v*sin(p);
		  if(p<360)
		  {
			p+=0.01;
		  }
		  Delay_ms(10);
			wheel1.Target =wheel1speed ;
			wheel2.Target =wheel2speed ;
			wheel3.Target =wheel3speed ;
			PID_Update(&wheel1);
			PID_Update(&wheel2);
			PID_Update(&wheel3);
			Motor_SetSpeed1(wheel1.Out);
			Motor_SetSpeed2(wheel2.Out);
			Motor_SetSpeed3(wheel3.Out);
		}
  }
}
