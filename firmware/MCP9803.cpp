#include "MCP9803.h"
#include "math.h"

bool Sensor::setAddress(int a0, int a1, int a2){
    
    if(a0 == 1){
        address = address | 1;
    }
    if(a1 == 1){
        address = address | 2;
    }
    if(a2 == 1){
        address = address | 4;
    }
    
    Wire.begin();
    Wire.beginTransmission(address);
    byte status = Wire.endTransmission();
    if(status != 0){
        Serial.println("Serial init failed 1");
        return false;
    }
    Wire.beginTransmission(address);
    Wire.write(0x01);
    Wire.write(0x01100000);
    status = Wire.endTransmission();
    if(status != 0){
        Serial.println("Serial init failed 1");
        return false;
    }
    Serial.println("sensor initialized");
    return true;
}

float Sensor::temperature(){
    Wire.beginTransmission(address);
    Wire.write(0x00);
    byte status = Wire.endTransmission();
    if(status != 0){
        return 999.99;
    }
    Wire.requestFrom(address, 2);
    byte a = Wire.read();
    byte b = Wire.read();
    float temp = a;
    temp +=(float)b/256.00;
    
    //Convert to Farenheit
    float tempF = temp*1.8+32;
    return tempF;
}