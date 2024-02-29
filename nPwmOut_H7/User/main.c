/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)+����Ԫ
 * @version     V1.0
 * @date        2024-02-26
 * @brief       ���ڸ߼���ʱ�����ָ������PWMʵ����в��������������
 * @Function		1��ͨ����ͬ��������ָ��������PWM��	
					2��ͨ����EC11��ת����������������������б������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� ������ H750������
 *	��������Ӧ�ܽţ�PA8��PA2��PA3
 *	��ת��������������ܽţ�PB8\PB9 PC5\PC6 PG13\PG14
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIMER/atim.h"
#include "./BSP/SpinEncoder/spinencoder.h"

extern TIM_HandleTypeDef g_timx_npwm_handle;											/* ��ʱ��1���ͨ����� */
extern TIM_HandleTypeDef g_tim15_npwm_handle ;											/* ��ʱ��15���ͨ����� */


int main(void)
{
    uint8_t key;
    uint8_t t = 0;
    
    sys_cache_enable();                             /* ʹ��L1-Cache */
    HAL_Init();                                     /* ��ʼ��HAL�� */
    sys_stm32_clock_init(192, 5, 2, 4);             /* ����ʱ�ӣ�480MHz */
    delay_init(480);                                /* ��ʼ����ʱ */
    usart_init(115200);                             /* ��ʼ������ */
	exti_init();									/* ��ʼ���ⲿ�ж� */
    led_init();                                     /* ��ʼ��LED */
    key_init();                                     /* ��ʼ������ */
    atim_timx_chy_npwm_init(5000 - 1, 24000 - 1);   /* ��ʼ���߼���ʱ�����ָ������PWM��PWMƵ��Ϊ2Hz */
    while (1)
    {
		/* 
			����3���������ƶ�ʱ��3��ͨ�����ָ������PWM�� 
		*/
		
        key = key_scan(0);
        if (key == KEY0_PRES)
        {
						HAL_TIM_PWM_Start(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
						HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
						HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
						atim_timx_chy_npwm_set(2);              /* PA8 ���5��PWM */
        }
				else if( key == KEY1_PRES)
				{
						HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);	
						HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
						HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
						atim_tim15_chy_npwm_set(3);				/* PA2 ���5��PWM ����ԭ�ӿ���������������������ƽ��Ӱ�� */                                                                                                                                
				}
				else if( key == KEY2_PRES )
				{
						HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
						HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
						HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
						atim_tim15_chy_npwm_set(4);				/* PA3 ���5��PWM */
				}
				/* ��ʾ�������������� */
						if (++t == 20)
						{
								t = 0;
								LED0_TOGGLE();
						}
						
						delay_ms(200);
				}
}
