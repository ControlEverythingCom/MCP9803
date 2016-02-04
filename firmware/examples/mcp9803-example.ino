// This #include statement was automatically added by the Particle IDE.
#include "mcp9803/MCP9803.h"
MCP9803 sensor;
double temperature;

void setup() {
    sensor.setAddress(1,0,0);
    Particle.variable("temperature", temperature);
}

void loop() {
    temperature = sensor.temperature();
    Serial.printf("Temperature: %f \n", temperature);
    delay(2000);
}