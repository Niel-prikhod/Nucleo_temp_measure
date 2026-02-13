#ifndef INC_DATA_ACQ_H_
# define INC_DATA_ACQ_H_

# include "main.h"

// --- Configuration ---
#define SENSOR_BUFFER_SIZE  1   // We only need 1 sample per interrupt for now

// --- Public Variables ---
extern volatile uint16_t adc_raw_buffer[SENSOR_BUFFER_SIZE];
extern volatile uint8_t  sensor_new_data_flag;

// data_acq.c
void Sensor_Start(void);  // Kicks off the Timer and DMA

#endif
