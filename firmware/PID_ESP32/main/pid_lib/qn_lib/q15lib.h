#ifndef Q15LIB_H_
#define Q15LIB_H_

#include "types_qn.h"

q15_t double_to_q15(double n);
double q15_to_double(q15_t n);

q15_t q15_sum(q15_t n1, q15_t n2);
q15_t q15_mult(q15_t n1, q15_t n2);
q15_t q15_div(q15_t n1, q15_t n2);


#endif
