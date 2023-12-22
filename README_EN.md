This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gyverhx711
Library of working with sensors (ACP) HX711 for Arduino
- Reading
- change of amplification and channel
- Sleeping mode
- Calibration

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** gyverhx711 ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/gyverhx711/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
Gyverhx711 Sensor (Data, Clock, Chan);
// Constants Chan:
// hx_gain128_a - channel A reinforcement 128
// hx_gain32_b - channel b amplification 32
// hx_gain64_a - channel A amplification 64
`` `

<a id="usage"> </a>
## Usage
`` `CPP
Bool Available ();// True - available for reading
Long read ();// to get data
VOID Tare ();// Automatic calibration)
VOID Setoffset (LONG CAL);// install offset manually
Long getoffset ();// Get offset
VOID Sleepmode (Bool Mode);// True - sleep mode, false - wake up

VOID setchannel (Uint8_t Chan);// Install the channel and strengthening hx_gain128_a/hx_gain32_b/hx_gain64_a
// applies after the next call ()!
`` `

### Peculiarities
#### Update speed
ADC has two high -speed modes, tuned in the signal for 15 leg (PIN RATE):
- Low (GND): 10 measurements per second (every 100 ms)
- High (VCC): 80 measurements per second (every 12.5 ms)
- on the Chinese module, the speed is chosen by a jumper (zero resistor)

#### Reading Data
The availability of new data is checked in `AVAILABLE ()`.If you request `read ()` before - the library will return the previous dimension.
It is recommended to use the `if (sensor.available ()) val = sensor.read ();` ``

#### Calibration (Tarming)
When calling the function `tar ()` automatic calibration will occur: the current signal from the sensor (veswith on the scales)
will be accepted for 0. The function `tare ()` takes the last value from the sensor, therefore in some cases
It makes sense to call it inside `AVAILABLE ()` and after `read ()`.If the calibration is called at the start of the program,
When the data from the sensor has not yet been obtained, it will automatically be called `Read ()`.Therefore, it is recommended
Wait for some time between the start of MK and the `Tare ()` `` `` in the area of 200ms).

### connection
One tensodel:
- Red: E+
- Black: E-
- White: a-
- Green: a+

Connection of the board to MK:
- GND, VCC: power 2.5-5V
- SCK, DT: Any Io Pins

! [Scheme] (/doc/sceme (1) .jpg)
! [Scheme] (/doc/scheme (2) .jpg)

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
#include <gyverhx711.h>
Gyverhx711 Sensor (3, 2, Hx_gain64_A);
// hx_gain128_a - channel A reinforcement 128
// hx_gain32_b - channel b amplification 32
// hx_gain64_a - channel A amplification 64

VOID setup () {
  Serial.Begin (9600);
  
  // If the tariffing at the first launch -
  // you need to wait for the reader readiness
  Delay (500);
  Sensor.tare ();// Calibration of zero
  
  //sensor.sleepmode(True);// Turn off the sensor
  //sensor.sleepmode(False);// Turn on the sensor
}

VOID loop () {
  // Reading only by accessibility!IF AVAILABLE
  if (sensor.available ()) {
    Serial.println (Sensor.read ());
  }
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- V1.1 (Pull VARDENTHEONE) - negative values, removed the filter, tariffing until the first value is obtained
- V1.1.1 - Extra variables were removed after V1.1
- v1.2 - added the ability to change the channel/amplification on the fly

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code