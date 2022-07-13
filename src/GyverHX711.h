/*
    Библиотека работы с датчиками (АЦП) HX711 для Arduino
    Документация:
    GitHub: https://github.com/GyverLibs/GyverHX711
    Возможности:
    - Чтение
    - Смена усиления и канала
    - Спящий режим
    - Калибровка
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
    v1.1 (pull VardenTheOne) - отрицательные значения, убран фильтр, тарирование до получения первого значения
    v1.1.1 - убраны лишние переменные после v1.1
*/

#ifndef _GyverHX711_h
#define _GyverHX711_h
#include <Arduino.h>

// режимы:
#define HX_GAIN128_A 0
#define HX_GAIN32_B 1
#define HX_GAIN64_A 2

class GyverHX711 {
public:
    // пин дата, пин клок, режим HX_GAIN128_A/HX_GAIN32_B/HX_GAIN64_A
    GyverHX711 (uint8_t data, uint8_t clock, uint8_t mode = HX_GAIN64_A) :
    _data(data), _clock(clock), _mode(mode) {
        pinMode(data, INPUT);
        pinMode(clock, OUTPUT);
    }
    
    // true - доступен для чтения
    bool available() {
        return (!digitalRead(_data));
    }
    
    // получить моментальное значение
    long read() {
        if (available()) {
            _weight = 0;
            for (uint8_t i = 0; i < 24; i++) {
                digitalWrite(_clock, HIGH);
                delayMicroseconds(1);
                _weight <<= 1;
                if (digitalRead(_data)) _weight |= 1;
                digitalWrite(_clock, LOW);
                delayMicroseconds(1);
            }
            for (uint8_t i = 0; i < _mode + 1; i++) {
                digitalWrite(_clock, 1);
                delayMicroseconds(1);
                digitalWrite(_clock, 0);
                delayMicroseconds(1);
            }
            if (_weight & 0x800000) _weight |= 0xFF000000;  // отрицательные
        }
        return _weight + _cal;
    }
    
    // тарировать (автоматическая калибровка)
    void tare() {
        if (_weight == 0) _cal = -read();   // первый запуск
        else _cal = -_weight;               // остальные
    }
    
    // установить оффсет вручную
    void setOffset(long cal) {
        _cal = cal;
    }
    
    // получить оффсет
    long getOffset() {
        return _cal;
    }
    
    // true - режим сна, false - проснуться
    void sleepMode(bool mode) {
        digitalWrite(_clock, 0);
        if (mode) digitalWrite(_clock, 1);
    }

private:
    long _weight = 0, _cal = 0;
    const uint8_t _data, _clock, _mode;
};
#endif