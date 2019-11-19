#include "types_qn.h"
#include "q31lib.h"


//  q31 (signed) function impl.


q31_t double_to_q31(double n){
    return (q31_t)(n * 0x80000000);         //  31bit shift (2^31 = 0x80000000)
}

double q31_to_double(q31_t n){
    return (double)(((double long)n) / 0x80000000);
}

inline q31_t q31_sum(q31_t n1, q31_t n2){
    q63_t   aux;

    aux = (q63_t)n1 + (q63_t)n2;

    if(aux > 0x7FFFFFFF)
        aux = 0x7FFFFFFF;
    else if(aux < -0x7FFFFFFF)
        aux = -0x7FFFFFFF;

    return (q31_t)aux;
}

inline q31_t q31_mult(q31_t n1, q31_t n2){

    q63_t   aux;
    aux = (q63_t)n1 * (q63_t)n2;

    return aux >> 31;

}

inline q31_t q31_div(q31_t n1, q31_t n2){

    q63_t   aux;
    aux = (q63_t)n1 << 31;

    return aux / (q63_t)n2;

}
