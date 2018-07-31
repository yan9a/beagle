#include <stdio.h>
#include <unistd.h>
#include "ce_ai.h"
using namespace std;
int main()
{
    CE_Ai tsensor(4);
	int n;
	float v, t;
    for(int i=0;i<10;i++){
		n = tsensor.Read();
		v = 1.8*float(n)/ 4095;
		t = (float(n)*1.8 - 2047.5) / 40.95;
        printf("n= %d v=%f t=%f\n",n,v,t);
        usleep(1000000);
    }
    return 0;
}
