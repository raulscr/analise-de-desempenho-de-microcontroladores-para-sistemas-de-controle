/**
  ******************************************************************************
  * @file    q7lib.c
  * @author  Raul Scarmocin
  * @version V2.0.0
  * @date    30-May-2019
  * @brief   This file provides all the Q7 functions
  ******************************************************************************
  */

#include "types_qn.h"
#include "q7lib.h"


/**
  * @brief  Perform the convertion of a double value to Q7
  * @param  n: double value to be converted 
  * @retval n converted to Q7-format
  */
q7_t double_to_q7(double n){
    return (q7_t)(n * 0x80);            //  7bit shift (2^7 = 0x80)
}

/**
  * @brief  Perform the convertion of a Q7 to double value
  * @param  n: Q7-formated value
  * @retval n in double format
  */
double q7_to_double(q7_t n){
    return (double)(((double long)n) / 0x80);
}


/**
  * @brief  Perform the addition of two Q7 values
  * @note   Avoid overflow and underflow by saturation (max value = 2^7, min value = - 2^7)
  * @note   Subraction is a particular case of this function
  * @param  n1: Q7-formated first value
  * @param  n2: Q7-formated second value
  * @retval Q7-formated value that represents the addition of n1 and n2
  */
inline q7_t q7_sum(q7_t n1, q7_t n2){
    q15_t   aux;

    aux = (q15_t)n1 + (q15_t)n2;

    if(aux > 0x7F)
        aux = 0x7F;
    else if(aux < -0x7F)
        aux = -0x7F;

    return (q7_t)aux;
}

/**
  * @brief  Perform the multiplication of two Q7 values
  * @note   The result is a Q15 value, but the 7 LSB are discarted
  * @param  n1: Q7-formated first value
  * @param  n2: Q7-formated second value
  * @retval Q7-formated value that represents the multiplication of n1 and n2
  */
inline q7_t q7_mult(q7_t n1, q7_t n2){

    q15_t   aux;
    aux = (q15_t)n1 * (q15_t)n2;

    return aux >> 7;

}

/**
  * @brief  Perform the division of two Q7 values
  * @note   To avoid the lose of the first bits, the first value is bit-shifted 7-bits to left
  * @param  n1: Q7-formated first value
  * @param  n2: Q7-formated second value
  * @retval Q7-formated value that represents the division of n1 and n2
  */
inline q7_t q7_div(q7_t n1, q7_t n2){

    q15_t   aux;
    aux = (q15_t)n1 << 7;

    return aux / (q15_t)n2;

}

