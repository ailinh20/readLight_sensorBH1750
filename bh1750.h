#ifndef BH1750_H
#define BH1750_H

#include "Arduino.h"
#include <wire.h>

void setMode(uint8_t mode);
void setMeasuringTime(float measuringTimeFactor);
int setTimewait(uint8_t mode);
uint16_t readData_BH1750();
void writeData_BH1750(byte val);
float readLight(uint8_t mode, float measuringTimeFactor);

#endif