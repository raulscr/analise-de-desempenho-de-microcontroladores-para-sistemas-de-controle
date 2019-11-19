/*
 * includes.h
 *
 *  Created on: 18 de mar de 2019
 *      Author: Raul
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_


#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "stm32f103xb.h"

#define FLOAT_OP
#define RAM_RUN
//#define TEST_WITH_DIV   		2
//#define EXCLUDE_PERIPH_OP
//#define EXCLUDE_CALC_OP


#define RAM_ATTRIBUTE __attribute__((long_call))



#define SET_TEST_PIN            	GPIOA->BSRR = GPIO_PIN_8

#define RESET_TEST_PIN          	GPIOA->BSRR = (uint32_t)GPIO_PIN_8 << 16U

#define SET_TEST_PIN_2          	GPIOA->BSRR = GPIO_PIN_9

#define RESET_TEST_PIN_2          	GPIOA->BSRR = (uint32_t)GPIO_PIN_9 << 16U

#define RESET_TIMER_FLAGS

#define PID_PERFORM_READ(__INPUT__)		({					\
											__INPUT__ = ADC1->DR;\
										})

#define PID_PERFORM_WRITE(__OUTPUT__)	({					\
											TIM1->CCR3 = __OUTPUT__;\
										})

#endif /* INCLUDES_H_ */
