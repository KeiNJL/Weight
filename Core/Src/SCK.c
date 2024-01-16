
#include "main.h"
#include "gpio.h"
#include "tim.h"

static volatile uint8_t counter = 0;
static volatile uint32_t data = 0;
static volatile uint32_t read_data = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim ->Instance == TIM3)
	{

		if (counter >= 51)
		{
			HAL_TIM_Base_Stop_IT(&htim3);
			read_data = data;
			HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
			counter=0;
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			 __HAL_GPIO_EXTI_CLEAR_IT(DOUT_Pin);
			HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
		}else if (counter==0)
		{
			HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
		}
		else
		{
			if (counter%2 == 1)
			{
				HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
			}
			if (counter%2 == 0)
//			if (counter%2 == 0 && counter != 0)
			{
				if (HAL_GPIO_ReadPin(DOUT_GPIO_Port, DOUT_Pin) == GPIO_PIN_SET)
				{
					data = 1 | data;
				}
				data = data << 1;
				HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
			}
		}
	counter ++;
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin == DOUT_Pin)
   {
	   HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	   HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
	   data = 0;
	   counter = 0;
	   HAL_TIM_Base_Start_IT(&htim3);
   }
}
