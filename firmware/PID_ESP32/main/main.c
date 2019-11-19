#include <stdio.h>
#include "includes.h"
#include "pid_lib/pidlib.h"
#include "pid_lib/qn_lib/q7lib.h"
#include "pid_lib/qn_lib/q15lib.h"
#include "pid_lib/qn_lib/q31lib.h"


#if defined(Q7_OP)
#define PARSE_OP(NUM) double_to_q7(NUM)
#elif defined(Q15_OP)
#define PARSE_OP(NUM) double_to_q15(NUM)
#elif defined(Q31_OP)
#define PARSE_OP(NUM) double_to_q31(NUM)
#elif defined(INT_OP)
#define PARSE_OP(NUM) (int)(NUM * 32)
#else
#define PARSE_OP(NUM) NUM
#endif

pid_type pid;



void IRAM_ATTR TIMER0G0_ISR(void* arg){
	pidInterruptRoutine(&pid);
}

static void configGPIO(){
	REG_WRITE(GPIO_ENABLE_REG, BIT4 | BIT5);
	REG_SET_BIT(GPIO_OUT_W1TC_REG, BIT4 | BIT5);
}

static void configADC(){

#ifdef ADC1_READ
	//Configure ADC1 (Channel 6 -> GPIO 34)

	// disable HALL sensor
	REG_CLR_BIT(RTC_IO_HALL_SENS_REG, RTC_IO_XPD_HALL);


	// set ADC-CTRL-RTC controller
	REG_SET_BIT(SENS_SAR_START_FORCE_REG, 0xF);
	// 11dB atten all pads
	REG_WRITE(SENS_SAR_ATTEN1_REG, 0xFFFFFFFF);

	// set channel in SAR_MEAS_START1
	REG_SET_BIT(SENS_SAR_MEAS_START1_REG, BIT(6 + SENS_SAR1_EN_PAD_S));

	REG_SET_BIT(SENS_SAR_MEAS_START1_REG, SENS_MEAS1_START_FORCE);
	REG_SET_BIT(SENS_SAR_MEAS_START1_REG, SENS_SAR1_EN_PAD_FORCE);
	REG_SET_BIT(SENS_SAR_TOUCH_CTRL1_REG, SENS_XPD_HALL_FORCE);
	REG_SET_BIT(SENS_SAR_TOUCH_CTRL1_REG, SENS_HALL_PHASE_FORCE);
	REG_CLR_BIT(SENS_SAR_READ_CTRL_REG, SENS_SAR1_DIG_FORCE);

	REG_CLR_BIT(SENS_SAR_READ_CTRL_REG, SENS_SAR1_CLK_DIV_M);

	//force power up
	REG_SET_BIT(SENS_SAR_MEAS_WAIT2_REG, SENS_FORCE_XPD_SAR_PU);

	// disable all another fuck 
	REG_CLR_BIT(SENS_SAR_MEAS_CTRL_REG, SENS_AMP_RST_FB_FSM_M);
	REG_CLR_BIT(SENS_SAR_MEAS_CTRL_REG, SENS_AMP_SHORT_REF_FSM_M);
	REG_CLR_BIT(SENS_SAR_MEAS_CTRL_REG, SENS_AMP_SHORT_REF_GND_FSM_M);

	REG_SET_BIT(SENS_SAR_MEAS_WAIT1_REG, SENS_SAR_AMP_WAIT1_M);
	REG_SET_BIT(SENS_SAR_MEAS_WAIT1_REG, SENS_SAR_AMP_WAIT2_M);
	REG_SET_BIT(SENS_SAR_MEAS_WAIT2_REG, SENS_SAR_AMP_WAIT2_M);

	//inverse (why the hell the input is getting iverted??!))
	REG_SET_BIT(SENS_SAR_READ_CTRL_REG, SENS_SAR1_DATA_INV);

#else
	//Configure ADC2 (Channel 6 -> GPIO 14)

	// disable HALL sensor
	REG_CLR_BIT(RTC_IO_HALL_SENS_REG, RTC_IO_XPD_HALL);

	//force power up
	REG_SET_BIT(SENS_SAR_MEAS_WAIT2_REG, SENS_FORCE_XPD_SAR_PU);

	// disable all another fuck 
	REG_CLR_BIT(SENS_SAR_MEAS_CTRL_REG, SENS_AMP_RST_FB_FSM_M);
	REG_CLR_BIT(SENS_SAR_MEAS_CTRL_REG, SENS_AMP_SHORT_REF_FSM_M);
	REG_CLR_BIT(SENS_SAR_MEAS_CTRL_REG, SENS_AMP_SHORT_REF_GND_FSM_M);
	REG_SET_BIT(SENS_SAR_TOUCH_CTRL1_REG, SENS_XPD_HALL_FORCE);
	REG_SET_BIT(SENS_SAR_TOUCH_CTRL1_REG, SENS_HALL_PHASE_FORCE);

	//REG_CLR_BIT(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_CLK_DIV_M);

	// set ADC-CTRL-RTC controller
	REG_SET_BIT(SENS_SAR_START_FORCE_REG, 0x3 << SENS_SAR2_BIT_WIDTH_S);
	REG_CLR_BIT(SENS_SAR_START_FORCE_REG, SENS_SAR2_PWDET_CCT_M);
	REG_SET_BIT(SENS_SAR_START_FORCE_REG, SENS_SAR2_EN_TEST);
	REG_SET_BIT(SENS_SAR_START_FORCE_REG, BIT(2) << SENS_SAR2_PWDET_CCT_S);
	REG_SET_BIT(SYSCON_SARADC_CTRL_REG, SYSCON_SARADC_SAR2_MUX);
	REG_CLR_BIT(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_DIG_FORCE);
	//invert (why the hell the input is getting iverted??!))
	REG_SET_BIT(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_DATA_INV);
	REG_SET_BIT(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_SAMPLE_BIT_M);

	// set channel in SAR_MEAS_START1
	REG_SET_BIT(SENS_SAR_MEAS_START2_REG, SENS_SAR2_EN_PAD_FORCE);
	REG_SET_BIT(SENS_SAR_MEAS_START2_REG, 7 << SENS_SAR2_EN_PAD_S);
	REG_SET_BIT(SENS_SAR_MEAS_START2_REG, SENS_MEAS2_START_FORCE);

	// 11dB atten all pads
	REG_WRITE(SENS_SAR_ATTEN2_REG, 0xFFFFFFFF);
#endif

}



#ifdef LEDC_PWM_WRITE
static void configPWM(){

	DPORT_SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_LEDC_CLK_EN);	// enable DPORT peripheral
	DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_LEDC_RST);
	REG_SET_BIT(LEDC_HSTIMER0_CONF_REG, (APB_CLK_FREQ / 16 / PWM_FREQ) << LEDC_DIV_NUM_HSTIMER0_S);	// divisor
	REG_SET_BIT(LEDC_HSTIMER0_CONF_REG, 12 << LEDC_HSTIMER0_LIM_S);		// duty resolution
	REG_SET_BIT(LEDC_HSTIMER0_CONF_REG, LEDC_TICK_SEL_HSTIMER0);		// APB clk
	REG_SET_BIT(LEDC_HSTIMER0_CONF_REG, LEDC_HSTIMER0_RST);			// reset timer
	REG_CLR_BIT(LEDC_HSTIMER0_CONF_REG, LEDC_HSTIMER0_RST);	
	REG_WRITE(LEDC_HSCH0_DUTY_REG, 0);					// duty = 0 
	REG_WRITE(LEDC_HSCH0_HPOINT_REG, 0);					// hpoint
	REG_SET_BIT(LEDC_HSCH0_CONF0_REG, LEDC_SIG_OUT_EN_HSCH0);		// output enable
	REG_SET_BIT(LEDC_HSCH0_CONF0_REG, 0x0 << LEDC_TIMER_SEL_HSCH0_S);	// hs-timer0


	REG_CLR_BIT(LEDC_HSCH0_CONF1_REG, LEDC_DUTY_SCALE_HSCH0_M);		// no scale
	REG_SET_BIT(LEDC_HSCH0_CONF1_REG, BIT(LEDC_DUTY_CYCLE_HSCH0_S));		// set cycle
	REG_SET_BIT(LEDC_HSCH0_CONF1_REG, BIT(LEDC_DUTY_NUM_HSCH0_S));		// set num of cycles
	REG_SET_BIT(LEDC_HSCH0_CONF1_REG, LEDC_DUTY_INC_HSCH0);			// set increase
	REG_SET_BIT(LEDC_HSCH0_CONF1_REG, LEDC_DUTY_START_HSCH0);		// start timer

	REG_SET_BIT(GPIO_ENABLE_REG, BIT18);					// enable output GPIO18
	REG_SET_BIT(GPIO_FUNC18_OUT_SEL_CFG_REG, LEDC_HS_SIG_OUT0_IDX);
	REG_SET_BIT(GPIO_FUNC18_OUT_SEL_CFG_REG, GPIO_FUNC0_OEN_SEL);
	REG_SET_BIT(IO_MUX_GPIO18_REG, FUNC_GPIO18_GPIO18);					

}
#else
static void configPWM(){

	DPORT_SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_PWM0_CLK_EN);	// enable DPORT peripheral
	DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_PWM0_RST);

	REG_SET_BIT(GPIO_ENABLE_REG, BIT18);					// enable output GPIO18
	REG_SET_BIT(GPIO_FUNC18_OUT_SEL_CFG_REG, PWM0_OUT0A_IDX);
	REG_SET_BIT(GPIO_FUNC18_OUT_SEL_CFG_REG, GPIO_FUNC0_OEN_SEL);
	REG_SET_BIT(IO_MUX_GPIO18_REG, FUNC_GPIO18_GPIO18);


	uint32_t periodo = APB_CLK_FREQ / 8 / PWM_FREQ;

	REG_SET_BIT(MCPWM_CLK_CFG_REG(0), 15);						// prescaler
	REG_SET_BIT(MCPWM_TIMER0_CFG0_REG(0), 0x0 << MCPWM_TIMER0_PRESCALE_S);		// prescaler again	
	REG_SET_BIT(MCPWM_TIMER0_CFG0_REG(0), periodo << MCPWM_TIMER0_PERIOD_S);	// Fpwm = Fclk/count/(Presc + 1) -> 2k = 1M/count/(1)
	REG_SET_BIT(MCPWM_TIMER0_CFG0_REG(0), 0x0 << MCPWM_TIMER0_PERIOD_UPMETHOD_S);	// update when the count turn to 0
	REG_SET_BIT(MCPWM_TIMER0_CFG1_REG(0), 0x1 << MCPWM_TIMER0_MOD_S);		// up mode
	REG_SET_BIT(MCPWM_GEN0_STMP_CFG_REG(0), BIT(1) << MCPWM_GEN0_A_UPMETHOD_S);	// TEZ
	REG_SET_BIT(MCPWM_GEN0_STMP_CFG_REG(0), BIT(1) << MCPWM_GEN0_B_UPMETHOD_S);	// TEZ
	REG_SET_BIT(MCPWM_GEN0_TSTMP_A_REG(0), 0);					// PWMA
	REG_SET_BIT(MCPWM_GEN0_TSTMP_B_REG(0), 0);					// PWMB
	REG_SET_BIT(MCPWM_GEN0_A_REG(0), 0x2 << MCPWM_GEN0_A_UTEZ_S);			
	REG_SET_BIT(MCPWM_GEN0_A_REG(0), 0x1 << MCPWM_GEN0_A_UTEA_S);			
	REG_SET_BIT(MCPWM_GEN0_A_REG(0), 0x0 << MCPWM_GEN0_A_UTEP_S);		
	REG_SET_BIT(MCPWM_GEN0_B_REG(0), 0x2 << MCPWM_GEN0_B_UTEZ_S);			
	REG_SET_BIT(MCPWM_GEN0_B_REG(0), 0x1 << MCPWM_GEN0_B_UTEA_S);			
	REG_SET_BIT(MCPWM_GEN0_B_REG(0), 0x0 << MCPWM_GEN0_B_UTEP_S);	
	REG_SET_BIT(MCPWM_TIMER0_CFG1_REG(0), 0x2 << MCPWM_TIMER0_START_S);		// start and run
	REG_SET_BIT(MCPWM_OPERATOR_TIMERSEL_REG(0), 0x0 << MCPWM_OPERATOR0_TIMERSEL_S);	// timer select for operators
	REG_SET_BIT(MCPWM_OPERATOR_TIMERSEL_REG(0), 0x1 << MCPWM_OPERATOR1_TIMERSEL_S);
	REG_SET_BIT(MCPWM_OPERATOR_TIMERSEL_REG(0), 0x2 << MCPWM_OPERATOR2_TIMERSEL_S);
	REG_SET_BIT(MCPWM_UPDATE_CFG_REG(0), MCPWM_OP2_UP_EN);				// global enable of update 	
	REG_SET_BIT(MCPWM_UPDATE_CFG_REG(0), MCPWM_GLOBAL_FORCE_UP);			// forced update of active registers in PWM operator 0
	REG_CLR_BIT(MCPWM_UPDATE_CFG_REG(0), MCPWM_GLOBAL_FORCE_UP);
	
}
#endif

static void configTIM(){

	DPORT_SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_TIMERGROUP_CLK_EN);
	DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_TIMERGROUP_RST);

	REG_SET_BIT(TIMG_T0CONFIG_REG(0), TIMG_T0_AUTORELOAD);
	REG_CLR_BIT(TIMG_T0CONFIG_REG(0), TIMG_T0_EN);
	REG_SET_BIT(TIMG_T0CONFIG_REG(0), TIMG_T0_INCREASE);
	REG_SET_BIT(TIMG_T0CONFIG_REG(0), 16 << TIMG_T0_DIVIDER_S);
	REG_SET_BIT(TIMG_T0CONFIG_REG(0), TIMG_T0_ALARM_EN);
	REG_SET_BIT(TIMG_T0CONFIG_REG(0), TIMG_T0_LEVEL_INT_EN);
	REG_CLR_BIT(TIMG_T0CONFIG_REG(0), TIMG_T0_EDGE_INT_EN);

	REG_SET_BIT(TIMG_T0LO_REG(0), 0);
	REG_SET_BIT(TIMG_T0HI_REG(0), 0);

	uint64_t alarm_val = (uint64_t)APB_CLK_FREQ / 16 / FREQ_TIM;
	REG_WRITE(TIMG_T0ALARMHI_REG(0), (uint32_t)(alarm_val >> 32));
	REG_WRITE(TIMG_T0ALARMLO_REG(0), (uint32_t)alarm_val);

/*

  * @brief  Attach an CPU interrupt to a hardware source.
  *         We have 4 steps to use an interrupt:
  *         1.Attach hardware interrupt source to CPU.  intr_matrix_set(0, ETS_WIFI_MAC_INTR_SOURCE, ETS_WMAC_INUM);
  *         2.Set interrupt handler.                    xt_set_interrupt_handler(ETS_WMAC_INUM, func, NULL);
  *         3.Enable interrupt for CPU.                 xt_ints_on(1 << ETS_WMAC_INUM);
  *         4.Enable interrupt in the module.

*/

	intr_matrix_set(0, ETS_TG0_T0_LEVEL_INTR_SOURCE, 13);
	xt_set_interrupt_handler(13, TIMER0G0_ISR, NULL);
	xt_ints_on(BIT(13));
	DPORT_REG_SET_BIT(DPORT_APP_TG_T0_LEVEL_INT_MAP_REG, 13);



	REG_SET_BIT(TIMG_T0CONFIG_REG(0), TIMG_T0_EN);

}


void core1_task_2(void *arg){
	while(1){
		printf("%d, %d\n", pid.input, pid.output);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void app_main(){
	#ifdef CORE1_TASK_DEF
	xTaskCreatePinnedToCore(&core1_task, "core1_task", 1024 * 8, (void*)&pid, 5, NULL, 1);
	#else
	xTaskCreatePinnedToCore(&core1_task_2, "core1_task", 1024 * 8, (void*)NULL, 5, NULL, 1);
	#endif
	new_PID(&pid, PARSE_OP(0.05), PARSE_OP(0.03), PARSE_OP(0.02), ADC_RANGE * 0.26, DUTY_RES * 0.01, DUTY_RES * 0.99);

	configGPIO();
	configPWM();
	configADC();
	configTIM();

	while(1){
		pidLoopRoutine(&pid);
	}
}
