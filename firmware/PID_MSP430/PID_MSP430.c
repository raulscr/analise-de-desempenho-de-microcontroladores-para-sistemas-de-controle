#include <msp430.h>
#include <string.h>
#include "portMCU.h"
#include "pidlib.h"


#ifdef RAM_RUN

typedef void (*pid_func_type)(pid_type*);
unsigned int alloc[182]/*, alloc_rti[5]*/;
pid_func_type pidLoopRoutine_ram, pidInterruptRoutine_ram;


#define RAM_CPY(FUNC_RAM, FUNC, ALLOC)  ({  \
                                            memcpy((void *)ALLOC, (void *)((int)FUNC), sizeof(ALLOC));\
                                            FUNC_RAM = (pid_func_type)((unsigned int)ALLOC);\
                                        })

#define PID_INTERRUPT_ROUTINE(__PID__) pidInterruptRoutine(__PID__)
#define PID_LOOP_ROUTINE(__PID__) pidLoopRoutine_ram(__PID__)

#else
#define PID_INTERRUPT_ROUTINE(__PID__) pidInterruptRoutine(__PID__)
#define PID_LOOP_ROUTINE(__PID__) pidLoopRoutine(__PID__)
#endif

pid_type pid;

void GPIO_config(void);
void BCS_config(void);
void TIM_config(void);
void PWM_config(void);
void ADC_config(void);

int main(void){
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    new_PID(&pid, PARSE_OP(0.12), PARSE_OP(0.95), PARSE_OP(0.007), (ADC_RANGE >> 3) / 3.45, DUTY_RES * 0.01, DUTY_RES * 0.99);
    #ifdef RAM_RUN
//    RAM_CPY(pidInterruptRoutine_ram, pidInterruptRoutine, alloc_rti);
    RAM_CPY(pidLoopRoutine_ram, pidLoopRoutine, alloc);
    #endif
    GPIO_config();
    BCS_config();
    PWM_config();
    ADC_config();
    TIM_config();
    __enable_interrupt();
    while(1)
        PID_LOOP_ROUTINE(&pid);
}

void BCS_config(void){

    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    BCSCTL2 = DIVS0 + DIVS1;                    // SMCLK = DCOCLK / 8 ~ 2 MHz
    BCSCTL3 = XCAP0 + XCAP1;

    while(BCSCTL3 & LFXT1OF);
}

void GPIO_config(void){
    P1DIR = (BIT4 | BIT5);
    P1SEL &= ~(BIT4 | BIT5);
    P1SEL2 &= ~(BIT4 | BIT5);
}

void PWM_config(void){
    P2DIR |= BIT2;                            // P1.2 and P1.3 output
    P2SEL |= BIT2;                            // P1.2 and P1.3 TA1/2 options
    P2SEL2 &= ~BIT2;                            // P1.2 and P1.3 TA1/2 options

    TA1CTL = TASSEL_2 + ID_0;                // SMCLK, div = 1 (TIMCLK = 2MHz),up mode
    TA1CCTL1 = OUTMOD_7;                            // CCR1 toggle/set
    TA1CCR0 = DUTY_RES - 1;                                  // PWM Period/2
    TA1CCR1 = 0;                                   // CCR1 PWM duty cycle - start with null
    TA1CTL |= MC_1;
}

void TIM_config(void){

    TA0CTL = TASSEL_2 + ID_0 + TAIE;     // SMCLK, div = 8 (TIMCLK = 250kHz)
    TA0CCR0 = 2000000/TIM_FREQ - 1;                       // (TACCR0 = 2MHz/20kHz - 1)
    TA0CCTL0 = CCIE;
    TA0CTL |= MC_1;
}

void ADC_config(void){
    P1DIR &= ~BIT1;

    ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON; // ADC10ON, interrupt enabled
    ADC10CTL1 = INCH_1 + SHS_0 + CONSEQ_0; // input A1
    ADC10AE0 |= BIT1; // PA.1 ADC option select
}

#pragma  vector=TIMER0_A0_VECTOR
__interrupt void TimerA1_RTI(void){
    PID_INTERRUPT_ROUTINE(&pid);
}


