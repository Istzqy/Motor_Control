/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK) + ����Ԫ
 * @version     V1.0
 * @date        2023-12-29
 * @brief       ����LVGL lv_btn(��ť) ʵ����п���
 * @function	����LCD�ϵ�3��������ť�ֱ�ʵ��3·ָ������PWM���
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� ������ H750������
 * 
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/MPU/mpu.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/SDRAM/sdram.h"
#include "./BSP/TOUCH/touch.h"
#include "lvgl_demo.h"
#include "./BSP/TIMER/atim.h"
#include "./BSP/SpinEncoder/spinencoder.h"


int main(void)
{
    sys_cache_enable();                 /* ʹ��L1-Cache */
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(192, 5, 2, 4); /* ����ʱ�ӣ�480MHz */
    delay_init(480);                    /* ��ʼ����ʱ */
    usart_init(115200);                 /* ��ʼ������ */
    led_init();                         /* ��ʼ��LED */
    key_init();                         /* ��ʼ������ */
    mpu_memory_protection();            /* ������ش洢���� */
    sdram_init();                       /* ��ʼ��SDRAM */
    atim_timx_chy_npwm_init(5000 - 1, 24000 - 1);   /* ��ʼ���߼���ʱ�����ָ������PWM��PWMƵ��Ϊ2Hz */
    /* ������������� */
    if (key_scan(0) == KEY0_PRES)       /* KEY0����,��ִ��У׼���� */
    {
        lcd_clear(WHITE);               /* ���� */
        tp_adjust();                    /* ��ĻУ׼ */
        tp_save_adjust_data();
    }
    
    lvgl_demo();                        /* ����lvgl���� */
}