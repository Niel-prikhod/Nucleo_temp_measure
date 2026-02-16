#include "main.h"


void	EMA_init(ema_t	*filter, float alpha) {
	filter->ema_cur = 0.0f; 
	filter->alpha = alpha;
	filter->initialized = 0;
}

float	EMA_update(ema_t *filter, uint16_t raw) {
	if (!filter)
		return 0;
	if (!filter->initialized) {
		filter->ema_cur = raw;
		filter->initialized = 1;
	}
	else {
		filter->ema_cur = filter->ema_cur *(1 - filter->alpha) + (float)raw *
			filter->alpha;
	}
	return filter->ema_cur;
}

void	Calc_Physics(signal_t *signal) {
	float		logR;

	signal->current_time = HAL_GetTick();
	signal->voltage = (signal->raw_filtered / 4095.0f) * V_REF;
	signal->resistance = signal->voltage * RESISTOR / (V_REF - signal->voltage);
	logR = logf(signal->resistance);
	signal->temperature = (1.0 / (SH_EQ_C1 + SH_EQ_C2 * logR + SH_EQ_C3 * logR * logR * logR)) - ABS_ZERO;
}
