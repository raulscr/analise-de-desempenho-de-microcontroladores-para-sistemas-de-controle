/*
 * pid.h
 *
 *  Created on: 24 de out de 2018
 *      Author: raul
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_



#define Q15_OP
//#define RAM_RUN
#define CORE1_TASK_DEF_2
//#define TEST_WITH_DIV	2

#define ADC1_READ
//#define LEDC_PWM_WRITE
//#define EXCLUDE_PERIPH_OP
//#define EXCLUDE_CALC_OP



#define FREQ_TIM		5000
#define PWM_FREQ		5000

#define ADC_RANGE		4095

#ifdef LEDC_PWM_WRITE
#define DUTY_RES		4095
#else
#define DUTY_RES		512
#endif


#define RAM_ATTRIBUTE	IRAM_ATTR


#include <string.h>
#include "esp_types.h"
#include "soc/soc.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_sig_map.h"
#include "soc/rtc_io_reg.h"
#include "soc/ledc_reg.h"
#include "soc/dport_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/sens_reg.h"
#include "soc/syscon_reg.h"
#include "soc/timer_group_reg.h"
#include "soc/mcpwm_reg.h"

#include "freertos/xtensa_api.h"
#include "rom/ets_sys.h"



#ifdef CORE1_TASK_DEF_2
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#endif



#define SET_TEST_PIN		REG_SET_BIT(GPIO_OUT_W1TS_REG, BIT4);

#define RESET_TEST_PIN		REG_SET_BIT(GPIO_OUT_W1TC_REG, BIT4);

#define SET_TEST_PIN_2		REG_SET_BIT(GPIO_OUT_W1TS_REG, BIT5);

#define RESET_TEST_PIN_2        REG_SET_BIT(GPIO_OUT_W1TC_REG, BIT5);


/*
 * Macro to clear timer flags on ISR
 */
#define RESET_TIMER_FLAGS		({	\
						REG_WRITE(TIMG_T0UPDATE_REG(0), 1);\
						REG_SET_BIT(TIMG_INT_CLR_TIMERS_REG(0), TIMG_T0_INT_CLR);\
						REG_SET_BIT(TIMG_T0CONFIG_REG(0), TIMG_T0_ALARM_EN);\
					})

/*
 * Macro to read the ADC
 * if Q7_OP defined, the 12-bits must be ranged to 7-bits (loses 5-bits of resolution)
 * ADC2 must be used carefully, Wireless module must use it
 */
#ifdef ADC1_READ

#ifdef Q7_OP

#define PID_PERFORM_READ(__INPUT__)	({ 	\
						REG_CLR_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_SAR);\
						REG_SET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_SAR);\
						while (REG_GET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_DONE_SAR) == 0);\
						REG_CLR_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_SAR);\
						__INPUT__ = (uint16_t)(REG_GET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_DATA_SAR) >> 5);\
					})
#else

#define PID_PERFORM_READ(__INPUT__)	({ 	\
						REG_CLR_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_SAR);\
						REG_SET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_SAR);\
						while (REG_GET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_DONE_SAR) == 0);\
						REG_CLR_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_SAR);\
						__INPUT__ = (uint16_t)REG_GET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_DATA_SAR);\
					})
#endif

#else

#ifdef Q7_OP

#define PID_PERFORM_READ(__INPUT__)	({ 	\
						REG_CLR_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_SAR);\
						REG_SET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_SAR);\
						while(REG_GET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_DONE_SAR) == 0);\
						REG_CLR_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_SAR);\
						__INPUT__ = (uint16_t)REG_GET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_DATA_SAR) >> 5;\
					})
#else

#define PID_PERFORM_READ(__INPUT__)	({ 	\
						REG_CLR_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_SAR);\
						REG_SET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_SAR);\
						while(REG_GET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_DONE_SAR) == 0);\
						REG_CLR_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_SAR);\
						__INPUT__ = (uint16_t)REG_GET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_DATA_SAR);\
					})

#endif

#endif

/*
 * Macro to write at the PWM modules
 * LEDC sounds non-linear
 */
#ifdef LEDC_PWM_WRITE
#define PID_PERFORM_WRITE(__OUTPUT__)	({	\
						REG_WRITE(LEDC_HSCH0_DUTY_REG, __OUTPUT__ << 4);\
						REG_SET_BIT(LEDC_HSCH0_CONF1_REG, LEDC_DUTY_START_HSCH0);\
					})
#else
#define PID_PERFORM_WRITE(__OUTPUT__)	({	\
						REG_WRITE(MCPWM_GEN0_TSTMP_A_REG(0), __OUTPUT__ * 1.28);\
						REG_SET_BIT(MCPWM_GEN0_STMP_CFG_REG(0), BIT(1) << MCPWM_GEN0_A_UPMETHOD_S);\
					})
#endif






/**
  * Data-types definitions according to the user-sets (includes.h must be configured by user)
  */

#if defined(Q7_OP)

#include "qn_lib/q7lib.h"
typedef q31_t   pid_const_t;
#define PARSE_OP(NUM) double_to_q7(NUM)
#define SUM(NUM1, NUM2) q7_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) (q7_mult(NUM1, NUM2))
#define DIV(NUM1, NUM2) q7_div(NUM1, NUM2)

#elif defined(Q15_OP)

#include "qn_lib/q15lib.h"
typedef q31_t   pid_const_t;
#define PARSE_OP(NUM) double_to_q15(NUM)
#define SUM(NUM1, NUM2) q15_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q15_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q15_div(NUM1, NUM2)

#elif defined(Q31_OP)

#include "qn_lib/q31lib.h"
typedef q31_t   pid_const_t;
#define PARSE_OP(NUM) double_to_q31(NUM)
#define SUM(NUM1, NUM2) q31_sum(NUM1, NUM2)
#define MULT(NUM1, NUM2) q31_mult(NUM1, NUM2)
#define DIV(NUM1, NUM2) q31_div(NUM1, NUM2)

#elif defined(DOUBLE_OP)

typedef double   pid_const_t;
#define PARSE_OP(NUM) (double)(NUM)
#define SUM(NUM1, NUM2) (NUM1 + NUM2)
#define MULT(NUM1, NUM2) (NUM1 * NUM2)
#define DIV(NUM1, NUM2) (NUM1 / NUM2)

#else

typedef float   pid_const_t;
#define PARSE_OP(NUM) (float)(NUM)
#define SUM(NUM1, NUM2) (NUM1 + NUM2)
#define MULT(NUM1, NUM2) (NUM1 * NUM2)
#define DIV(NUM1, NUM2) (NUM1 / NUM2)

#endif

#endif
