#include "Serial.h"

Serial::Serial()
{
	fd=-1;
	strcpy(port,"/dev/ttyS0");
	baud = B9600;
}

Serial::Serial(const char* Device,long BaudRate)
{
	fd=-1;
	strcpy(port,Device);
	baud = BaudRate;
}

Serial::~Serial()
{
	Close();
}

long Serial::Open(void) {

	struct termios settings;
	memset(&settings, 0, sizeof(settings));
	settings.c_iflag = 0;
	settings.c_oflag = 0;
	settings.c_cflag = CS8 | CREAD | CLOCAL;// 8n1, see termios.h for more information
	settings.c_lflag = 0;
	settings.c_cc[VMIN] = 1;
	settings.c_cc[VTIME] = 0;

	fd = open(port, O_RDWR | O_NONBLOCK);
	if (fd == -1) {
		return -1;
	}
	cfsetospeed(&settings, baud);
	cfsetispeed(&settings, baud);

	tcsetattr(fd, TCSANOW, &settings);

	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	return 0;
}

void Serial::Close() {
	if(IsOpened()) close(fd);
	fd=-1;
}

bool Serial::IsOpened()
{
	if(fd== (-1)) return false;
	else return true;
}

void Serial::SetPort(char* Device) {
	strcpy(port,Device);
}

char* Serial::GetPort() {
	return port;
}

void Serial::SetBaudRate(long baudrate) {
	if (baudrate < 9600) baud = B4800;
	else if (baudrate < 19200) baud = B9600;
	else if (baudrate < 38400) baud = B19200;
	else if (baudrate < 57600) baud = B38400;
	else if (baudrate < 115200) baud = B57600;
	else baud = B115200;
}

long Serial::GetBaudRate() {
	long baudrate=9600;
	if (baud < B9600) baudrate =4800;
	else if (baud < B19200) baudrate =9600;
	else if (baud < B38400) baudrate = 19200;
	else if (baud < B57600) baudrate = 38400;
	else if (baud < B115200) baudrate = 57600;
	else baudrate = 115200;
	return baudrate;
}
char Serial::ReadChar(bool& success)
{
	success=false;
	if (!IsOpened()) {return 0;	}
	success=read(fd, &rxchar, 1)==1;
	return rxchar;
}

bool Serial::Write(char *data)
{
	if (!IsOpened()) {return false;	}
	long n = strlen(data);
	if (n < 0) n = 0;
	else if(n > 1024) n = 1024;
	return (write(fd, data, n)==n);
}

bool Serial::WriteChar(char ch)
{
	char s[2];
	s[0]=ch;
	s[1]=0;//null terminated
	return Write(s);
}

bool Serial::SetRTS(bool value) {
	long RTS_flag = TIOCM_RTS;
	bool success=true;
	if (value) {
		if (ioctl(fd, TIOCMBIS, &RTS_flag) == -1) success=false;//Set RTS pin
	}
	else {
		if (ioctl(fd, TIOCMBIC, &RTS_flag) == -1) success=false;//Clear RTS pin
	}
	return success;
}

bool Serial::SetDTR(bool value) {
	long DTR_flag = TIOCM_DTR;
	bool success=true;
	if (value) {
		if (ioctl(fd, TIOCMBIS, &DTR_flag) == -1) success=false;//Set RTS pin
	}
	else {
		if (ioctl(fd, TIOCMBIC, &DTR_flag) == -1) success=false;//Clear RTS pin
	}
	return success;
}

bool Serial::GetCTS(bool& success) {
	success=true;
	long status;
	if(ioctl(fd, TIOCMGET, &status)== -1) success=false;
	return ((status & TIOCM_CTS) != 0);
}

bool Serial::GetDSR(bool& success) {
	success=true;
	long status;
	if(ioctl(fd, TIOCMGET, &status)== -1) success=false;
	return ((status & TIOCM_DSR) != 0);
}

bool Serial::GetRI(bool& success) {
	success=true;
	long status;
	if(ioctl(fd, TIOCMGET, &status)== -1) success=false;
	return ((status & TIOCM_RI) != 0);
}

bool Serial::GetCD(bool& success) {
	success=true;
	long status;
	if(ioctl(fd, TIOCMGET, &status)== -1) success=false;
	return ((status & TIOCM_CD) != 0);
}
