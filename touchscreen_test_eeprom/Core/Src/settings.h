/*
 * settings.h
 *
 *  Created on: Apr 22, 2022
 *      Author: Sam
 */
#include "stdio.h"

#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#define EEPROM_SET 0x24596B84EA78324DULL

//const uint64_t EEPROM_SET;
typedef struct Settings {
  int x0;
  int y0;
  int x1;
  int y1;
} Settings;

int EEPROM_exists(void);

#endif /* INC_SETTINGS_H_ */
