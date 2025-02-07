/* USER CODE BEGIN Header */
/**Navreet Kaur
 * ECET 260 ARM Microcontrollers
 * 12 Sep, 2019
 * LAB 2_GPIO
 * This lab turns four LEDs on in clockwise direction and when the blue button(Active low) is pressed, it changes to counterclockwise direction
 * ****Two LEDS on the same pin is the main thing*****
 * PIN 8_RED LED = Active Low
 * PIN 3_BLUE LED = Active LOW
 * PIN 3_YELLOW LED = Active High
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	unsigned char Button;      // defining a new char button to check the state of button
	int State = 0;          // defining a new integer state which defines the every state of LEDs
	GPIO_InitTypeDef GPIO_InitStruct = {0};  //initialization

  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */

 SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
// turning Pin 3 as an input so that both LEDs are off .
      GPIO_InitStruct.Pin = LED3_Pin;
  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  	  HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);


//While loop Begins
      while(1) {
     Button = HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) ;  //reading the Button

     switch(State){
     //states of LEDs
          case 0: //Green onn
        	  HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);  // Red off
        	  HAL_Delay(200);
        	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);  // Green onn
        	  HAL_Delay(200);

        	if(Button == 1){
                 State++; //if button is not pressed goto next state
        	}
        	else{
        		State = 3;  //if button is pressed goto third state
        	}
          break;

          case 1:  //Blue onn
        	  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);  // Green off
        	  HAL_Delay(200);
           //changing Pin 3 as an output to turn it on
        	  GPIO_InitStruct.Pin = LED3_Pin;
        	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        	  HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

        	  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET); //Blue on
        	  HAL_Delay(200);
            // PIN 3 as an input to turn the LED off
        	  GPIO_InitStruct.Pin = LED3_Pin;
        	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        	  HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

        	  HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);  // Red off
        	  HAL_Delay(200);

        	  if(Button == 1){
                    State++;       //if button is not pressed go to next state
           	}
        	   else{
        	          State = 0;    //if button is pressed goto previous state
        	}
           break;

           case 2:  //Yellow on
        	  HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);  // Red off
        	  HAL_Delay(200);
       // Pin 3 as an output to turn yellow onn
              GPIO_InitStruct.Pin = LED3_Pin;
        	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        	  HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

        	  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET); //Yellow on
        	  HAL_Delay(200);
       // Pin 3 as an input to turn yellow off
        	 GPIO_InitStruct.Pin = LED3_Pin;
             GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        	 HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

           HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);  // Red off

           if(Button == 1){
                State++;    //goto next state if button is not pressed
            }
            else{
                   State = 1;   // goto previous state if button is pressed
           	}
            break;

           case 3: //Red onn
            HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);  // Green off
            HAL_Delay(200);
            HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);  // Red onn
            HAL_Delay(200);

            if(Button == 1){
                 State = 0;    // goto state 0 if button is not pressed
        	}
          	else{
                   	State = 2;   //goto previous state if button is pressed
            }
             break;
     } //switch statement ends
      } //while loop ends
}// main function ends
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////Previous codes when LEDs changed direction after completing one full cycle//////////////////////////////////////////
    //if(Button == 1)
  //{
	 // HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	 // HAL_Delay(1000);
	 // HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	  //HAL_Delay(250);

	 // GPIO_InitStruct.Pin = LED3_Pin;
	 // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	 // HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

	 // HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	 // HAL_Delay(1000);

	 // GPIO_InitStruct.Pin = LED3_Pin;
	 // GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	 // HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

	 // GPIO_InitStruct.Pin = LED3_Pin;
	 /// GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	 // HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

	 // HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	 // HAL_Delay(1000);

	  //GPIO_InitStruct.Pin = LED3_Pin;
	 // GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  //HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);
//
	 // HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
	 // HAL_Delay(1000);
	 // HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
	  //HAL_Delay(250);


  //else if(Button == 0){
	     // HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
	  	 //HAL_Delay(1000);
	  	 // HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
	  	  //HAL_Delay(250);

	  	  //GPIO_InitStruct.Pin = LED3_Pin;
	  	 // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  	 // HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

	  	  //HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	  	 // HAL_Delay(1000);

	  	  //GPIO_InitStruct.Pin = LED3_Pin;
	  	 // GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  	 // HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

	  	 // GPIO_InitStruct.Pin = LED3_Pin;
	  	 // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  	 // HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

	  	 // HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	  	 // HAL_Delay(1000);

	  	  //GPIO_InitStruct.Pin = LED3_Pin;
	  	  //GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  	 // HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

	  	 // HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	  	 // HAL_Delay(1000);
	  	//  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	  	 ///HAL_Delay(250);


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED8_Pin */
  GPIO_InitStruct.Pin = LED8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED8_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Button_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED2_Pin */
  GPIO_InitStruct.Pin = LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED3_Pin */
  GPIO_InitStruct.Pin = LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
