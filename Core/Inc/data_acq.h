#ifndef INC_DATA_ACQ_H_
# define INC_DATA_ACQ_H_

# include "main.h"

#define SENSOR_BUFFER_SIZE  1 

extern volatile uint16_t	g_adc_data[SENSOR_BUFFER_SIZE];
extern volatile bool		g_sensor_data_flag;

/*
*  Starts the ADC in DMA mode first, then start the timer 
*/
void Sensor_Start(void);  

/*
*		--- Interrupt Callback ---
*	Override of the HAL library's function.
*	It calls this function automatically when DMA finishes.
*	Add visual effect - toggle LED every 200 ticks
*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

#endif
