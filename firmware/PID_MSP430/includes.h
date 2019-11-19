/*
 * includes.h
 *
 *  Created on: 12 de mar de 2019
 *      Author: Raul
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_


#include <stdint.h>
#include <string.h>
#include <msp430.h>
#include "q7lib.h"
#include "q15lib.h"
#include "q31lib.h"

#define     FLOAT_OP
//#define     RAM_ATRRIBUTE
#define   TEST_WITH_DIV     5

#define ADC_RANGE   1024
#define DUTY_RES    255
//#define PWM_FREQ    2000
#define TIM_FREQ    500


#define SET_TEST_PIN            ({                  \
                                    P1OUT |= BIT4;  \
                                })

#define RESET_TEST_PIN          ({               \
                                    P1OUT &= ~BIT4; \
                                })


#define SET_TEST_PIN_2          ({                  \
                                    P1OUT |= BIT5;  \
                                })

#define RESET_TEST_PIN_2        ({                  \
                                    P1OUT &= ~BIT5; \
                                })

#define RESET_TIMER_FLAGS       ({                     \
                                    TA0CTL &= ~TAIFG;\
                                })


#ifdef Q7_OP
#define PID_PERFORM_READ(__INPUT__)     ({                                  \
                                            ADC10CTL0 |= ADC10SC + ENC;     \
                                            while(ADC10CTL1 & ADC10BUSY);   \
                                            __INPUT__ = (ADC10MEM >> 3);      \
                                        })
#else
#define PID_PERFORM_READ(__INPUT__)     ({                                  \
                                            ADC10CTL0 |= ADC10SC + ENC;     \
                                            while(ADC10CTL1 & ADC10BUSY);   \
                                            __INPUT__ = ADC10MEM;           \
                                        })
#endif

#define PID_PERFORM_WRITE(__OUTPUT__)   ({                              \
                                                TA1CCR1 = __OUTPUT__;   \
                                        })


#endif /* INCLUDES_H_ */
