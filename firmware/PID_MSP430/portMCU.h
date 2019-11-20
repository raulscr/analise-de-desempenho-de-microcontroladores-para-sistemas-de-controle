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
#include <msp430.h>
#include <stdint.h>


#define     Q7_OP
#define     RAM_RUN
//#define     RAM_ATTRIBUTE
//#define   TEST_WITH_DIV     5

//#define PWM_FREQ		2000
//#define COUNTER_PERIOD	8400
#define TIM_FREQ		500
#define DUTY_RES    		255

#ifdef Q7_OP
#define ADC_RANGE		127
#else
#define ADC_RANGE		1023
#endif



#define SET_TEST_PIN                P1OUT |= BIT4

#define RESET_TEST_PIN              P1OUT &= ~BIT4

#define SET_TEST_PIN_2              P1OUT |= BIT5

#define RESET_TEST_PIN_2            P1OUT &= ~BIT5

#define RESET_TIMER_FLAGS           TA0CTL &= ~TAIFG

#ifdef Q7_OP
#define PID_PERFORM_READ(__INPUT__)     ({                  \
                                            ADC10CTL0 |= ADC10SC + ENC;\
                                            while(ADC10CTL1 & ADC10BUSY);\
                                            __INPUT__ = ADC10MEM;\
                                        })
#else
#define PID_PERFORM_READ(__INPUT__)     ({                  \
                                            ADC10CTL0 |= ADC10SC + ENC;\
                                            while(ADC10CTL1 & ADC10BUSY);\
                                            __INPUT__ = (ADC10MEM >> 3);\
                                        })
#endif

#define PID_PERFORM_WRITE(__OUTPUT__)   ({                  \
                                            TA1CCR1 = __OUTPUT__;\
                                        })


/**
  * Data-types definitions according to the user-sets (includes.h must be configured by user)
  */

#if defined(Q7_OP)

#include "qn_lib/q7lib.h"
typedef q7_t   pid_const_t;
#define PARSE_OP(NUM) double_to_q7(NUM)
#define SUM(NUM1, NUM2) q7_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) (q7_mult(NUM1, NUM2))
#define DIV(NUM1, NUM2) q7_div(NUM1, NUM2)

#elif defined(Q15_OP)

#include "qn_lib/q15lib.h"
typedef q15_t   pid_const_t;
#define PARSE_OP(NUM) double_to_q15(NUM)
#define SUM(NUM1, NUM2) q15_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q15_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q15_div(NUM1, NUM2)
/*
#elif defined(Q31_OP)

#include "qn_lib/q31lib.h"
typedef q31_t   pid_const_t;
#define PARSE_OP(NUM) double_to_q31(NUM)
#define SUM(NUM1, NUM2) q31_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q31_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q31_div(NUM1, NUM2)
*/
#elif defined(DOUBLE_OP)

typedef double   pid_const_t;
#define PARSE_OP(NUM) (double)(NUM)
#define SUM(NUM1, NUM2) (NUM1 + NUM2)
#define MULT(NUM1, NUM2) (NUM1 * NUM2)
#define DIV(NUM1, NUM2) (NUM1 / NUM2)

#else

typedef float   pid_const_t;
#define PARSE_OP(NUM) (float)(NUM)
#define SUM(NUM1, NUM2) (NUM1 + NUM2)
#define MULT(NUM1, NUM2) (NUM1 * NUM2)
#define DIV(NUM1, NUM2) (NUM1 / NUM2)

#endif

#endif
