/**
 ****************************************************************************************************
 * @file        atim.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       �߼���ʱ����������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� ������ H750������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __ATIM_H
#define __ATIM_H

#include "./SYSTEM/sys/sys.h"

/* �߼���ʱ��1���� */
#define ATIM_TIMX_NPWM                          TIM1
#define ATIM_TIMX_NPWM_IRQn                     TIM1_UP_IRQn
#define ATIM_TIMX_NPWM_IRQHandler               TIM1_UP_IRQHandler
#define ATIM_TIMX_NPWM_CLK_ENABLE()             do { __HAL_RCC_TIM1_CLK_ENABLE(); } while (0)
#define ATIM_TIMX_NPWM_CHY                      TIM_CHANNEL_1
#define ATIM_TIMX_NPWM_CHY_GPIO_PORT            GPIOA
#define ATIM_TIMX_NPWM_CHY_GPIO_PIN             GPIO_PIN_8
#define ATIM_TIMX_NPWM_CHY_GPIO_AF              GPIO_AF1_TIM1	/* ����õ�TIMER1��ͨ��1 */
#define ATIM_TIMX_NPWM_CHY_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)

/* ͨ�ö�ʱ��15���� */
#define ATIM_TIM15_NPWM                         TIM15
#define ATIM_TIM15_NPWM_IRQn                    TIM15_IRQn
#define ATIM_TIM15_NPWM_IRQHandler               TIM15_IRQHandler
#define ATIM_TIM15_NPWM_CLK_ENABLE()             do { __HAL_RCC_TIM15_CLK_ENABLE(); } while (0)
#define ATIM_TIM15_NPWM_CH1                     TIM_CHANNEL_1
#define ATIM_TIM15_NPWM_CH2                     TIM_CHANNEL_2
#define ATIM_TIM15_NPWM_CHY_GPIO_PORT           GPIOA
#define ATIM_TIM15_NPWM_CHY_GPIO_PIN1           GPIO_PIN_2
#define ATIM_TIM15_NPWM_CHY_GPIO_PIN2           GPIO_PIN_3
#define ATIM_TIM15_NPWM_CHY_GPIO_AF             GPIO_AF4_TIM15	/* ����õ�TIMER15��ͨ��1��ͨ��2 */
#define ATIM_TIM15_NPWM_CHY_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)

/* �����л���־ */
#define X_Axis	1
#define Y_Axis	2
#define	Z_Axis	3

//#define ATIM_TIMX_COMP                          TIM8
//#define ATIM_TIMX_COMP_CLK_ENABLE()             do { __HAL_RCC_TIM8_CLK_ENABLE(); } while (0)
//#define ATIM_TIMX_COMP_CH1_GPIO_PORT            GPIOC
//#define ATIM_TIMX_COMP_CH1_GPIO_PIN             GPIO_PIN_6
//#define ATIM_TIMX_COMP_CH1_GPIO_AF              GPIO_AF3_TIM8
//#define ATIM_TIMX_COMP_CH1_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)
//#define ATIM_TIMX_COMP_CH2_GPIO_PORT            GPIOC
//#define ATIM_TIMX_COMP_CH2_GPIO_PIN             GPIO_PIN_7
//#define ATIM_TIMX_COMP_CH2_GPIO_AF              GPIO_AF3_TIM8
//#define ATIM_TIMX_COMP_CH2_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)
//#define ATIM_TIMX_COMP_CH3_GPIO_PORT            GPIOC
//#define ATIM_TIMX_COMP_CH3_GPIO_PIN             GPIO_PIN_8
//#define ATIM_TIMX_COMP_CH3_GPIO_AF              GPIO_AF3_TIM8
//#define ATIM_TIMX_COMP_CH3_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)
//#define ATIM_TIMX_COMP_CH4_GPIO_PORT            GPIOC
//#define ATIM_TIMX_COMP_CH4_GPIO_PIN             GPIO_PIN_9
//#define ATIM_TIMX_COMP_CH4_GPIO_AF              GPIO_AF3_TIM8
//#define ATIM_TIMX_COMP_CH4_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)

//#define ATIM_TIMX_CPLM                          TIM1
//#define ATIM_TIMX_CPLM_CLK_ENABLE()             do { __HAL_RCC_TIM1_CLK_ENABLE(); } while (0)
//#define ATIM_TIMX_CPLM_CHY                      TIM_CHANNEL_1
//#define ATIM_TIMX_CPLM_CHY_GPIO_PORT            GPIOA
//#define ATIM_TIMX_CPLM_CHY_GPIO_PIN             GPIO_PIN_8
//#define ATIM_TIMX_CPLM_CHY_GPIO_AF              GPIO_AF1_TIM1
//#define ATIM_TIMX_CPLM_CHY_GPIO_CLK_ENABLE()    do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)
//#define ATIM_TIMX_CPLM_CHYN_GPIO_PORT           GPIOA
//#define ATIM_TIMX_CPLM_CHYN_GPIO_PIN            GPIO_PIN_7
//#define ATIM_TIMX_CPLM_CHYN_GPIO_AF             GPIO_AF1_TIM1
//#define ATIM_TIMX_CPLM_CHYN_GPIO_CLK_ENABLE()   do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PORT           GPIOA
//#define ATIM_TIMX_CPLM_BKIN_GPIO_PIN            GPIO_PIN_6
//#define ATIM_TIMX_CPLM_BKIN_GPIO_AF             GPIO_AF1_TIM1
//#define ATIM_TIMX_CPLM_BKIN_GPIO_CLK_ENABLE()   do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while (0)

//#define ATIM_TIMX_PWMIN                         TIM8
//#define ATIM_TIMX_PWMIN_IRQn                    TIM8_CC_IRQn
//#define ATIM_TIMX_PWMIN_IRQHandler              TIM8_CC_IRQHandler
//#define ATIM_TIMX_PWMIN_CLK_ENABLE()            do { __HAL_RCC_TIM8_CLK_ENABLE(); } while (0)
//#define ATIM_TIMX_PWMIN_CHY                     TIM_CHANNEL_1
//#define ATIM_TIMX_PWMIN_CHY_GPIO_PORT           GPIOC
//#define ATIM_TIMX_PWMIN_CHY_GPIO_PIN            GPIO_PIN_6
//#define ATIM_TIMX_PWMIN_CHY_GPIO_AF             GPIO_AF3_TIM8
//#define ATIM_TIMX_PWMIN_CHY_GPIO_CLK_ENABLE()   do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)

/* �������� */
void atim_timx_chy_npwm_init(uint16_t arr, uint16_t psc);   /* ��ʼ���߼���ʱ�����ָ������PWM */
void atim_timx_chy_npwm_set(uint32_t npwm);                 /* ���ø߼���ʱ��1���ָ������PWM */
void atim_tim15_chy_npwm_set(uint32_t npwm);								/* ����ͨ�ö�ʱ��15���ָ������PWM */
//void atim_timx_comp_init(uint16_t arr, uint16_t psc);       /* ��ʼ���߼���ʱ������Ƚ� */
//void atim_timx_cplm_init(uint16_t arr, uint16_t psc);       /* ��ʼ���߼���ʱ������������������� */
//void atim_timx_cplm_set(uint16_t ccr, uint8_t dtg);         /* ���ø߼���ʱ������������������� */
//void atim_timx_pwmin_chy_init(uint16_t psc);                /* ��ʼ���߼���ʱ��PWM���� */

#endif
