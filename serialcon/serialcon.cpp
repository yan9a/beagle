#include <stdio.h>
#include "Serial.h"
using namespace std;
int main()
{
 Serial com("/dev/ttyO4",9600);//initialize port 4 , baud rate= 9600

 printf("Opening port: %s.\n",com.GetPort());
 long r = com.Open();//return 0 if success
 if(r!=0) {
    printf("Error opening port: %s.\n",com.GetPort());
    return r;
 }

 bool successFlag;
 char s[]="Hello TTYO";
 printf("Writing: %s.\n",s);
 successFlag=com.Write(s);//write a string
 successFlag=com.WriteChar('!');//write a character

 printf("Waiting 3 seconds.\n");
 delay(3000);//delay 3 sec to wait for a character

 printf("Reading.\n");
 char c=com.ReadChar(successFlag);//read a char
 if(successFlag) printf("Rx: %c\n",c);

 bool stmp=false;

 printf("Setting RTS and reading CTS.\n");
 for(int i=0;i<5;i++){

    stmp=i%2?true:false;
    com.SetRTS(stmp);
    if(stmp) printf("RTS: 1\n");
    else printf("RTS: 0\n");
    delay(100);
    stmp=com.GetCTS(successFlag);
    if(successFlag) {
        if(stmp) printf("CTS: 1\n");
        else printf("CTS: 0\n");
    }
    delay(1000);
 }


 printf("Closing port %s.\n",com.GetPort());
 com.Close();
return 0;
}
