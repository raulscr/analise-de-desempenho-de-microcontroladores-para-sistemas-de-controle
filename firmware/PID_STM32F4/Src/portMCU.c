#include "portMCU.h"



inline void setTestPin(){
	GPIOA->BSRR = GPIO_PIN_1;
}

inline void resetTestPin(){
	GPIOA->BSRR = (uint32_t)GPIO_PIN_1 << 16U;
}

inline void setTestPinCalc(){
	GPIOA->BSRR = GPIO_PIN_4;
}

inline void resetTestPinCalc(){
	GPIOA->BSRR = (uint32_t)GPIO_PIN_4 << 16U;
}

inline void resetTimerFlags(){

}


inline void adcRead(pid_const_t *input){

	ADC1->SR |= ADC_FLAG_STRT;
	while(!(ADC1->SR & ADC_FLAG_EOC));
	ADC1->SR &= ~(ADC_FLAG_STRT | ADC_FLAG_EOC);

	#ifdef Q7_OP
	*input = (pid_const_t)(ADC1->DR >> 5);
	#else
	*input = (pid_const_t)ADC1->DR;
	#endif

}

inline void pwmWrite(pid_const_t output){

	#ifdef Q7_OP
	TIM1->CCR3 = (uint16_t)output * 33;
	#else
	TIM1->CCR3 = (uint16_t)output;
	#endif
}


