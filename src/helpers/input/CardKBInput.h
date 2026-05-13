#pragma once
#include <Wire.h>

#ifndef CARDKB_I2C_ADDR
  #define CARDKB_I2C_ADDR 0x5F
#endif
#ifndef CARDKB_SDA
  #define CARDKB_SDA 17
#endif
#ifndef CARDKB_SCL
  #define CARDKB_SCL 18
#endif

static uint8_t  _cardkb_last_key  = 0;
static uint32_t _cardkb_last_time = 0;

inline void cardKBBegin() {
    Wire.begin(CARDKB_SDA, CARDKB_SCL);
    Wire.setClock(100000);
}

inline char cardKBCheck() {
    Wire.requestFrom(CARDKB_I2C_ADDR, 1);
    if (!Wire.available()) return 0;
    uint8_t key = Wire.read();
    if (key == 0x00) { _cardkb_last_key = 0; return 0; }
    uint32_t now = millis();
    if (key == _cardkb_last_key && (now - _cardkb_last_time) < 80) return 0;
    _cardkb_last_key = key;
    _cardkb_last_time = now;
    if (key >= 0x20 && key <= 0x7E) return (char)key;
    return (char)key;
}
