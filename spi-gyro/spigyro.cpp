#include<stdio.h>
#include"cespi.h"
#include "ceutil.h"
using namespace std;
int main()
{
    cespi gyro;
    gyro.Begin();

    char t[7]={0,0,0,0,0,0,0};
    char r[7]={0,0,0,0,0,0,0};
    //b7 = set (1) for reading
    //b6 = cleared (0) not to auto increase address
    //b5-b0 = register address

    //read the "who am i" register at address 0x0F
    //its value should be 0xD3
    t[0]=0x8F;//read, not auto 0x0F | 0x80
    gyro.Transfer(t,r,2);
    printf("I am 0x%02x\n",r[1]);

    //Configure Gyro
    //CTRL_REG2 = |0 |0 |HPM1|HPM0|HPCF3|HPCF2|HPCF1|HPCF0|
    //Default =   |0 |0 |0   |0   |0    |0    |0    |0    |
    //HPM = 00 => Normal (High Pass filter Mode selection)
    //HPC = 1001 => 0.1 High Pass Filter Cut-off freq configuration
    //write @address 0x21, value = 0x09
    t[0]=0x21;
    t[1]=0x09;
    gyro.Transfer(t,r,2);

    //CTRL_REG3 = |I1_Int1|I1_Boot|H_Lactive|PP_OD|I2DRDY|I2_WTM|I2_ORun|I2_Empty|
    //Default =   |0      |0      |0        |0    |0     |0     |0      |0       |
    //Use Default

    //CTRL_REG4 = |BDU|BLE|FS1|FS0| - |ST1|ST0|SIM|
    //Default =   |0  |0  |0  |0  |0  |0  |0  |0  |
    //BDU = 1 => Block Data Update
    //BLE = 0 => Little endian
    //FS = 00 => 250 dps (Full scale selection)
    //ST = 000 => Disable Self test
    //write @ address 0x23, value =0x80
    t[0]=0x23;
    t[1]=0x80;
    gyro.Transfer(t,r,2);

    //CTRL_REG5 = |BOOT|FIFO_EN| - |HPen|INT1_Sel1|INT1_Sel0|Out_Sel1|Out_Sel0|
    //Default =   |0   |0      |0  |0   |0        |0        |0       |0       |
    //BOOT = 0 => Normal mode (Reboot Memory Content)
    //FIFO_EN = 0 => disable FIFO
    //HPen = 0 => disable (High Pass Filter)
    //INT1_Sel = 00 => Non high pass filtered data are used for interrupt generation
    //Out_Sel = 00 => no filtering
    //Use Default

    //CTRL_REG1 = |DR1|DR0|BW1|BW0|PD|Zen|Yen|Xen|
    //Default =   |0  |0  |0  |0  |0 |1  |1  |1  |
    //DR = 11 => ODR 800 Hz (output data rate)
    //BW = 10 => Cut-off 50 (Bandwidth 50 Hz)
    //PD = 1 => Normal
    //Zen = Yen = Xen = 1 => Enable
    //write @ address 0x20, value =0xEF
    t[0]=0x20;
    t[1]=0xEF;
    gyro.Transfer(t,r,2);

    t[0]=0xE0;//read ctrl registers
    gyro.Transfer(t,r,5);//send addr 1 byte + read 4 byte
    printf("reg = %02x%02x %02x%02x\n",r[1],r[2],r[3],r[4]);

    int x,y,z;

    for(int i=0;i<10;i++)//with T=0.1 for 30 sec
    {
        //read address 0x28, OUT_X_L register
        //set MSB bit for auto address increment
        t[0]=0xE8;
        gyro.Transfer(t,r,7);
        x=((int(r[2])<<8)+r[1])|(r[2]&0x80?0xFFFF0000:0x00000000);
        y=((int(r[4])<<8)+r[3])|(r[4]&0x80?0xFFFF0000:0x00000000);
        z=((int(r[6])<<8)+r[5])|(r[6]&0x80?0xFFFF0000:0x00000000);
        //Print results
        //printf("x y z = %02x%02x %02x%02x %02x%02x\n",d[1],d[0],d[3],d[2],d[5],d[4]);
        printf("x y z = %d %d %d\n",x,y,z);
        usleep(500000);
    }

    return 0;
}
