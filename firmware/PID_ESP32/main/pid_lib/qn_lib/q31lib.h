#ifndef Q31LIB_H_
#define Q31LIB_H_


#include "types_qn.h"

q31_t double_to_q31(double n);
double q31_to_double(q31_t n);

q31_t q31_sum(q31_t n1, q31_t n2);
q31_t q31_mult(q31_t n1, q31_t n2);
q31_t q31_div(q31_t n1, q31_t n2);

#endif
