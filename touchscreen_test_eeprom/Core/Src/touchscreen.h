/*
 * touchscreen.h
 *
 *  Created on: Apr 23, 2022
 *      Author: Sam
 */

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"
#include "stdio.h"

#ifndef SRC_TOUCHSCREEN_H_
#define SRC_TOUCHSCREEN_H_

#define LCD_FRAME_BUFFER_LAYER0 (LCD_FRAME_BUFFER + 0x130000)
#define LCD_FRAME_BUFFER_LAYER1 LCD_FRAME_BUFFER

void Touchscreen_Calibration(void);
void TouchscreenCalibration_SetHint(void);
void GetPhysValues(int16_t LogX, int16_t LogY, int16_t * pPhysX, int16_t * pPhysY);
void WaitForPressedState(uint8_t Pressed);

uint16_t Calibration_GetX(uint16_t x);
uint16_t Calibration_GetY(uint16_t y);
uint8_t IsCalibrationDone(void);

#endif /* SRC_TOUCHSCREEN_H_ */
