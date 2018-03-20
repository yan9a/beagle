#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
int main()
{
    string cmdstr="mpack -s \"Test c++ subject\" /home/debian/sendemail/emailbody.txt yan9aye@gmail.com";
    int r=system(cmdstr.c_str());
    cout<<cmdstr<<endl;
    cout<<"Return: "<<r<<endl;
    return r;
}
