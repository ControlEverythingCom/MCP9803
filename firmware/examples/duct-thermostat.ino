// This #include statement was automatically added by the Particle IDE.
#include "MCP9803/MCP9803.h"
MCP9803 sensor;
double temperature;
String temperatureString;

bool heat;
float setTemp;
float tempSwing = 1.00;
String setTempString;
String tempSwingString;

String hvacStatus = "";

int setTemperature(String temperature);
int setTemperatureSwing(String temperature);
void setMode(const char *event, const char *data);

int tempSwingEEPROMLocation = 5;
int setTempEEPROMLocation = 1;
int hvacStatusBoolLocation = 0;

void setup() {
    getStoredInfo();
    sensor.setAddress(1,0,0);
    Particle.variable("temperature", temperatureString);
    Particle.variable("HVAC", hvacStatus);
    Particle.variable("SetTemp", setTempString);
    Particle.variable("TempSwing", tempSwingString);
    Particle.function("setTemp", setTemperature);
    Particle.function("setSwing", setTemperatureSwing);
    Particle.subscribe("HVAC_Mode", setMode, MY_DEVICES);
}

void loop() {
    temperature = sensor.temperature();
    temperatureString = String(temperature, 2);
    Serial.printf("Temperature: %f \n", temperature);
    //Running heater
    if(heat){
        if(temperature >= setTemp){
            //Close HVAC DUCT
            Particle.publish("ductControl", "close");
            Serial.println("Duct Closed");
        }else{
            if(temperature <= setTemp - tempSwing){
                //Open HVAC DUCT
                Particle.publish("ductControl", "open");
                Serial.println("Duct Open");
            }
        }
    }
    //Running AC
    else{
        if(temperature <= setTemp){
            //Close HVAC DUCT
            Particle.publish("ductControl", "close");
            Serial.println("Duct Closed");
        }else{
            if(temperature >= setTemp + tempSwing){
                //Open HVAC DUCT
                Particle.publish("ductControl", "open");
                Serial.println("Duct Open");
            }
        }
    }
    delay(2000);
}

int setTemperature(String temperature){
    setTemp = temperature.toFloat();
    setTempString = String(setTemp, 2);
    EEPROM.put(setTempEEPROMLocation, setTemp);
    Serial.printf("setTemp: %.2f \n", setTemp);
}

int setTemperatureSwing(String temperature){
    tempSwing = temperature.toFloat();
    tempSwingString = String(tempSwing, 2);
    EEPROM.put(tempSwingEEPROMLocation, tempSwing);
    Serial.printf("tempSwing: %.2f \n", tempSwing);
    
}

void setMode(const char *event, const char*data){
    String command = String(data);
    if(command.equalsIgnoreCase("AC")){
        heat = false;
        hvacStatus = "AC";
    }
    if(command.equalsIgnoreCase("HEAT")){
        heat = true;
        hvacStatus = "HEAT";
    }
    EEPROM.put(hvacStatusBoolLocation, heat);
}

void getStoredInfo(){
    EEPROM.get(setTempEEPROMLocation, setTemp);
    setTempString = String(setTemp, 2);
    EEPROM.get(tempSwingEEPROMLocation, tempSwing);
    tempSwingString = String(tempSwing, 2);
    EEPROM.get(hvacStatusBoolLocation, heat);
    if(heat){
        hvacStatus = "HEAT";
    }else{
        hvacStatus = "AC";
    }
    Serial.printf("setTemp: %.2f \n", setTemp);
    Serial.printf("tempSwing: %.2f \n", tempSwing);
    Serial.printf("heat: %d \n", heat);
}
