#ifndef Q7LIB_H_
#define Q7LIB_H_

#include "types_qn.h"

q7_t double_to_q7(double n);
double q7_to_double(q7_t n);

q7_t q7_sum(q7_t n1, q7_t n2);
q7_t q7_mult(q7_t n1, q7_t n2);
q7_t q7_div(q7_t n1, q7_t n2);

#endif
