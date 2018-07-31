#include <stdio.h>
#include <unistd.h>
#include "ce_ao.h"
#include "ce_io.h"
using namespace std;
int main()
{
    CE_Ao dcmotor(0,0);//pwmchip0,pwm0    
    CE_IO dir(60,OUTPUT);// GPIO_60 as output
	int duty = 0;
    printf("Driving DC motor from 0 percent to 100 percent full speed.\n");
	dcmotor.Period(10000000);//10 ms -> 100 Hz
	dcmotor.Duty(0);
	dcmotor.Enable(true);
	usleep(1000000);
    
    dir.Write(LOW);
    printf("Forward direction.\n");
	for (int i = 0; i <= 10; i++) {
		duty = 1000000 * i;// 1 ms duty of 10 ms period => 10% full speed
		dcmotor.Duty(duty);
		printf("Percent FS = %d \n", i*10);
		usleep(1000000);//wait
	}
    
    dir.Write(HIGH);
    printf("Reverse direction.\n");
	for (int i = 0; i <= 10; i++) {
		duty = 1000000 * (10-i);// 1 ms duty of 10 ms period => 10% full speed
		dcmotor.Duty(duty);
		printf("Percent FS = %d \n", (10-i)*10);
		usleep(1000000);//wait
	}
	dcmotor.Enable(false);
    return 0;
}
