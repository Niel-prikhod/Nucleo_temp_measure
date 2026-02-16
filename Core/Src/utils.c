#include "utils.h"

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

int send_csv(UART_HandleTypeDef *huart, signal_t signal) {
	int len;

	len = ser_printf(huart, "%lu, %u, %.2f, %.2f, %.2f, %.2f\r\n", 
		signal.current_time, 
		signal.raw,
		signal.raw_filtered,
		signal.voltage, 
		signal.resistance,
		signal.temperature);
	return len;
}

