
#include "main.h"
#include "gpio.h"
#include "tim.h"

static uint8_t counter = 0;
static uint32_t data = 0;
static volatile uint32_t read_data = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim ->Instance == TIM3)
	{
		counter++;
		if (counter == 50)
		{
			HAL_TIM_Base_Stop_IT(&htim3);
			read_data = data;
			HAL_NVIC_EnableIRQ(EXTI_LINE_14);
		}
		else
		{
			if (counter%2 == 1)
			{
				HAL_GPIO_TogglePin(SCK_GPIO_Port, SCK_Pin);
			}
			if ((counter%2 == 0) && (counter != 0))
			{
				if (HAL_GPIO_ReadPin(DOUT_GPIO_Port, DOUT_Pin) == GPIO_PIN_SET)
				{
					data = 1 | data;
				}
				data = data << 1;
				HAL_GPIO_TogglePin(SCK_GPIO_Port, SCK_Pin);
			}
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin == DOUT_Pin)
   {
	   data = 0;
	   counter = 0;
	   HAL_NVIC_DisableIRQ(EXTI_LINE_14);
	   HAL_TIM_Base_Start_IT(&htim3);
   }
}


