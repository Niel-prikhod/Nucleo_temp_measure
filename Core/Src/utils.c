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
	uint32_t	current_time;
	uint16_t	raw;
	float		voltage;
	int			len;

	current_time = HAL_GetTick();
	raw = adc_raw_buffer[0];
	voltage = (raw / 4095.0f) * 3.3f;
	len = ser_printf(huart, "%lu, %u, %.2f, 0, 0, 0\r\n", 
	   current_time, raw, voltage);
	return len;
}

