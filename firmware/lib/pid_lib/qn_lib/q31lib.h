/**
  ******************************************************************************
  * @file    q31lib.h
  * @author  Raul Scarmocin
  * @version V1.0.0
  * @date    30-May-2019
  * @brief   This file provides the Q31 addition, multiplication and division functions
  * @note    Subraction is a particular case of addition
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef Q31LIB_H_
#define Q31LIB_H_


#include "types_qn.h"

q31_t double_to_q31(double n);
double q31_to_double(q31_t n);

q31_t q31_sum(q31_t n1, q31_t n2);
q31_t q31_mult(q31_t n1, q31_t n2);
q31_t q31_div(q31_t n1, q31_t n2);

#endif
