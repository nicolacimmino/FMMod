
#ifndef __FMMOD_TERMINAL_H__
#define __FMMOD_TERMINAL_H__

#include <EEPROM.h>
#include "VT100.h"
#include "messages.h"

#define TERMINAL_WIDTH 80

extern float outputPower[];

void printBanner()
{
    VT100.setCursor(2, 1);
    printMessage(0);
}

void printReport()
{
    VT100.setCursor(11, 2);
    VT100.setTextColor(VT_YELLOW);
    Serial.print("PRE: ");
    VT100.setTextColor(VT_WHITE);
    Serial.print(EEPROM.read(EEPROM_PRE) ? "50" : "75");
    Serial.print(" uS");

    VT100.setCursor(13, 2);
    VT100.setTextColor(VT_YELLOW);
    Serial.print("STE: ");
    VT100.setTextColor(VT_WHITE);
    Serial.print(EEPROM.read(EEPROM_STE) ? "Stereo" : "Mono   ");

    VT100.setCursor(15, 2);
    VT100.setTextColor(VT_YELLOW);
    Serial.print("F: ");
    VT100.setTextColor(VT_WHITE);
    Serial.print(EEPROM.read(EEPROM_FREQ_MHZ));
    Serial.print(" MHz");

    VT100.setCursor(17, 2);
    VT100.setTextColor(VT_YELLOW);
    Serial.print("PWR: ");
    VT100.setTextColor(VT_WHITE);
    Serial.print(outputPower[min(EEPROM.read(EEPROM_PWR), 15)]);    
    Serial.print(" dBuV");

    VT100.setCursor(22, 2);
    VT100.setTextColor(VT_YELLOW);
    Serial.print(" P - Preemphasis  S - Stereo  F - Frequency  W - Power");

    VT100.cursorOff();
}

uint8_t askFrequency()
{
    char line[16];
    memset(line, 0, 16);

    VT100.setCursor(19, 2);
    VT100.clearLine();
    VT100.setTextColor(VT_RED);
    Serial.print("Frequency: ");

    while (!Serial.available())
    {
        delay(1);
    }

    Serial.readBytesUntil('\r', line, 16);

    VT100.setCursor(19, 2);
    VT100.clearLine();

    return (uint8_t)atoi(line);
}

uint8_t askPower()
{
    char line[16];
    memset(line, 0, 16);

    VT100.setCursor(19, 2);
    VT100.clearLine();
    VT100.setTextColor(VT_RED);
    Serial.print("Power (0-15): ");

    while (!Serial.available())
    {
        delay(1);
    }

    Serial.readBytesUntil('\r', line, 16);

    VT100.setCursor(19, 2);
    VT100.clearLine();

    return min((uint8_t)atoi(line), 15);
}

#endif