#ifndef UTILS_H
# define UTILS_H

# include "stm32f4xx_hal.h"
# include "stm32f4xx_hal_uart.h"
# include "sig_proc.h"
# include <stdarg.h>
# include <stdio.h>

/* 
* Custom printf wrapper for UART communication
* relies on internal buffer (char[128])
*/
int		ser_printf(UART_HandleTypeDef *huart, char *format, ...);

/*
* Sends thermistor's data in CSV format via UART:
* time_ms, adc_raw, adc_raw_filtered, voltage_V, resistance_Ohm, temperature_C 
*/
int		send_csv(UART_HandleTypeDef *huart, signal_t signal);

#endif
