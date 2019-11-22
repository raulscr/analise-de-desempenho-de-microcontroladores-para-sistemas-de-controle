/**
  ******************************************************************************
  * @file    pidlib.c
  * @author  Raul Scarmocin
  * @version V2.0.1
  * @date    30-May-2019
  * @brief   This file provides all the PID-Control functions
  ******************************************************************************
  */

#include <portMCU.h>
#include "pidlib.h"

/**
  * @brief  Initializes the PID-Controller
  * @param  pid: pointer to a pid_type structure that will be initialized
  * @param  Ka:	Ka-Constant value, where Ka = (2*Kp*fs + Ki + 2*Kd*fs²)/(2*fs)
  * @param  Kb:	Kb-Constant value, where Kb = Kd*fs + Kp/2
  * @param  Kc:	Kc-Constant value, where Kc = Kd * fs / 2
  * @param  ref: reference value, in range of adc-input
  * @param  min_output: minimun output value, in range of pwm-output
  * @param  max_output: maximun output value, in range of pwm-output
  * @retval initialized pid_type pointer
  */
pid_type* new_PID(pid_type *pid, pid_const_t Ka, pid_const_t Kb, pid_const_t Kc,
			int16_t ref, uint16_t min_output, uint16_t max_output){

	pid->Ka = Ka;
	pid->Kb = Kb;
	pid->Kc = Kc;

	pid->ref = ref;
	pid->min_output = min_output;
	pid->max_output = max_output;

	pid->err_2 = 0;
	pid->err_1 = 0;
	pid->err = 0;

	pid->input = 0;
	pid->output = 0;

	pid->loop = 0;

	return pid;
}


/**
  * @brief  Update the pid controller
  * @note   Must be placed in the main-loop
  * @note   The flag must be set periodically, preferencially by a timer interrupt
  * @param  pid: pointer to a pid_type structure that will be updated
  * @retval none
  */
#if defined(RAM_RUN) && defined(RAM_ATTRIBUTE)
RAM_ATTRIBUTE
#endif 
inline void pidLoopRoutine(pid_type *pid){
    if(pid->loop){

	/**
	  * @brief  Exclude Peripheral operations to measure just the CPU operations
	  */
	#ifndef EXCLUDE_PERIPH_OP

        PID_PERFORM_WRITE(pid->output);
        PID_PERFORM_READ(pid->input);

	#endif

        SET_TEST_PIN;

	/**
	  * @brief  Exclude CPU operations to measure just the peripheral operations
	  */
	#ifndef EXCLUDE_CALC_OP


	/**
	  * @brief  Simulate a Volt-to-quantizer conversion cast using divisions
	  */
	#ifdef TEST_WITH_DIV

        volatile int unused_var;
        uint8_t i = TEST_WITH_DIV + 1;
        while(i--)
            unused_var = pid->input / (double)i;

	#endif



	/**
	  * @brief  PID-Controller specific operations
	  */
        pid->err_2 = pid->err_1;
        pid->err_1 = pid->err;
        pid->err = pid->ref - pid->input;

        pid->output = SUM(MULT(pid->Ka, pid->err), (pid_const_t)pid->output);
        pid->output = SUM(MULT(pid->Kb, pid->err_1), (pid_const_t)pid->output);
        pid->output = SUM(MULT(pid->Kc, pid->err_2), (pid_const_t)pid->output);

        if(pid->output > pid->max_output)
            pid->output = pid->max_output;

        if(pid->output < pid->min_output)
            pid->output = pid->min_output;

        pid->loop = 0;

	#endif
        RESET_TEST_PIN;
        RESET_TEST_PIN_2;
    }
}

/**
  * @brief  Function placed in the timer interrupt to periodically set the flag
  * @param  pid: pointer to a pid_type structure that will be updated
  * @retval none
  */
#if defined(RAM_RUN) && defined(RAM_ATTRIBUTE)
RAM_ATTRIBUTE
#endif
inline void pidInterruptRoutine(pid_type *pid){

    SET_TEST_PIN_2;
    RESET_TIMER_FLAGS;
    pid->loop = 1;

}


