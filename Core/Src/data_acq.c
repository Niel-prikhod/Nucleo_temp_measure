#include "data_acq.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2; 

volatile uint16_t adc_raw_buffer[SENSOR_BUFFER_SIZE];
volatile uint8_t  sensor_new_data_flag = 0;

void Sensor_Start(void)
/*
*  Starts the ADC in DMA mode first, then start the timer 
*/
{
	if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_raw_buffer, SENSOR_BUFFER_SIZE) != HAL_OK) {
		HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_SET); 
        while(1);
    }
    if (HAL_TIM_Base_Start(&htim2) != HAL_OK) {
        while(1) {
            HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
            HAL_Delay(50); 
        }  
	}
	HAL_TIM_GenerateEvent(&htim2, TIM_IT_UPDATE);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
/*
--- Interrupt Callback ---
*	Override of the HAL library's function.
*	It calls this function automatically when DMA finishes.
*	Add visual effect - toggle LED every 200 ticks
*/
{
    if (hadc->Instance == ADC1) {
        sensor_new_data_flag = 1;

        static int counter = 0;
        counter++;

        if (counter >= 200)
        {
            HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
            counter = 0;
        }
    }
}
