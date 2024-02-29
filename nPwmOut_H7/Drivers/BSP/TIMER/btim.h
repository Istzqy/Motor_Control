/**
 ****************************************************************************************************
 * @file        btim.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       ������ʱ����������
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

#ifndef __BTIM_H
#define __BTIM_H

#include "./SYSTEM/sys/sys.h"

/* ������ʱ������ */
#define BTIM_TIMX_INT               TIM6
#define BTIM_TIMX_INT_IRQn          TIM6_DAC_IRQn
#define BTIM_TIMX_INT_IRQHandler    TIM6_DAC_IRQHandler
#define BTIM_TIMX_INT_CLK_ENABLE()  do { __HAL_RCC_TIM6_CLK_ENABLE(); } while (0)

/* �������� */
void btim_timx_int_init(uint16_t arr, uint16_t psc);    /* ��ʼ��������ʱ�� */

#endif
