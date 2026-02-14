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
	len = vsprintf(ser_buf, format, args);
	if (len > 0) {
		HAL_UART_Transmit(huart, (uint8_t*)ser_buf, len, 100);
	}
	va_end(args);
	return len;
}
