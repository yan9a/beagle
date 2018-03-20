#ifndef SERIAL_H
#define SERIAL_H


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>//the terminal I/O interfaces
#include <string.h>  // needed for memset
#include <sys/ioctl.h> //ioctl() call defenitions

using namespace std;
inline void delay(unsigned long ms)
{
	usleep(ms * 1000);
}

class Serial {
	long fd;//serial_fd
	char rxchar;
	char port[32];
	long baud;
public:
	Serial();
	Serial(const char* Device,long BaudRate);
	~Serial();
	long Open(void);//return 0 if success
	void Close();
	char ReadChar(bool& success);//return read char if success
	bool WriteChar(char ch);////return success flag
	bool Write(char *data);//write null terminated string and return success flag
	bool SetRTS(bool value);//return success flag
	bool SetDTR(bool value);//return success flag
	bool GetCTS(bool& success);
	bool GetDSR(bool& success);
	bool GetRI(bool& success);
	bool GetCD(bool& success);
	bool IsOpened();
	void SetPort(char* Port);// 0 for ttyS0 , add 100 for USB devices e.g. 100 for ttyUSB0
	char* GetPort();
	void SetBaudRate(long baudrate);
	long GetBaudRate();
};
#endif // SERIAL_H
