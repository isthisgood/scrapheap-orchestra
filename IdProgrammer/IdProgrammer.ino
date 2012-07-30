#include <EEPROM.h>

const int ID = 0;

void setup()
{
  EEPROM.write(0, ID);  
}

void loop()
{
}
