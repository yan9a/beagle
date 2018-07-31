#include <stdio.h>
#include <unistd.h>
#include "ce_ai.h"
using namespace std;
int main()
{
    CE_Ai ai(5);
    for(int i=0;i<60;i++){
        printf("i=%d ai= %d \n",i,ai.Read());
        usleep(1000000);
    }
    return 0;
}
