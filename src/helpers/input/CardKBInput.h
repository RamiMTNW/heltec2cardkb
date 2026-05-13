#pragma once
#include <Wire.h>
#include <helpers/ui/UIScreen.h>

#ifndef CARDKB_I2C_ADDR
  #define CARDKB_I2C_ADDR 0x5F
#endif

static uint8_t  _ckb_last = 0;
static uint32_t _ckb_time = 0;

inline char cardKBCheck() {
    Wire.requestFrom((uint8_t)CARDKB_I2C_ADDR, (uint8_t)1);
    if (!Wire.available()) return 0;
    uint8_t k = Wire.read();
    if (k == 0) { _ckb_last = 0; return 0; }
    uint32_t now = millis();
    if (k == _ckb_last && (now - _ckb_time) < 80) return 0;
    _ckb_last = k; _ckb_time = now;
    return (char)k;
}
