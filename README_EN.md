This is an automatic translation, may be incorrect in some places. See sources and examples!

# GyverHX711
Library for working with sensors (ADC) HX711 for Arduino
- Reading
- Change gain and channel
- Sleep mode
- Calibration

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverHX711** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/GyverHX711/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
GyverHX711 sensor(data, clock, gain);
// gain constants:
// HX_GAIN128_A - channel A set128
// HX_GAIN32_B - channel B gain 32
// HX_GAIN64_A - channel A gain 64
```

<a id="usage"></a>
## Usage
```cpp
bool available(); // true - readable
longread(); // to get data
void tare(); // tare (automatic calibration)
void setOffset(long cal); // set offset manually
long getOffset(); // get offset
void sleepMode(bool mode); // true - sleep mode, false - wake up
```

### Peculiarities
#### Update rate
The ADC has two speed modes, it is configured by applying a signal to the 15th leg (pin RATE):
- LOW (GND): 10 measurements per second (every 100ms)
- HIGH (VCC): 80 measurements per second (every 12.5 ms)
- On the Chinese module, the speed is selected by a jumper (zero resistor)

#### Read data
The availability of new data is checked in `available()`. If you request `read()` earlier, the library will return the previous measurement.
It is recommended to use the construct `if (sensor.available()) val = sensor.read();`

#### Calibration (taring)
When calling the `tare()` function, automatic calibration will occur: the current signal from the sensor (weight on the scales)
will be taken as 0. The `tare()` function takes the last received value from the sensor, so in some cases
it makes sense to call it inside `available()` and after `read()`. If calibration is called at program start,
when the data from the sensor has not yet been received, then `read()` will be automatically called in it. Therefore, it is recommended
wait some time between the start of the MK and the call to `tare()` (around 200ms).

### Connection
One load cell scale:
- Red: E+
- Black: E-
- White: A-
- Green: A+

Connecting the board to the MK:
- GND, VCC: power supply 2.5-5V
- SCK, DT: any IO pins

![scheme](/docs/scheme(1).jpg)
![scheme](/docs/scheme(2).jpg)

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
#include <GyverHX711.h>
GyverHX711 sensor(3, 2, HX_GAIN64_A);
// HX_GAIN128_A - channel A gain 128
//HX_GAIN32_B - channel B gain 32
// HX_GAIN64_A - channel A gain 64

void setup() {
  Serial.begin(9600);
  
  // if tare on first run -
  // you need to wait for the sensor to be ready
  delay(500);
  sensor.tare(); // zero calibration
  
  //sensor.sleepMode(true); // turn off the sensor
  //sensor.sleepMode(false); // turn on the sensor
}

void loop() {
  // read only when available! if available
  if (sensor.available()) {
    Serial.println(sensor.read());
  }
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 (pull VardenTheOne) - negative values, filter removed, taring until the first value is obtained

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!