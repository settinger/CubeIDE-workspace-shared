/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"
#include "eeprom.h"
#include "settings.h"
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LCD_FRAME_BUFFER_LAYER0 (LCD_FRAME_BUFFER + 0x130000)
#define LCD_FRAME_BUFFER_LAYER1 LCD_FRAME_BUFFER

#define DEBOUNCE_TIME_MS 10
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t button0_debounce_time_old = 0;
static TS_StateTypeDef  TS_State;
static uint8_t Calibration_Done = 0;
static int16_t  A1, A2, B1, B2;
static int16_t aPhysX[2], aPhysY[2], aLogX[2], aLogY[2];


/* Virtual address defined by the user: 0xFFFF value is prohibited */
uint16_t VirtAddVarTab[NB_OF_VAR] = {0x5555, 0x6666, 0x7777, 0x8888};
uint16_t VarDataTab[NB_OF_VAR] = {0, 0, 0, 0};
uint16_t VarValue,VarDataTmp = 0;

//extern uint16_t VirtAddVarTab[NB_OF_VAR];
//extern uint16_t VarDataTab[NB_OF_VAR];
//extern uint16_t VarValue,VarDataTmp;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Serial_Message(char*);
void Print_Int(int);
static void TouchscreenCalibration_SetHint(void);
static void GetPhysValues(int16_t LogX, int16_t LogY, int16_t * pPhysX, int16_t * pPhysY);
static void WaitForPressedState(uint8_t Pressed);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// Send a message over serial
void Serial_Message(char string[]) {
	HAL_UART_Transmit(&huart5, (uint8_t*)string, strlen((char*)string), 100);
	HAL_UART_Transmit(&huart5, (uint8_t*)"\r\n", 2, 100);
}

void Print_Int(int x) {
	char string[24]; // Lazy assume integer is fewer than 24 digits
	sprintf(string, "%d", x);
	HAL_UART_Transmit(&huart5, (uint8_t*)string, strlen(string), 100);
	HAL_UART_Transmit(&huart5, (uint8_t*)"\r\n", 2, 100);
}

// External-interrupt callback to toggle LD4 when user button is pressed
// Debounces by expecting a 10ms gap (or more) between valid presses
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	uint32_t button0_debounce_time_new = HAL_GetTick();
	if ((button0_debounce_time_new-button0_debounce_time_old) >= DEBOUNCE_TIME_MS) {
		HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
		button0_debounce_time_old = button0_debounce_time_new;
	}
}

/**
  * @brief  Performs the TS calibration
  * @param  None
  * @retval None
  */
void Touchscreen_Calibration(void)
{
  uint8_t status = 0;
  uint8_t i = 0;

  TouchscreenCalibration_SetHint();

  status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

  if (status != TS_OK)
  {
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 95, (uint8_t*)"ERROR", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t*)"Touchscreen cannot be initialized", CENTER_MODE);
  }

  while (1)
  {
    if (status == TS_OK)
    {
      aLogX[0] = 15;
      aLogY[0] = 15;
      aLogX[1] = BSP_LCD_GetXSize() - 15;
      aLogY[1] = BSP_LCD_GetYSize() - 15;

      for (i = 0; i < 2; i++)
      {
        GetPhysValues(aLogX[i], aLogY[i], &aPhysX[i], &aPhysY[i]);
      }
      A1 = (1000 * ( aLogX[1] - aLogX[0]))/ ( aPhysX[1] - aPhysX[0]);
      B1 = (1000 * aLogX[0]) - A1 * aPhysX[0];

      A2 = (1000 * ( aLogY[1] - aLogY[0]))/ ( aPhysY[1] - aPhysY[0]);
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
static void TouchscreenCalibration_SetHint(void)
{
  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Set Touchscreen Demo description */
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 - 27, (uint8_t*)"Before using the Touchscreen", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 - 12, (uint8_t*)"you need to calibrate it.", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 3, (uint8_t*)"Press on the black circles", CENTER_MODE);
}

/**
  * @brief  Get Physical position
  * @param  LogX : logical X position
  * @param  LogY : logical Y position
  * @param  pPhysX : Physical X position
  * @param  pPhysY : Physical Y position
  * @retval None
  */
static void GetPhysValues(int16_t LogX, int16_t LogY, int16_t * pPhysX, int16_t * pPhysY)
{
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
static void WaitForPressedState(uint8_t Pressed)
{
  TS_StateTypeDef  State;

  do
  {
    BSP_TS_GetState(&State);
    HAL_Delay(10);
    if (State.TouchDetected == Pressed)
    {
      uint16_t TimeStart = HAL_GetTick();
      do {
        BSP_TS_GetState(&State);
        HAL_Delay(10);
        if (State.TouchDetected != Pressed)
        {
          break;
        } else if ((HAL_GetTick() - 100) > TimeStart)
        {
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
uint16_t Calibration_GetX(uint16_t x)
{
  return (((A1 * x) + B1)/1000);
}

/**
  * @brief  Calibrate Y position
  * @param  y: Y position
  * @retval calibrated y
  */
uint16_t Calibration_GetY(uint16_t y)
{
  return (((A2 * y) + B2)/1000);
}

/**
  * @brief  Check if the TS is calibrated
  * @param  None
  * @retval calibration state
  */
uint8_t IsCalibrationDone(void)
{
  return (Calibration_Done);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_FMC_Init();
  MX_I2C3_Init();
  MX_SPI5_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_USB_OTG_HS_HCD_Init();
  MX_UART5_Init();
  MX_TIM7_Init();
  MX_DMA2D_Init();
  MX_LTDC_Init();
  /* USER CODE BEGIN 2 */

  Serial_Message("Device has turned on.\n");

  BSP_LCD_Init();
  // Set up Layer 1 for white
  BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER_LAYER1);
  BSP_LCD_SelectLayer(1);
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  BSP_LCD_SetColorKeying(1, LCD_COLOR_WHITE);
  BSP_LCD_SetLayerVisible(1, DISABLE);

  // Set up Layer 0
  BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER_LAYER0);
  BSP_LCD_SelectLayer(0);

  BSP_LCD_DisplayOn();
  BSP_LCD_Clear(LCD_COLOR_BLUE);
  BSP_LCD_DisplayStringAtLine(2, (uint8_t*)" Thank you ");
  BSP_LCD_DisplayStringAtLine(3, (uint8_t*)"  XXXXXX!  ");

  // Touchscreen initialization
  // If no values for A1, A2, B1, B2 are stored in EEPROM, run the calibration
  // Else, go right into init things
  //Touchscreen_Calibration();
  BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  Serial_Message("LCD X dimension: ");
  Print_Int(BSP_LCD_GetXSize());
  Serial_Message("\n\nLCD Y dimension: ");
  Print_Int(BSP_LCD_GetYSize());



  /* Unlock the Flash Program Erase controller */
  HAL_FLASH_Unlock();
  HAL_Delay(1000);
  /* EEPROM Init */
  Serial_Message("EEPROM initializing...");
  if( EE_Init() != EE_OK)
  {
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
  if((EE_ReadVariable(VirtAddVarTab[0],  &VarDataTab[0])) != HAL_OK)
  {
    Error_Handler();
  } else {
	  Serial_Message("EEPROM read:");
	  writeToEEPROM = VarDataTab[0];
	  Print_Int(writeToEEPROM);
	  writeToEEPROM++;
  }

  Settings barf;
  barf.x0 = 4;
  Print_Int(barf.x0);

  // Write something to EEPROM
  if((EE_WriteVariable(VirtAddVarTab[0],  writeToEEPROM)) != HAL_OK)
  {
	Error_Handler();
  }
  Serial_Message("EEPROM written");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
//	HAL_Delay(700);
	  WaitForPressedState(1);

	  BSP_TS_GetState(&TS_State);
	  int16_t x = TS_State.X;
	  int16_t y = TS_State.Y;
	  Serial_Message("Touch X coordinate: ");
	  Print_Int(x);
	  Serial_Message("\n\nTouch Y coordinate: ");
	  Print_Int(y);

	  /* Wait until touch is released */
	  WaitForPressedState(0);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  Serial_Message("ERROR");
  //__disable_irq();
  while (1)
  {
	    /* Toggle LED3 fast */
	    BSP_LED_Toggle(LED3);
	    HAL_Delay(40);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
