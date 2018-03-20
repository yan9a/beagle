#ifndef CESPI_H
#define CESPI_H

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string>
using namespace std;
class cespi
{
    public:
        cespi();
        virtual ~cespi();
        bool Begin();
        void Transfer(char* tx,char* rx,unsigned int n);
    private:
        int fd;
        unsigned char mode;
        unsigned char bits;
        int speed;
        int delay;
        string spidev;
};

#endif // CESPI_H
