/**
  ******************************************************************************
  * @file    pidlib.h
  * @author  Raul Scarmocin
  * @version V2.0.0
  * @date    30-May-2019
  * @brief   This file provides all the PID-Control functions
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PID_LIB_PIDLIB_H_
#define PID_LIB_PIDLIB_H_

#include "qn_lib/types_qn.h"
#include "qn_lib/q7lib.h"
#include "qn_lib/q15lib.h"
#include "qn_lib/q31lib.h"
#include "portMCU.h"


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




/** 
  * @brief  PID-Controller Structure definition  
  * @param  Ka:	Ka-Constant value, where 
  * @param  Ka:	Kb-Constant value, where Kb = Kd*fs + Kp/2
  * @param  Ka:	Kc-Constant value, where Kc = Kd * fs / 2
  * @param  ref: reference value, in range of adc-input
  * @param  min_output: minimum output value, in range of pwm-output
  * @param  max_output: maximum output value, in range of pwm-output
  */
typedef struct {
    pid_const_t Ka, Kb, Kc;		/* PID-Controller constants, where 
						Ka = (2*Kp*fs + Ki + 2*Kd*fs²)/(2*fs)
						Kb = Kd*fs + Kp/2
						Kc = Kd * fs / 2
					*/
    pid_const_t ref;			// reference value, in range of adc-input
    pid_const_t err;			// error value e[k], defined by ref - input[k]
    pid_const_t err_1;			// e[k-1]
    pid_const_t err_2;			// e[k-2]
    uint16_t min_output;		// minimum output value, in range of pwm-output
    uint16_t max_output;		// maximum output value, in range of pwm-output
    uint16_t output;			// output value, in range of PWM-range (or similar)
    uint16_t input;			// output value, in range of ADC-range
    uint8_t loop;			// loop flag, used to update the PID-Controller periodically
} pid_type;





/**
  * Error-prevent to define read and write operations
  * PID_PERFORM_READ and PID_PERFORM_WRITE must be defined by user in includes.h file
  */


#ifndef PID_PERFORM_READ
#error "PID_PERFORM_READ(__INPUT__) must be defined"
#endif

#ifndef PID_PERFORM_WRITE
#error "PID_PERFORM_WRITE(__OUTPUT__) must be defined"
#endif

/**
  * Define PARSE-OP according to the data-type used in the operations
  */
#if defined(Q7_OP)
#define PARSE_OP(NUM) double_to_q7(NUM)
#elif defined(Q15_OP)
#define PARSE_OP(NUM) double_to_q15(NUM)
#elif defined(Q31_OP)
#define PARSE_OP(NUM) double_to_q31(NUM)
#elif defined(INT_OP)
#define PARSE_OP(NUM) (int)(NUM)
#else
#define PARSE_OP(NUM) NUM
#endif


/**
  * Exported functions
  */
pid_type* new_PID(pid_type *pid, pid_const_t Ka, pid_const_t Kb, pid_const_t Kc,
					int16_t ref, uint16_t min_output, uint16_t max_output);
void pidLoopRoutine(pid_type *pid);
void pidInterruptRoutine(pid_type *pid);

#endif


