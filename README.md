[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverHX711.svg?color=brightgreen)](https://github.com/GyverLibs/GyverHX711/releases/latest/download/GyverHX711.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverHX711.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverHX711)
[![arduino-library](https://www.ardu-badge.com/badge/GyverHX711.svg?)](https://www.ardu-badge.com/GyverHX711)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverHX711?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

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
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="init"></a>
## Инициализация
```cpp
GyverHX711 sensor(data, clock, chan);
// константы chan:
// HX_GAIN128_A - канал А усиление 128
// HX_GAIN32_B - канал B усиление 32
// HX_GAIN64_A - канал А усиление 64
```

<a id="usage"></a>
## Использование
```cpp
bool available();               // true - доступен для чтения
long read();                    // получить данные
void tare();                    // тарировать (автоматическая калибровка)
void setOffset(long cal);       // установить оффсет вручную
long getOffset();               // получить оффсет
void sleepMode(bool mode);      // true - режим сна, false - проснуться

void setChannel(uint8_t chan);  // установить канал и усиление HX_GAIN128_A/HX_GAIN32_B/HX_GAIN64_A
// ПРИМЕНЯЕТСЯ ПОСЛЕ СЛЕДУЮЩЕГО ВЫЗОВА read()!
```

### Особенности
#### Скорость обновления
АЦП имеет два скоростных режима, настраивается подачей сигнала на 15 ножку (пин RATE):
- LOW (GND): 10 измерений в секунду (каждые 100 мс)
- HIGH (VCC): 80 измерений в секунду (каждые 12.5 мс)
- На китайском модуле скорость выбирается перемычкой (нулевой резистор)

#### Чтение данных
Доступность новых данных проверяется в `available()`. Если запросить `read()` раньше - библиотека вернёт предыдущее измерение. 
Рекомендуется использовать конструкцию `if (sensor.available()) val = sensor.read();`  

#### Калибровка (тарирование)
При вызове функции `tare()` произоайдёт автоматическая калибровка: текущий сигнал с датчика (вес на весах) 
будет принят за 0. Функция `tare()` берёт последнее полученное значение с датчика, поэтому в некоторых случаях 
есть смысл вызывать её внутри `available()` и после `read()`. Если калибровка вызывается при старте программы, 
когда данные с датчика ещё не были получены, то в ней автоматически будет вызван `read()`. Поэтому рекомендуется 
выждать некоторое время между стартом МК и вызовом `tare()` (в районе 200мс).

### Подключение
Один тензодатчик:
- Красный: E+
- Чёрный: E-
- Белый: A-
- Зелёный: A+

Подключение платы к МК:
- GND, VCC: питание 2.5-5V
- SCK, DT: любые IO пины

![scheme](/docs/scheme(1).jpg)
![scheme](/docs/scheme(2).jpg)

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
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
```

<a id="versions"></a>
## Версии
- v1.0
- v1.1 (pull VardenTheOne) - отрицательные значения, убран фильтр, тарирование до получения первого значения
- v1.1.1 - убраны лишние переменные после v1.1
- v1.2 - добавлена возможность менять канал/усиление на лету

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
