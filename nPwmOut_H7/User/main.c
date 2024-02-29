/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)+张启元
 * @version     V1.0
 * @date        2024-02-26
 * @brief       基于高级定时器输出指定个数PWM实验进行步进电机驱动控制
 * @Function		1、通过不同按键产生指定个数的PWM波	
					2、通过对EC11旋转编码器产生的两相脉冲进行辨相计数
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 北极星 H750开发板
 *	输出脉冲对应管脚：PA8、PA2、PA3
 *	旋转编码器输入脉冲管脚：PB8\PB9 PC5\PC6 PG13\PG14
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIMER/atim.h"
#include "./BSP/SpinEncoder/spinencoder.h"

extern TIM_HandleTypeDef g_timx_npwm_handle;											/* 定时器1输出通道句柄 */
extern TIM_HandleTypeDef g_tim15_npwm_handle ;											/* 定时器15输出通道句柄 */


int main(void)
{
    uint8_t key;
    uint8_t t = 0;
    
    sys_cache_enable();                             /* 使能L1-Cache */
    HAL_Init();                                     /* 初始化HAL库 */
    sys_stm32_clock_init(192, 5, 2, 4);             /* 配置时钟，480MHz */
    delay_init(480);                                /* 初始化延时 */
    usart_init(115200);                             /* 初始化串口 */
	exti_init();									/* 初始化外部中断 */
    led_init();                                     /* 初始化LED */
    key_init();                                     /* 初始化按键 */
    atim_timx_chy_npwm_init(5000 - 1, 24000 - 1);   /* 初始化高级定时器输出指定个数PWM，PWM频率为2Hz */
    while (1)
    {
		/* 
			利用3个按键控制定时器3个通道输出指定个数PWM波 
		*/
		
        key = key_scan(0);
        if (key == KEY0_PRES)
        {
						HAL_TIM_PWM_Start(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
						HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
						HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
						atim_timx_chy_npwm_set(2);              /* PA8 输出5个PWM */
        }
				else if( key == KEY1_PRES)
				{
						HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);	
						HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
						HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
						atim_tim15_chy_npwm_set(3);				/* PA2 输出5个PWM 正点原子开发板上有上拉电阻对其电平有影响 */                                                                                                                                
				}
				else if( key == KEY2_PRES )
				{
						HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
						HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
						HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
						atim_tim15_chy_npwm_set(4);				/* PA3 输出5个PWM */
				}
				/* 提示主程序正在运行 */
						if (++t == 20)
						{
								t = 0;
								LED0_TOGGLE();
						}
						
						delay_ms(200);
				}
}
