![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
# GyverHX711
Библиотека работы с датчиками (АЦП) HX711 для Arduino
- Чтение
- Смена усиления и канала
- Спящий режим
- Калибровка

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverHX711** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverHX711/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
```cpp
GyverHX711 sensor(data, clock, gain);
// константы gain:
// HX_A_GAIN128 - канал А усиление 128
// HX_B_GAIN32 - канал B усиление 32
// HX_A_GAIN64 - канал А усиление 64
```

<a id="usage"></a>
## Использование
```cpp
bool available();           // true - доступен для чтения
long read();                // получить данные с фильтрацией
long read_current_value();  // получить данные без фильтрации
void tare();                // тарировать (автоматическая калибровка)
void setOffset(long cal);   // установить оффсет вручную
long getOffset();           // получить оффсет
void sleepMode(bool mode);  // true - режим сна, false - проснуться
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
#include <GyverHX711.h>
GyverHX711 sensor(7, 8, HX_GAIN128_A);

void setup() {
  Serial.begin(9600);
  sensor.tare();              // калибровка нуля
  
  //sensor.sleepMode(true);   // выключить датчик
  //sensor.sleepMode(false);  // включить датчик
}

void loop() {
  // чтение только по доступности! if available
  if (sensor.available()) {
    Serial.println(sensor.read());
  }
}
```

<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!
