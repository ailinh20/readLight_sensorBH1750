#include <Wire.h>
#include "bh1750.h"

#define CHM 0b00010000     //CHM: Continuously H-Resolution Mode
#define CHM_2 0b00010001   //CHM_2: Continuously H-Resolution Mode2
#define CLM 0b00010011     //CLM: Continuously L-Resolution Mode
#define OTH 0b00100000     //OTH: One Time H-Resolution Mode
#define OTH_2 0b00100001   //OTH_2: One Time H-Resolution Mode2
#define OTL 0b00100011      //OTL: One Time L-Resolution Mode
#define MTFactor_Default 1

//float measuringTimeFactor = 3.68;
uint8_t mode = CHM_2;
int timeWait = setTimewait(mode);
void setup(){
  Serial.begin(9600);
  Wire.begin();
  setMeasuringTime(MTFactor_Default); 
  setMode(mode);
}
void loop(){ 
  delay(timeWait*MTFactor_Default);
  float val = readLight(mode, MTFactor_Default);
  Serial.print("Light: ");
  Serial.print(val);
  Serial.println(" lx");
}
