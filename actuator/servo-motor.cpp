#include <stdio.h>
#include <unistd.h>
#include "ce_ao.h"
using namespace std;
int main()
{
    CE_Ao smotor(0,0);//pwmchip0,pwm0
	int duty = 0;
	int angle = 0;
    printf("Moving servo motor from -90 deg to +90 deg.\n");
	smotor.Period(20000000);//20 ms -> 50 Hz
	smotor.Duty(600000);//0.6 ms for -90
	smotor.Enable(true);
	usleep(3000000);
	for (int i = -9; i <= 9; i++) {
		duty = 100000 * (i+15);
		//-90 deg to 90 deg corresponds to 600000 to 2400000
		angle = i*10;
		smotor.Duty(duty);
		printf("Angle = %d \n", angle);
		usleep(1000000);//wait
	}
	smotor.Enable(false);
    return 0;
}
