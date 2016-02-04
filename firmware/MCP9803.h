#include "spark_wiring_i2c.h"
#include "spark_wiring_usbserial.h"
#include "spark_wiring_constants.h"

class MCP9803{
public:
    bool setAddress(int a0, int a1, int a2);
    float temperature();
    
private:
    int address = 0x48;
};