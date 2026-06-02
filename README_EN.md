This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverHX711.svg?color=brightgreen)](https://github.com/GyverLibs/GyverHX711/releases/latest/download/GyverHX711.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverHX711.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverHX711)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverHX711?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverHX711
The HX711 sensor library for Arduino
- Reading
- Change of amplification and channel
- Sleeping mode.
- Sizing

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverHX711** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverHX711/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
```cpp
GyverHX711 sensor(data, clock, chan);
// chan constants:
// HX GAIN128 A - Channel A amplification 128
// HX GAIN32 B channel B gain 32
// HX GAIN64 A channel A amplification 64
```

<a id="usage"></a>
## Use of use
```cpp
bool available();               // True - Available to read
long read();                    // obtain
void tare();                    // calibration (automatic calibration)
void setOffset(long cal);       // manually
long getOffset();               // offset
void sleepMode(bool mode);      // True - sleep mode, false - wake up

void setChannel(uint8_t chan);  // channel and amplify HX GAIN128 A/HX GAIN32 B/HX GAIN64  A
// Applied after the next call read()!
```

### Features
#### Speed of renewal
ADC has two speed modes, is configured by sending a signal to 15 legs (pin RATE):
- LOW (GND): 10 measurements per second (every 100 ms)
- HIGH (VCC): 80 measurements per second (every 12.5 ms)
- On the Chinese module, the speed is selected by a jumper (zero resistor).

#### Reading data
The availability of new data is checked in`available()`. If you ask.`read()`The library will return the previous dimension.
It is recommended to use the design`if (sensor.available()) val = sensor.read();`  

#### Sizing (calibration)
When calling a function`tare()`automatic calibration: current signal from the sensor (weight on the scale)
That'll be 0. Function`tare()`takes the last value obtained from the sensor, so in some cases
It makes sense to call her inside.`available()`after`read()`. If the calibration is called at the start of the program,
When the data from the sensor has not yet been received, it will automatically be called`read()`. Therefore, it is recommended
wait some time between the start of the MK and the challenge`tare()`(around 200ms).

### Connection
One strain gauge:
- Red: E+
- Black: E-
- White: A-
- Green: A+

Connecting the board to the MK:
- GND, VCC: power 2.5-5V
- SCK, DT: Any IO pins

![scheme](/docs/scheme(1).jpg)
![scheme](/docs/scheme(2).jpg)

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
#include <GyverHX711.h>
GyverHX711 sensor(3, 2, HX_GAIN64_A);
// HX GAIN128 A - Channel A amplification 128
// HX GAIN32 B channel B gain 32
// HX GAIN64 A channel A amplification 64

void setup() {
  Serial.begin(9600);
  
  // if the calibration at the first start -
  // Wait for the sensor to be ready.
  delay(500);
  sensor.tare();    // zeroing
  
  //sensor.sleepMode(true) // turn off the sensor
  //sensor.sleepMode(false) // turn on the sensor
}

void loop() {
  // Read only available! if available
  if (sensor.available()) {
    Serial.println(sensor.read());
  }
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 (pull VardenTheOne) - negative values, filter removed, calibration until the first value is obtained
- v1.1.1 - Extra variables are removed after v1. 1st
- v1.2 - added the ability to change the channel / amplification on the fly

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
