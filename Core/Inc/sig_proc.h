#ifndef SIG_PROC_H
# define SIG_PROC_H

# include <stdint.h>
# include <stdbool.h>
# include <math.h>
# include "stm32f4xx_hal.h"

#define V_REF 3.3f
#define RESISTOR 10000
#define SH_EQ_C1 0.001129148
#define SH_EQ_C2 0.000234125
#define SH_EQ_C3 0.0000000876741
#define ABS_ZERO 273.15

/*
 *	Store signal data that are used to get temperature from thermistor
 */
typedef	struct {
	uint32_t	current_time;
	uint16_t	raw;
	float		raw_filtered;
	float		voltage;
	float		resistance;
	float		temperature;
}	signal_t;

/*
 *	Used to store current average value for EMA (Exponential Moving Average)
 *	filtration.
 */
typedef struct {
	float	ema_cur;
	float	alpha;
	bool	initialized;
}	ema_t;

/**
 * Initialize fields of `filter`. Set initialization flag to 0 for first time
 * usage
 */
void	EMA_init(ema_t *filter, float alpha);

/*
 *	Applies Exponential Moving Average filter defined by `filter` to `raw` 
 *	value. Stores new current average value to `filter->ema_cur` and return it.
 *
 *	In case of "unitialized" filter, set initialization flag and return raw.
 */
float	EMA_update(ema_t *filter, uint16_t raw);

/* 
* Fills signal_t structure.
* Calculates:
*	- voltage[V] from `signal->raw_filtered` value;
*	- resistance[\Omega], using voltage divider equation; 
*	- temperature[\degC], using Reinhart-Hart equation, constants are define by SH_EQ_C1-3
*/
void	Calc_Physics(signal_t *signal);

#endif
