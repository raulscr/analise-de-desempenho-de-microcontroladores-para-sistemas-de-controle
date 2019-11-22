/**
  ******************************************************************************
  * @file    q15lib.h
  * @author  Raul Scarmocin
  * @version V1.0.0
  * @date    30-May-2019
  * @brief   This file provides the Q15 addition, multiplication and division functions
  * @note    Subraction is a particular case of addition
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef Q15LIB_H_
#define Q15LIB_H_

#include "types_qn.h"

q15_t double_to_q15(double n);
double q15_to_double(q15_t n);

q15_t q15_sum(q15_t n1, q15_t n2);
q15_t q15_mult(q15_t n1, q15_t n2);
q15_t q15_div(q15_t n1, q15_t n2);


#endif
