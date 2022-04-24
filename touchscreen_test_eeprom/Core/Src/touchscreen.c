/*
 * touchscreen.c
 *
 *  Created on: Apr 23, 2022
 *      Author: Sam
 */

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"
#include "touchscreen.h"
#include "stdio.h"

extern TS_StateTypeDef TS_State;
static uint8_t Calibration_Done = 0;
static int16_t A1, A2, B1, B2;
static int16_t aPhysX[2], aPhysY[2], aLogX[2], aLogY[2];

/**
 * @brief  Performs the TS calibration
 * @param  None
 * @retval None
 */
void Touchscreen_Calibration(void) {
  uint8_t status = 0;
  uint8_t i = 0;

  TouchscreenCalibration_SetHint();

  status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

  if (status != TS_OK) {
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 95, (uint8_t*) "ERROR",
        CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 80,
        (uint8_t*) "Touchscreen cannot be initialized", CENTER_MODE);
  }

  while (1) {
    if (status == TS_OK) {
      aLogX[0] = 15;
      aLogY[0] = 15;
      aLogX[1] = BSP_LCD_GetXSize() - 15;
      aLogY[1] = BSP_LCD_GetYSize() - 15;

      for (i = 0; i < 2; i++) {
        GetPhysValues(aLogX[i], aLogY[i], &aPhysX[i], &aPhysY[i]);
      }
      A1 = (1000 * (aLogX[1] - aLogX[0])) / (aPhysX[1] - aPhysX[0]);
      B1 = (1000 * aLogX[0]) - A1 * aPhysX[0];

      A2 = (1000 * (aLogY[1] - aLogY[0])) / (aPhysY[1] - aPhysY[0]);
      B2 = (1000 * aLogY[0]) - A2 * aPhysY[0];

      Calibration_Done = 1;
      return;
    }

    HAL_Delay(5);
  }
}

/**
 * @brief  Display calibration hint
 * @param  None
 * @retval None
 */
void TouchscreenCalibration_SetHint(void) {
  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Set Touchscreen Demo description */
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() / 2 - 27,
      (uint8_t*) "Before using the Touchscreen", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() / 2 - 12,
      (uint8_t*) "you need to calibrate it.", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() / 2 + 3,
      (uint8_t*) "Press on the black circles", CENTER_MODE);
}

/**
 * @brief  Get Physical position
 * @param  LogX : logical X position
 * @param  LogY : logical Y position
 * @param  pPhysX : Physical X position
 * @param  pPhysY : Physical Y position
 * @retval None
 */
void GetPhysValues(int16_t LogX, int16_t LogY, int16_t *pPhysX, int16_t *pPhysY) {
  /* Draw the ring */
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_FillCircle(LogX, LogY, 5);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_FillCircle(LogX, LogY, 2);

  /* Wait until touch is pressed */
  WaitForPressedState(1);

  BSP_TS_GetState(&TS_State);
  *pPhysX = TS_State.X;
  *pPhysY = TS_State.Y;

  /* Wait until touch is released */
  WaitForPressedState(0);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_FillCircle(LogX, LogY, 5);
}

/**
 * @brief  Wait For Pressed State
 * @param  Pressed: Pressed State
 * @retval None
 */
void WaitForPressedState(uint8_t Pressed) {
  TS_StateTypeDef State;

  do {
    BSP_TS_GetState(&State);
    HAL_Delay(10);
    if (State.TouchDetected == Pressed) {
      uint16_t TimeStart = HAL_GetTick();
      do {
        BSP_TS_GetState(&State);
        HAL_Delay(10);
        if (State.TouchDetected != Pressed) {
          break;
        } else if ((HAL_GetTick() - 100) > TimeStart) {
          return;
        }
      } while (1);
    }
  } while (1);
}

/**
 * @brief  Calibrate X position
 * @param  x: X position
 * @retval calibrated x
 */
uint16_t Calibration_GetX(uint16_t x) {
  return (((A1 * x) + B1) / 1000);
}

/**
 * @brief  Calibrate Y position
 * @param  y: Y position
 * @retval calibrated y
 */
uint16_t Calibration_GetY(uint16_t y) {
  return (((A2 * y) + B2) / 1000);
}

/**
 * @brief  Check if the TS is calibrated
 * @param  None
 * @retval calibration state
 */
uint8_t IsCalibrationDone(void) {
  return (Calibration_Done);
}

// Touchscreen parameter loading
// Check for A1, A2, B1, B2 values stored in EEPROM
// If those exist, use those while initializing touchscreen
// If they don't, enter the calibration screen
void TS_Get_Params(void) {
  /* Unlock the Flash Program Erase controller */
  HAL_FLASH_Unlock();
  HAL_Delay(1000);
  /* EEPROM Init */
  Serial_Message("EEPROM initializing...");
  if (EE_Init() != EE_OK) {
    Error_Handler();
  }
  Serial_Message("EEPROM initialized");

  uint16_t writeToEEPROM;

  //  // Write something to EEPROM
  //  if((EE_WriteVariable(VirtAddVarTab[0],  writeToEEPROM)) != HAL_OK)
  //  {
  //	Error_Handler();
  //  }
  // Read that back
  if ((EE_ReadVariable(VirtAddVarTab[0], &VarDataTab[0])) != HAL_OK) {
    Error_Handler();
  } else {
    Serial_Message("EEPROM read:");
    writeToEEPROM = VarDataTab[0];
    Print_Int(writeToEEPROM);
    writeToEEPROM++;
  }

  // Write something to EEPROM
  if ((EE_WriteVariable(VirtAddVarTab[0], writeToEEPROM)) != HAL_OK) {
    Error_Handler();
  }
  HAL_FLASH_Lock();
  Serial_Message("EEPROM written");
}
