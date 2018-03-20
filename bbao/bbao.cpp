#include <stdio.h>
#include <unistd.h>
#include "ce_ao.h"
using namespace std;
int main()
{
    CE_Ao P9_14(0,0);//pwmchip0,pwm0
    printf("PWM signal output at P9_14\n");
    P9_14.Period(1000000000);
    P9_14.Duty(500000000);
    P9_14.Enable(true);
    for(int i=0;i<10;i++) usleep(1000000);//wait 10 sec
	P9_14.Enable(false);
    return 0;
}
