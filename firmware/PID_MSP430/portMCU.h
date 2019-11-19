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


#define     FLOAT_OP
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



void setTestPin();

void resetTestPin();

void setTestPinCalc();

void resetTestPinCalc();


/*
 * Macro to clear timer flags on ISR
 */
void resetTimerFlags();

/*
 * Macro to read the ADC
 * if Q7_OP defined, the 12-bits must be ranged to 7-bits (loses 5-bits of resolution)
 * ADC2 must be used carefully, Wireless module must use it
 */

void adcRead(pid_const_t *input);

/*
 * Macro to write at the PWM modules
 * LEDC sounds non-linear
 */

void pwmWrite(pid_const_t output);



#endif
