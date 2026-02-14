#include "main.h"

/* 
	* Custom printf wrapper for UART communication
	* relies on internal buffer (char[128])
*/
int	ser_printf(UART_HandleTypeDef *huart, char *format, ...) {
	int		len;
	char	ser_buf[128]; 
	va_list	args;

	va_start(args, format);
	len = vsnprintf(ser_buf, sizeof(ser_buf), format, args);
	va_end(args);
	if (len > 0 && huart != NULL) {
		HAL_UART_Transmit(huart, (uint8_t*)ser_buf, len, 100);
	}
	return len;
}

int send_voltage(UART_HandleTypeDef *huart, volatile uint16_t *adc_raw_buffer) {
	signal_t	signal;
	int			len;
	float		logR;

	signal.current_time = HAL_GetTick();
	signal.raw = adc_raw_buffer[0];
	signal.voltage = (signal.raw / 4095.0f) * V_REF;
	signal.resistance = signal.voltage * RESISTOR / (V_REF - signal.voltage);
	logR = logf(signal.resistance);
	signal.temperature = (1.0 / (SH_EQ_C1 + SH_EQ_C2 * logR + SH_EQ_C3 * logR * logR * logR)) - ABS_ZERO;
	len = ser_printf(huart, "%lu, %u, %.2f, %.2f, %.2f, 0\r\n", 
	   signal.current_time, signal.raw, signal.voltage, signal.resistance, signal.temperature);
	return len;
}

