/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
# include <stdio.h>
# include <stdarg.h>
# include <math.h>
# include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_LED_Pin GPIO_PIN_5
#define USER_LED_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
#define EMA_ALPHA 0.1
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
	uint16_t	raw_filtered;
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

// utils.c
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

// sig_proc.c
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

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
