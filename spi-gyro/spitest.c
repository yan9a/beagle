#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string.h>

char spidev[]="/dev/spidev1.0";
int fd;
unsigned char mode;
unsigned char bits;
int speed;
int delay;


void Transfer(char* tx,char* rx,unsigned int n)
{
    struct spi_ioc_transfer tr;
    tr.tx_buf = (unsigned long)tx;
	tr.rx_buf = (unsigned long)rx;
	tr.len = n;
	tr.delay_usecs = delay;
	tr.speed_hz = speed;
	tr.bits_per_word = bits;
    
	if(ioctl(fd, SPI_IOC_MESSAGE(1), &tr)<1){
        printf("Can't send SPI message.\n");
	}
}

int main()
{
    char t[7]={0,0,0,0,0,0,0};
    char r[7]={0,0,0,0,0,0,0};
    
    fd = open((const char*)spidev, O_RDWR);
	if (fd < 0){
        printf("Can't open %s.\n",spidev);
        return -1;
	}

    if(ioctl(fd, SPI_IOC_WR_MODE, &mode)==-1){
        printf("Can't set SPI mode.\n");
        return -1;
    }

    if(ioctl(fd, SPI_IOC_RD_MODE, &mode)==-1){
        printf("Can't get SPI mode.\n");
        return -1;
    }

    if(ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)==-1){
        printf("Can't set bits per word.\n");
        return -1;
    }

    if(ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits)==-1){
        printf("Can't get bits per word.\n");
        return -1;
    }

    if(ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)==-1){
        printf("Can't set max speed hz.\n");
        return -1;
    }

    if(ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)==-1){
        printf("Can't get max speed hz.\n");
        return -1;
    }

    printf("SPI mode: %d\n", mode);
	printf("Bits per word: %d\n", bits);
	printf("Max speed: %d Hz\n", speed);
    
    
    //read the "who am i" register at address 0x0F
    //its value should be 0xD3
    t[0]=0x8F;//read, not auto 0x0F | 0x80
    Transfer(t,r,2);
    printf("I am 0x%02x\n",r[1]);
    
	return 0;
}
