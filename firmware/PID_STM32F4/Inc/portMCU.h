/**
  ******************************************************************************
  * @file    portMCU.h
  * @author  Raul Scarmocin
  * @version V2.0
  * @date    21-Jun-2019
  * @brief   This file provides MCU-peripheral control to the pid-controller
  ******************************************************************************
  */

#ifndef PORTMCU_H_
#define PORTMCU_H_
#include "stm32f4xx_hal.h"
#include "stm32f407xx.h"
#include "qn_lib/types_qn.h"

#define Q15_OP
#define RAM_RUN
//#define TEST_WITH_DIV   		2
//#define EXCLUDE_PERIPH_OP
//#define EXCLUDE_CALC_OP


#define TIM_FREQ		5000
#define PWM_FREQ		5000
#define COUNTER_PERIOD	8400

#ifdef Q7_OP
#define DUTY_RES		127
#define ADC_RANGE		127
#else
#define DUTY_RES		COUNTER_PERIOD
#define ADC_RANGE		4095
#endif


#define RAM_ATTRIBUTE __attribute__((long_call))



#define SET_TEST_PIN            	GPIOA->BSRR = GPIO_PIN_1

#define RESET_TEST_PIN          	GPIOA->BSRR = (uint32_t)GPIO_PIN_1 << 16U

#define SET_TEST_PIN_2          	GPIOA->BSRR = GPIO_PIN_4

#define RESET_TEST_PIN_2          	GPIOA->BSRR = (uint32_t)GPIO_PIN_4 << 16U

#define RESET_TIMER_FLAGS

#ifdef Q7_OP
#define PID_PERFORM_READ(__INPUT__)		({					\
											ADC1->SR |= ADC_FLAG_STRT;\
											while(!(ADC1->SR & ADC_FLAG_EOC));\
											ADC1->SR &= ~(ADC_FLAG_STRT | ADC_FLAG_EOC);\
											__INPUT__ = (ADC1->DR >> 5);\
										})
#else
#define PID_PERFORM_READ(__INPUT__)		({					\
											ADC1->SR |= ADC_FLAG_STRT;\
											while(!(ADC1->SR & ADC_FLAG_EOC));\
											ADC1->SR &= ~(ADC_FLAG_STRT | ADC_FLAG_EOC);\
											__INPUT__ = ADC1->DR;\
										})
#endif

#define PID_PERFORM_WRITE(__OUTPUT__)	({					\
											TIM1->CCR3 = __OUTPUT__;\
										})


/**
  * Data-types definitions according to the user-sets (includes.h must be configured by user)
  */


/**
  * Define PARSE-OP according to the data-type used in the operations
  */
#if defined(Q7_OP)
typedef q7_t   pid_const_t;
#define PARSE_OP(NUM) double_to_q7(NUM)
#define SUM(NUM1, NUM2) q7_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q7_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q7_div(NUM1, NUM2)

#elif defined(Q15_OP)
typedef q15_t   pid_const_t;
#define PARSE_OP(NUM) double_to_q15(NUM)
#define SUM(NUM1, NUM2) q15_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q15_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q15_div(NUM1, NUM2)

#elif defined(Q31_OP)
typedef q31_t   pid_const_t;
#define PARSE_OP(NUM) double_to_q31(NUM)
#define SUM(NUM1, NUM2) q31_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q31_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q31_div(NUM1, NUM2)

#else
#define PARSE_OP(NUM) (NUM)
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

