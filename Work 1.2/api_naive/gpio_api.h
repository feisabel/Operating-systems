#ifndef _GPIO_API_
#define _GPIO_API_
#include <string>

void setOn(int gpio);

void setOff(int gpio);

void changeValue(int gpio);

int getValue(int gpio);

void setIn(int gpio);

void setOut(int gpio);

std::string getDirection(int gpio);

#endif