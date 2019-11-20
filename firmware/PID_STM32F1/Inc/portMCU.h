/*
 * includes.h
 *
 *  Created on: 18 de mar de 2019
 *      Author: Raul
 */

#ifndef PORTMCU_H_
#define PORTMCU_H_


#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "stm32f103xb.h"


#define PWM_FREQ		5000
#define COUNTER_PERIOD	3600
#define TIM_FREQ		5000

#ifdef Q7_OP
#define DUTY_RES		127
#define ADC_RANGE		127
#else
#define DUTY_RES		COUNTER_PERIOD
#define ADC_RANGE		4095
#endif


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
											ADC1->SR |= ADC_FLAG_STRT;\
											while(!(ADC1->SR & ADC_FLAG_EOC));\
											ADC1->SR &= ~(ADC_FLAG_STRT | ADC_FLAG_EOC);\
										})

#define PID_PERFORM_WRITE(__OUTPUT__)	({					\
											TIM1->CCR3 = __OUTPUT__;\
										})




/**
  * Data-types definitions according to the user-sets (includes.h must be configured by user)
  */

#if defined(Q7_OP)
typedef q7_t   pid_const_t;
#define SUM(NUM1, NUM2) q7_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q7_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q7_div(NUM1, NUM2)

#elif defined(Q15_OP)
typedef q15_t   pid_const_t;
#define SUM(NUM1, NUM2) q15_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q15_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q15_div(NUM1, NUM2)

#elif defined(Q31_OP)
typedef q31_t   pid_const_t;
#define SUM(NUM1, NUM2) q31_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q31_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q31_div(NUM1, NUM2)

#else
#define SUM(NUM1, NUM2) (NUM1 + NUM2)
#define MULT(NUM1, NUM2) (NUM1 * NUM2)
#define DIV(NUM1, NUM2) (NUM1 / NUM2)

#if defined(FLOAT_OP)
typedef float   pid_const_t;
#elif defined(DOUBLE_OP)
typedef double   pid_const_t;
#else
typedef int   pid_const_t;
#endif

#endif

#endif /* PORTMCU_H_ */
