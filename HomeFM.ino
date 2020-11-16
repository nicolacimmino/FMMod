
#define EEPROM_FREQ_MHZ 0
#define EEPROM_PRE 1
#define EEPROM_STE 2
#define EEPROM_PWR 3

#include <Arduino.h>
#include <FMTX.h>
#include "terminal.h"

unsigned long lastReport = 0;

float outputPower[] = {
    95.5,
    96.5,
    97.5,
    98.2,  
    98.9,  
    100,
    101.5,
    102.8,
    105.1, 
    105.6, 
    106.2, 
    106.5,
    107,
    107.4,
    107.7,
    108
};

void setup()
{
  delay(2000);
  Serial.begin(115200);
  VT100.begin(Serial);

  fmtx_init(EEPROM.read(EEPROM_FREQ_MHZ), EEPROM.read(EEPROM_PRE) ? EUROPE : JAPAN);
  fmtx_set_mono(!EEPROM.read(EEPROM_STE));  
  fmtx_set_rfgain(EEPROM.read(EEPROM_PWR));
}

void loop()
{
  int controlValue = Serial.read();
  if (controlValue == 'p')
  {
    EEPROM.write(EEPROM_PRE, !EEPROM.read(EEPROM_PRE));  
    fmtx_set_phcnst(EEPROM.read(EEPROM_PRE) ? EUROPE : JAPAN);
  }

  if (controlValue == 's')
  {
    EEPROM.write(EEPROM_STE, !EEPROM.read(EEPROM_STE));  
    fmtx_set_mono(EEPROM.read(EEPROM_STE));
  }

  if (controlValue == 'f')
  {
    EEPROM.write(EEPROM_FREQ_MHZ, askFrequency());
    fmtx_set_freq(EEPROM.read(EEPROM_FREQ_MHZ));
  }

  if (controlValue == 'w')
  {
    EEPROM.write(EEPROM_PWR, askPower());
    fmtx_set_rfgain(EEPROM.read(EEPROM_PWR));
  }

  if (controlValue > 0) {
      clearInputLine();
  }

  if (millis() - lastReport > 1000)
  {
    printBanner();
    printReport();
    lastReport = millis();
  }
}