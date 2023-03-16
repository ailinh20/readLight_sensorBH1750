#include "bh1750.h"

#define ADD_BH1750 0x23
#define DATA_REG_RESET 0b00000111
#define POWER_DOWN 0b00000000
#define POWER_ON 0b00000001


void writeData_BH1750(byte val){
  Wire.beginTransmission(ADD_BH1750);
  Wire.write(val);
  Wire.endTransmission();  
}


void setMeasuringTime(float measuringTimeFactor){
  byte mt = round(measuringTimeFactor*69); // lưu giá trị Mtreg mới
  byte highByteMT = ((mt>>5) | 0b01000000); // thay đổi 8bit cao của thanh ghi MTReg  
  byte lowByteMT = (mt & 0b00011111); // thay đổi 8bit thấp cả thanh ghi MTReg
  lowByteMT |= 0b01100000;
  writeData_BH1750(highByteMT); // Gửi 8bit cao của MTReg cho sensor
  writeData_BH1750(lowByteMT); // Gửi 8bit thấp của MTReg cho sensor
}

void setMode(uint8_t mode){
  writeData_BH1750(mode);
}

int setTimewait(uint8_t mode){
  if (mode == 0b00010011 || mode == 0b00100011) return 24; // mode L-Resolution Mode thì max Timewait = 24
  else return 180; // những mode còn lại max Timewait = 180
}

uint16_t readData_BH1750(){ //đọc 16bit data thô từ sensor
  uint8_t H_byte, L_byte;
  Wire.requestFrom(ADD_BH1750, 2);
  if(Wire.available()){
    H_byte=Wire.read();
    L_byte=Wire.read(); 
  }
  uint16_t result = H_byte;
  result <<= 8;
  return (result | L_byte);
}

float readLight(uint8_t mode, float measuringTimeFactor){
  uint16_t rawLux;
  float lux;
  rawLux = readData_BH1750();

  // chuyển đổi 16bit data thô nhận được từ sensor sang giá trị lux
  if((mode == 0b00010001) || (mode == 0b00100001)){ // mode CHM2 || mode OHM2
    lux = (rawLux/2.4)/measuringTimeFactor;     
  }
  else{
    lux = (rawLux/1.2)/measuringTimeFactor;
  }
  return lux;
}
