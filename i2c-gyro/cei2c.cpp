#include "cei2c.h"
#include "ceutil.h"
using namespace std;

#define PRINT_MES 0
CE_I2C::CE_I2C()
{
    //ctor
}

CE_I2C::CE_I2C(int bus_id,int slave_address)
{
    Begin(bus_id,slave_address);
}

CE_I2C::~CE_I2C()
{
    //dtor
}

bool CE_I2C::Begin(int bus_id,int slave_address)
{
    string filename = "/dev/i2c-";
    filename+=ToString(bus_id);
    if ((fd = open(filename.c_str(), O_RDWR)) < 0) {
        #if PRINT_MES==1
             printf("Failed to open the i2c bus\n");
        #endif //
        return false;
    }
    if (ioctl(fd, I2C_SLAVE, slave_address) < 0) {
        #if PRINT_MES==1
            printf("Failed to acquire bus access and/or talk to slave.\n");
        #endif
        return false;
    }
    #if PRINT_MES==1
        printf("I2C beginning \'%s\' successful.\n",filename.c_str());
    #endif // PRINT_MES
    return true;
}

bool CE_I2C::Write(char* buf,int n)
{
    if(write(fd,buf,n)!=n){
        #if PRINT_MES==1
            printf("Failed to write to the i2c bus.\n");
        #endif // PRINT_MES
        return false;
    }
    #if PRINT_MES==1
        printf("I2C writing %d byte(s) successful.\n",n);
    #endif // PRINT_MES
    return true;
}

bool CE_I2C::Read(char* buf,int n)
{
    if(read(fd,buf,n)!=n){
        #if PRINT_MES==1
            printf("Failed to read from the i2c bus.\n");
        #endif // PRINT_MES
        return false;
    }
    #if PRINT_MES==1
        printf("I2C reading %d byte(s) successful.\n",n);
    #endif // PRINT_MES
    return true;
}
