#include <stdio.h>
#include <unistd.h>
#include <string>
#include "bbpwm.h"
using namespace std;
int main()
{
    BBPWM P9_14("P9_14");
    printf("PWM signal output at P9_14\n");
    P9_14.Period(10000);
    P9_14.Duty(5000);
    P9_14.Run(true);
    int d=0,j=0;
    for(j=0;j<10;j++){
        for(int i=0;i<10;i++){
            d=i*1000;
            P9_14.Duty(d);
            usleep(200000);
        }
        printf("Cycle %d.\n",j);
    }
    printf("%d cycles produced.\n",j);
    return 0;
}
