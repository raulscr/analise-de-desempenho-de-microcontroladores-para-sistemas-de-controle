/*
 * pid.h
 *
 *  Created on: 24 de out de 2018
 *      Author: raul
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_



#define FLOAT_OP
//#define RAM_RUN
//#define TEST_WITH_DIV   2
//#define CORE1_TASK_DEF
#define CORE1_TASK_DEF_2
//#define ADC1_READ
#define LEDC_PWM_WRITE
#define EXCLUDE_PERIPH_OP
//#define EXCLUDE_CALC_OP




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

#include "driver/adc.h"


#include "freertos/xtensa_api.h"
#include "rom/ets_sys.h"

#if defined(CORE1_TASK_DEF) || defined(CORE1_TASK_DEF_2)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "lwip/sockets.h"

void core1_task(void*);
#endif


#define FREQ_TIM		10
#define PWM_FREQ		500
#define ADC_RANGE		4095

#ifdef LEDC_PWM_WRITE
#define DUTY_RES		4095
#else
#define DUTY_RES		1000000/PWM_FREQ
#endif


#define RAM_ATTRIBUTE	IRAM_ATTR



#define SET_TEST_PIN		REG_SET_BIT(GPIO_OUT_W1TS_REG, BIT4);

#define RESET_TEST_PIN		REG_SET_BIT(GPIO_OUT_W1TC_REG, BIT4);

#define SET_TEST_PIN_2		REG_SET_BIT(GPIO_OUT_W1TS_REG, BIT5);

#define RESET_TEST_PIN_2        REG_SET_BIT(GPIO_OUT_W1TC_REG, BIT5);



#define RAM_CPY(FUNC_RAM, FUNC, ALLOC)	({	\
						memcpy((void *)ALLOC, (void *)FUNC, sizeof(ALLOC));	\
						FUNC_RAM = (pid_func_type)ALLOC;			\
					})


#define RESET_TIMER_FLAGS		({	\
						REG_WRITE(TIMG_T0UPDATE_REG(0), 1);\
						REG_SET_BIT(TIMG_INT_CLR_TIMERS_REG(0), TIMG_T0_INT_CLR);\
						REG_SET_BIT(TIMG_T0CONFIG_REG(0), TIMG_T0_ALARM_EN);\
					})
#ifdef ADC1_READ
#define PID_PERFORM_READ(__INPUT__)	({ 	\
						REG_CLR_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_SAR);\
						REG_SET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_SAR);\
						while (REG_GET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_DONE_SAR) == 0);\
						__INPUT__ = (uint16_t)REG_GET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_DATA_SAR);\
						REG_CLR_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_SAR);\
					})
#elif defined(CORE1_TASK_DEF)
#error "Can't perform read on adc2 while using wireless"
#else
#define PID_PERFORM_READ(__INPUT__)	({ 	\
						REG_CLR_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_SAR);\
						REG_SET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_SAR);\
						while(REG_GET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_DONE_SAR) == 0);\
						__INPUT__ = (uint16_t)REG_GET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_DATA_SAR);\
						REG_CLR_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_SAR);\
					})
#endif
#ifdef LEDC_PWM_WRITE
#define PID_PERFORM_WRITE(__OUTPUT__)	({	\
						REG_WRITE(LEDC_HSCH0_DUTY_REG, __OUTPUT__ << 4);\
						REG_SET_BIT(LEDC_HSCH0_CONF1_REG, LEDC_DUTY_START_HSCH0);\
					})

#else
#define PID_PERFORM_WRITE(__OUTPUT__)	({	\
						REG_WRITE(MCPWM_GEN0_TSTMP_A_REG(0), __OUTPUT__);\
						REG_SET_BIT(MCPWM_GEN0_STMP_CFG_REG(0), BIT(1) << MCPWM_GEN0_A_UPMETHOD_S);\
					})
#endif

#endif
