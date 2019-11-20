/**
  ******************************************************************************
  * @file    q15lib.c
  * @author  Raul Scarmocin
  * @version V2.0.0
  * @date    30-May-2019
  * @brief   This file provides all the Q15 functions
  ******************************************************************************
  */

#include "types_qn.h"
#include "q15lib.h"




/**
  * @brief  Perform the convertion of a double value to Q15
  * @param  n: double value to be converted 
  * @retval n converted to Q15-format
  */
q15_t double_to_q15(double n){
	return (q15_t)(n * 0x8000);			//	15bit shift (2^15 = 0x8000)
}


/**
  * @brief  Perform the convertion of a Q15 to double value
  * @param  n: Q15-formated value
  * @retval n in double format
  */
double q15_to_double(q15_t n){
	return (double)(((double long)n) / 0x8000);
}


/**
  * @brief  Perform the addition of two Q15 values
  * @note   Avoid overflow and underflow by saturation (max value = 2^15, min value = - 2^15)
  * @note   Subraction is a particular case of this function
  * @param  n1: Q15-formated first value
  * @param  n2: Q15-formated second value
  * @retval Q15-formated value that represents the addition of n1 and n2
  */
inline q15_t q15_sum(q15_t n1, q15_t n2){
	q31_t	aux;

	aux = (q31_t)n1 + (q31_t)n2;

	if(aux > 0x7FFF)
		aux = 0x7FFF;
	else if(aux < -0x7FFF)
		aux = -0x7FFF;

	return (q15_t)aux;
}


/**
  * @brief  Perform the multiplication of two Q15 values
  * @note   The result is a Q31 value, but the 15 LSB are discarted
  * @param  n1: Q15-formated first value
  * @param  n2: Q15-formated second value
  * @retval Q1-formated value that represents the multiplication of n1 and n2
  */
inline q15_t q15_mult(q15_t n1, q15_t n2){

	q31_t	aux;
	aux = (q31_t)n1 * (q31_t)n2;

	return aux >> 15;

}

/**
  * @brief  Perform the division of two Q15 values
  * @note   To avoid the lose of the first bits, the first value is bit-shifted 15-bits to left
  * @param  n1: Q15-formated first value
  * @param  n2: Q15-formated second value
  * @retval Q15-formated value that represents the division of n1 and n2
  */
inline q15_t q15_div(q15_t n1, q15_t n2){

	q31_t	aux;
	aux = (q31_t)n1 << 15;

	return aux / (q31_t)n2;

}


