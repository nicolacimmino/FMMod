#ifndef __THUNDER_MESSAGES_H__
#define __THUNDER_MESSAGES_H__

#include "VT100.h"

const char message0[] PROGMEM = "\e[33m  ______ __  __ __  __           _  \r\n"
                                " |  ____|  \\/  |  \\/  |         | |     \e[32mSensor:\e[33m KT0803\r\n"
                                " | |__  | \\  / | \\  / | ___   __| |     \e[32mS/N:\e[33m 202010-003\r\n"
                                " |  __| | |\\/| | |\\/| |/ _ \\ / _` |     \e[32mAssembled:\e[33m 2020-10-11\r\n"
                                " | |    | |  | | |  | | (_) | (_| |     \e[32mBuilt:\e[33m " __DATE__ " " __TIME__ "\r\n"
                                " |_|    |_|  |_|_|  |_|\\___/ \\__,_|   \r\n"
                                "                    \e[32m(c) Nicola 2020\r\n";
                                                                             
const char *const messages[] PROGMEM = {message0};

void printMessage(uint8_t messageId)
{
    char buffer[512];
    strcpy_P(buffer, (char *)pgm_read_word(&(messages[messageId])));
    Serial.print(buffer);
}

#endif
