# About

This Library is intended for use with MCP9803 Mini module on the Particle Core/Photon platform.

The intention of this library is to make use of the MCP9803 mini module with Particle development web IDE as simple as possible for users.

The MCP9803 Mini Module from ControlEverything may be purchased [here] [mcp9803store].

###Developer information
NCD has been designing and manufacturing computer control products since 1995.  We specialize in hardware design and manufacturing of sensory input and output control devices.  We pride ourselves as being the industry leader of computer control relay products as well as sensory reading products.  Our products are proven reliable and we are very excited to support Particle.  For more information on NCD please visit www.controleverything.com

###Requirements
- [MCP9803 Mini Module][mcp9803store].
- Particle Core/Photon module
- Knowledge base for developing and programming with Particle Core/Photon modules.

### Version
1.0.0

### How to use this library

The libary must be imported into your application.  This can be done through the Particle WEB IDE by selecting Libraries, then select the MCP9803.  Click Include in App button.  Select the App you want to include the library in.  Finally click Add to this app.  For more information see [Particle's documentation] [sparkIncludeLibrary].

### Example use

Once the Library is included in your applicaiton you should see an include statement at the top like this:
```cpp
//This #include statement was automatically added by the Particle IDE.
#include "MCP9803/MCP9803.h"
```

Now you need to instanciate an object of the library for use in your application like this:
```cpp
MCP9803 sensor;
```

Here is an example use case for the class:
```cpp
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
```

###Public accessible methods
```cpp
void setAddress(int a0, int a1, int a2);
```
>Must be called first before using the object.  This method should also be called any time communication with
>the controller is lost or broken to recover communication  This method accepts three int arguments.  This
>tells the Library what address to direct commands to.  a0, a1, and a2 ints are representations of the three
>jumpers on the MCP9803 mini module which are labeled on the board 0, 1, and 2.  If the jumper is
>installed then that int in this call should be set to 1.  If it is not installed then the int should be set to
So if I have A0, A1, and A2 installed I would call ```sensor.setAddress(1, 1, 1).```


```cpp
float temperature();
```
>This method accepts no arguments.  A call to this method will return the current temperature in degrees Farenheit as a float variable.
>

License
----

GNU
[sparkIncludeLibrary]:https://docs.particle.io/guide/getting-started/build/photon/
[mcp9803store]:https://www.controleverything.com/content/Temperature?sku=MCP9803_I2CS