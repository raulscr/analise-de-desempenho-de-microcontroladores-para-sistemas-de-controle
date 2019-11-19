
#include "types_qn.h"
#include "q15lib.h"



//	q15 (signed) function impl.


q15_t double_to_q15(double n){
	return (q15_t)(n * 0x8000);			//	15bit shift (2^15 = 0x8000)
}

double q15_to_double(q15_t n){
	return (double)(((double long)n) / 0x8000);
}

inline q15_t q15_sum(q15_t n1, q15_t n2){
	q31_t	aux;

	aux = (q31_t)n1 + (q31_t)n2;

	if(aux > 0x7FFF)
		aux = 0x7FFF;
	else if(aux < -0x7FFF)
		aux = -0x7FFF;

	return (q15_t)aux;
}

inline q15_t q15_mult(q15_t n1, q15_t n2){

	q31_t	aux;
	aux = (q31_t)n1 * (q31_t)n2;

	return aux >> 15;

}

inline q15_t q15_div(q15_t n1, q15_t n2){

	q31_t	aux;
	aux = (q31_t)n1 << 15;

	return aux / (q31_t)n2;

}


