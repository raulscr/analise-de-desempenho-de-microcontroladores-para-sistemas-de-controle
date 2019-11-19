
#include "string.h"
#include "pidlib.h"
#include "includes.h"

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

#if defined(RAM_RUN) && defined(RAM_ATTRIBUTE)
RAM_ATTRIBUTE
#endif 
inline void pidLoopRoutine(pid_type *pid){
    if(pid->loop){
#ifndef EXCLUDE_PERIPH_OP
        PID_PERFORM_WRITE(pid->output);
        PID_PERFORM_READ(pid->input);
#endif

        SET_TEST_PIN;

#ifndef EXCLUDE_CALC_OP

#ifdef TEST_WITH_DIV
        int unused_var, i = TEST_WITH_DIV + 1;
        while(i--)
            unused_var = pid->input / i;
#endif

        pid->err_2 = pid->err_1;
        pid->err_1 = pid->err;
        pid->err = pid->ref - pid->input;

        pid->output = SUM(MULT(pid->Ka, pid->err), (pid_const_t)pid->output);
        pid->output = SUM(-MULT(pid->Kb, pid->err_1), (pid_const_t)pid->output);
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


#if defined(RAM_RUN) && defined(RAM_ATTRIBUTE)
RAM_ATTRIBUTE
#endif
inline void pidInterruptRoutine(pid_type *pid){

    SET_TEST_PIN_2;
    RESET_TIMER_FLAGS;
    pid->loop = 1;

}
