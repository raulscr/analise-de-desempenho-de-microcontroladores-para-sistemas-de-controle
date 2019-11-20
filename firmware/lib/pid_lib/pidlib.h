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
  * Exported functions
  */
pid_type* new_PID(pid_type *pid, pid_const_t Ka, pid_const_t Kb, pid_const_t Kc,
					int16_t ref, uint16_t min_output, uint16_t max_output);
void pidLoopRoutine(pid_type *pid);
void pidInterruptRoutine(pid_type *pid);

#endif


