#include<stdio.h>
#include<unistd.h>
using namespace std;
int main(){
    printf("Starting LED blink.\n");
    FILE *f=NULL;
    const char *path="/sys/class/leds/beaglebone:green:usr3/brightness";
    for(int i=0;i<10;i++){
        if((f=fopen(path,"r+"))!=NULL){
        fwrite("1",sizeof(char),1,f);
        fclose(f);
        }
        usleep(1000000);
        if((f=fopen(path,"r+"))!=NULL){
            fwrite("0",sizeof(char),1,f);
            fclose(f);
        }
        usleep(1000000);
    }
    printf("Ending LED blink.\n");
    return 0;
}
