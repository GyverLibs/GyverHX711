#include <GyverHX711.h>
GyverHX711 sensor(3, 2, HX_GAIN64_A);
// HX_GAIN128_A - канал А усиление 128
// HX_GAIN32_B - канал B усиление 32
// HX_GAIN64_A - канал А усиление 64

void setup() {
  Serial.begin(9600);
  
  // если тарирование при первом запуске -
  // нужно выждать готовность датчика
  delay(500);
  sensor.tare();    // калибровка нуля
  
  //sensor.sleepMode(true);		// выключить датчик
  //sensor.sleepMode(false);	// включить датчик
}

void loop() {
  // чтение только по доступности! if available
  if (sensor.available()) {
    Serial.println(sensor.read());
  }
}