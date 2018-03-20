#include <stdio.h>
#include <unistd.h>
#include <string>
#include "ce_io.h"
using namespace std;
int main()
{
    CE_IO dout(23,OUTPUT);
    CE_IO din(22,INPUT);

    for(int i=0;i<5;i++){
        printf("i=%d\n",i);

        //Read input
        printf("Input= %d \n",din.Read());

        //Write output
        dout.Write(HIGH);
        printf("Output = 1");
        usleep(500000);
        dout.Write(LOW);
        printf(" > 0\n");
        usleep(500000);
    }
    return 0;
}
