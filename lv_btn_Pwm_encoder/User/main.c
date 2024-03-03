/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK) + 张启元
 * @version     V1.0
 * @date        2024-03-03
 * @brief       基于LVGL lv_btn(按钮) 实验进行开发
 * @function	利用RGBLCD（7寸）上的3个触摸按钮分别实现3路指定个数PWM输出
 *				定时器TIM1的通道1 PA8
 *				定时器TIM15的通道1 PA2
 *				定时器TIM15的通道2 PA3
 * 				X轴旋钮  A相——PB8 		B相——PB9 
 * 				Y轴旋钮  A相——PC5 		B相——PC6 
 * 				Z轴旋钮  A相——PG13 	B相——PG14 
 *
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 北极星 H750开发板
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
    sys_cache_enable();                 /* 使能L1-Cache */
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(192, 5, 2, 4); /* 配置时钟，480MHz */
    delay_init(480);                    /* 初始化延时 */
    usart_init(115200);                 /* 初始化串口 */
	exti_init();						/* 外部中断初始化 */
    led_init();                         /* 初始化LED */
    key_init();                         /* 初始化按键 */
    mpu_memory_protection();            /* 保护相关存储区域 */
    sdram_init();                       /* 初始化SDRAM */
    atim_timx_chy_npwm_init(5000 - 1, 24000 - 1);   /* 初始化高级定时器输出指定个数PWM，PWM频率为2Hz */
    /* 电阻屏坐标矫正 */
    if (key_scan(0) == KEY0_PRES)       /* KEY0按下,则执行校准程序 */
    {
        lcd_clear(WHITE);               /* 清屏 */
        tp_adjust();                    /* 屏幕校准 */
        tp_save_adjust_data();
    }
    
    lvgl_demo();                        /* 运行lvgl例程 */
}
