/**
 ****************************************************************************************************
 * @file        btim.c
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

#include "./BSP/TIMER/btim.h"
#include "./BSP/LED/led.h"
#include "lvgl.h"

/* ������ʱ����� */
TIM_HandleTypeDef g_timx_handle = {0};

/**
 * @brief   ��ʼ��������ʱ��
 * @param   arr: �Զ���װ��ֵ
 * @param   psc: Ԥ��Ƶϵ��
 * @retval  ��
 */
void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
    g_timx_handle.Instance = BTIM_TIMX_INT;
    g_timx_handle.Init.Prescaler = psc;
    g_timx_handle.Init.Period = arr;
    HAL_TIM_Base_Init(&g_timx_handle);
    HAL_TIM_Base_Start_IT(&g_timx_handle);
}

/**
 * @brief   HAL��TIM��ʼ��MSP����
 * @param   ��
 * @retval  ��
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX_INT)
    {
        /* ʹ�ܻ�����ʱ��ʱ�� */
        BTIM_TIMX_INT_CLK_ENABLE();
        
        /* �����ж����ȼ���ʹ���ж� */
        HAL_NVIC_SetPriority(BTIM_TIMX_INT_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(BTIM_TIMX_INT_IRQn);
    }
}

/**
 * @brief   ������ʱ���жϷ�����
 * @param   ��
 * @retval  ��
 */
void BTIM_TIMX_INT_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_handle);
}

/**
 * @brief   HAL�������ʱ����ʱ�жϻص�����
 * @param   ��
 * @retval  ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == BTIM_TIMX_INT)
    {
        lv_tick_inc(1);                 /*lvgl��1ms����*/
    }
}
