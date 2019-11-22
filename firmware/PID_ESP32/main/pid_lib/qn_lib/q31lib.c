/**
  ******************************************************************************
  * @file    q31lib.c
  * @author  Raul Scarmocin
  * @version V2.0.0
  * @date    30-May-2019
  * @brief   This file provides all the Q31 functions
  ******************************************************************************
  */

#include "types_qn.h"
#include "q31lib.h"




/**
  * @brief  Perform the convertion of a double value to Q31
  * @param  n: double value to be converted 
  * @retval n converted to Q31-format
  */
q31_t double_to_q31(double n){
    return (q31_t)(n * 0x80000000);         //  31bit shift (2^31 = 0x80000000)
}

/**
  * @brief  Perform the convertion of a Q31 to double value
  * @param  n: Q31-formated value
  * @retval n in double format
  */
double q31_to_double(q31_t n){
    return (double)(((double long)n) / 0x80000000);
}

/**
  * @brief  Perform the addition of two Q31 values
  * @note   Avoid overflow and underflow by saturation (max value = 2^31, min value = - 2^31)
  * @note   Subraction is a particular case of this function
  * @param  n1: Q31-formated first value
  * @param  n2: Q31-formated second value
  * @retval Q31-formated value that represents the addition of n1 and n2
  */
inline q31_t q31_sum(q31_t n1, q31_t n2){
    q63_t   aux;

    aux = (q63_t)n1 + (q63_t)n2;

    if(aux > 0x7FFFFFFF)
        aux = 0x7FFFFFFF;
    else if(aux < -0x7FFFFFFF)
        aux = -0x7FFFFFFF;

    return (q31_t)aux;
}

/**
  * @brief  Perform the multiplication of two Q31 values
  * @note   The result is a Q63 value, but the 31 LSB are discarted
  * @param  n1: Q31-formated first value
  * @param  n2: Q31-formated second value
  * @retval Q31-formated value that represents the multiplication of n1 and n2
  */
inline q31_t q31_mult(q31_t n1, q31_t n2){

    q63_t   aux;
    aux = (q63_t)n1 * (q63_t)n2;

    return aux >> 31;

}

/**
  * @brief  Perform the division of two Q31 values
  * @note   To avoid the lose of the first bits, the first value is bit-shifted 31-bits to left
  * @param  n1: Q31-formated first value
  * @param  n2: Q31-formated second value
  * @retval Q31-formated value that represents the division of n1 and n2
  */
inline q31_t q31_div(q31_t n1, q31_t n2){

    q63_t   aux;
    aux = (q63_t)n1 << 31;

    return aux / (q63_t)n2;

}


