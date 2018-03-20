#ifndef CE_I2C_H
#define CE_I2C_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

//http://elinux.org/Interfacing_with_I2C_Devices

class CE_I2C
{
    public:
        CE_I2C();
        CE_I2C(int bus_id,int slave_address);
        virtual ~CE_I2C();
        bool Begin(int bus_id,int slave_address);
        bool Write(char* buf,int n);
        bool Read(char* buf,int n);
    private:
        int fd;
};

#endif // CE_I2C_H
