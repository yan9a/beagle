// File: spi-ai.cpp
// Description: SPI communication with MCP3008 ADC
// WebSite: http://cool-emerald.blogspot.com
// MIT License (https://opensource.org/licenses/MIT)
// Copyright (c) 2018 Yan Naing Aye


#include <stdio.h>
#include <stdlib.h>
#include "ce_spi.h"
using namespace std;

int main()
{
    CE_SPI m;
    m.Begin();

    int x;
    float K=0.003225806; 
    // (3.3/1023) V per digit for +3.3V full scale 
    //  using 10 bit digital output
    
    for(int j=0;j<10;j++)
    {
        m.tx[0]=0x01;//Send start bit
        m.tx[1]=0x80;//read channel 0
        m.tx[2]=0x00;
        m.Transfer(3);
        x = m.rx[1]<<8 | m.rx[2]; //read channel 0
        x&=0x03FF;//mask out invalid bits
        printf("x = %d \t Voltage = %f ",x,(K*x));
        printf("\n");
        usleep(500000);
    }
	return 0;
}
