#include "portMCU.h"



inline void setTestPin(){
	P1OUT |= BIT4;
}

inline void resetTestPin(){
	P1OUT &= ~BIT4;
}

inline void setTestPinCalc(){
	P1OUT |= BIT5;
}

inline void resetTestPinCalc(){
	P1OUT &= ~BIT5;
}

inline void resetTimerFlags(){
	TA0CTL &= ~TAIFG;
}


inline void adcRead(pid_const_t *input){

	ADC10CTL0 |= ADC10SC + ENC;
	while(ADC10CTL1 & ADC10BUSY);

	#ifdef Q7_OP
	*input = (pid_const_t)(ADC10MEM >> 3);
	#else
	*input = (pid_const_t)ADC10MEM;
	#endif

}

inline void pwmWrite(pid_const_t output){

	#ifdef Q7_OP
	TA1CCR1 = output << 1;
	#else
	TA1CCR1 = output;
	#endif
}


