/*
 * pid.h
 *
 *  Created on: 24 de out de 2018
 *      Author: raul
 */

#ifndef PID_LIB_PIDLIB_H_
#define PID_LIB_PIDLIB_H_

#include "qn_lib/types_qn.h"
#include "qn_lib/q7lib.h"
#include "qn_lib/q15lib.h"
#include "qn_lib/q31lib.h"
#include "includes.h"


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



typedef struct {
    pid_const_t Ka, Kb, Kc;
    pid_const_t ref;
    pid_const_t err;
    pid_const_t err_1;
    pid_const_t err_2;
    uint16_t min_output;
    uint16_t max_output;
    uint16_t output;
    uint16_t input;
    uint8_t loop;
} pid_type;






#ifndef PID_PERFORM_READ
#error "PID_PERFORM_READ(__INPUT__) must be defined"
#endif

#ifndef PID_PERFORM_WRITE
#error "PID_PERFORM_WRITE(__OUTPUT__) must be defined"
#endif


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

pid_type* new_PID(pid_type *pid, pid_const_t Ka, pid_const_t Kb, pid_const_t Kc,
					int16_t ref, uint16_t min_output, uint16_t max_output);

void pidLoopRoutine(pid_type *pid);
void pidInterruptRoutine(pid_type *pid);

#endif
