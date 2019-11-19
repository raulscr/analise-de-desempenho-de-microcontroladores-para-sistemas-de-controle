#include "types_qn.h"
#include "q7lib.h"


//  Q7 (signed) function impl.


q7_t double_to_q7(double n){
    return (q7_t)(n * 0x80);            //  7bit shift (2^7 = 0x80)
}

double q7_to_double(q7_t n){
    return (double)(((double long)n) / 0x80);
}

inline q7_t q7_sum(q7_t n1, q7_t n2){
    q15_t   aux;

    aux = (q15_t)n1 + (q15_t)n2;

    if(aux > 0x7F)
        aux = 0x7F;
    else if(aux < -0x7F)
        aux = -0x7F;

    return (q7_t)aux;
}

inline q7_t q7_mult(q7_t n1, q7_t n2){

    q15_t   aux;
    aux = (q15_t)n1 * (q15_t)n2;

    return aux >> 7;

}

inline q7_t q7_div(q7_t n1, q7_t n2){

    q15_t   aux;
    aux = (q15_t)n1 << 7;

    return aux / (q15_t)n2;

}

