#include "cespi.h"
#define PRINT_MES 0
cespi::cespi()
{
    mode=0;
    bits=8;
    speed=500000;//500 kHz
    delay=0;
    spidev="/dev/spidev1.0";
}

cespi::~cespi()
{
    close(fd);
}

bool cespi::Begin()
{
    fd = open(spidev.c_str(), O_RDWR);
	if (fd < 0){
        printf("Can't open %s.\n",spidev.c_str());
        return false;
	}

    if(ioctl(fd, SPI_IOC_WR_MODE, &mode)==-1){
        printf("Can't set SPI mode.\n");
        return false;
    }

    if(ioctl(fd, SPI_IOC_RD_MODE, &mode)==-1){
        printf("Can't get SPI mode.\n");
        return false;
    }

    if(ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)==-1){
        printf("Can't set bits per word.\n");
        return false;
    }

    if(ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits)==-1){
        printf("Can't get bits per word.\n");
        return false;
    }

    if(ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)==-1){
        printf("Can't set max speed hz.\n");
        return false;
    }

    if(ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)==-1){
        printf("Can't get max speed hz.\n");
        return false;
    }

    printf("SPI mode: %d\n", mode);
	printf("Bits per word: %d\n", bits);
	printf("Max speed: %d Hz\n", speed);
	return true;
}

void cespi::Transfer(char* tx,char* rx,unsigned int n)
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
