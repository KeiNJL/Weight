/*
 * SCK.c
 *
 *  Created on: Dec 14, 2023
 *      Author: User
 */

#include "main.h"
#include "gpio.h"
#include "tim.h"

static uint8_t counter = 0;
//static uint8_t data[10];
//static uint8_t i = 0;

void start(void)
{
	counter = 0;
//		if (HAL_GPIO_ReadPin(DOUT_GPIO_Port,DOUT_Pin) == GPIO_PIN_RESET)
//		{
			HAL_TIM_Base_Start_IT(&htim3);
//		}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim ->Instance == TIM3)
	{
		counter++;
		if (counter == 50)
		{
			HAL_TIM_Base_Stop_IT(&htim3);
			counter = 0;
//			i = 0;
		}
		if (counter%2 == 1)
		{
			HAL_GPIO_TogglePin(SCK_GPIO_Port, SCK_Pin);
		}
		if (counter%2 == 0)
		{
			/*data[i] =*/HAL_GPIO_ReadPin(DOUT_GPIO_Port, DOUT_Pin);
			HAL_GPIO_TogglePin(SCK_GPIO_Port, SCK_Pin);
//			i++;
		}
	}
}

