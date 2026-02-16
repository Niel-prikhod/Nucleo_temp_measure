#include "data_acq.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2; 

volatile uint16_t g_adc_data[SENSOR_BUFFER_SIZE];
volatile bool  g_sensor_data_flag = 0;

void Sensor_Start(void) {
	if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)g_adc_data, SENSOR_BUFFER_SIZE)
		!= HAL_OK) {
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

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	static int	counter;

    if (hadc->Instance == ADC1) {
        g_sensor_data_flag = 1;
        counter = 0;
        counter++;
        if (counter >= 200) {
            HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
            counter = 0;
        }
    }
}
