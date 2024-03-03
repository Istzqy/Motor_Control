/**
 ****************************************************************************************************
 * @file        lvgl_demo.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-01
 * @brief       LVGL lv_btn(按钮) 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 北极星 H750开发板
 ****************************************************************************************************
 */
 
#include "lvgl_demo.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/TIMER/atim.h"
#include "./SYSTEM/delay/delay.h"
#include "FreeRTOS.h"
#include "task.h"
#include "./SYSTEM/usart/usart.h"

#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "lvgl_demo.h"
#include "LVGL/GUI_APP/lv_mainstart.h"
#include "./BSP/SpinEncoder/spinencoder.h"
#include <stdio.h>

extern TIM_HandleTypeDef g_timx_npwm_handle;						/* 定时器1输出通道句柄 */
extern TIM_HandleTypeDef g_tim15_npwm_handle ;						/* 定时器15输出通道句柄 */
extern	volatile uint8_t X_encode_Right ;                           /* X轴右转标志 	*/
extern	volatile uint8_t X_encode_Left ;                            /* X轴左转标志 	*/
extern	volatile uint8_t Y_encode_Right ;                           /* Y轴右转标志  	*/
extern	volatile uint8_t Y_encode_Left ;                            /* Y轴左转标志  	*/
extern	volatile uint8_t Z_encode_Right ;                           /* Z轴右转标志  	*/
extern	volatile uint8_t Z_encode_Left ;                            /* Z轴左转标志  	*/
//extern	volatile int32_t X_Pulseout ;       /* X轴输出脉冲数 */
//extern	volatile int32_t Y_Pulseout ;       /* Y轴输出脉冲数 */
//extern	volatile int32_t Z_Pulseout ;       /* Z轴输出脉冲数 */
uint8_t Axis_Switch = 0 ;  		/* 开关轴向切换标志 */

/******************************************************************************************************/
/*FreeRTOS配置*/

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO     1           /* 任务优先级 */
#define START_STK_SIZE      512         /* 任务堆栈大小 */
TaskHandle_t StartTask_Handler;         /* 任务句柄 */
void start_task(void *pvParameters);    /* 任务函数 */

/* LV_DEMO_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define LV_DEMO_TASK_PRIO   3           /* 任务优先级 */
#define LV_DEMO_STK_SIZE    2048        /* 任务堆栈大小 */
TaskHandle_t LV_DEMOTask_Handler;       /* 任务句柄 */
void lv_demo_task(void *pvParameters);  /* 任务函数 */

/* LED_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define LED_TASK_PRIO       4           /* 任务优先级 */
#define LED_STK_SIZE        128         /* 任务堆栈大小 */
TaskHandle_t LEDTask_Handler;           /* 任务句柄 */
void led_task(void *pvParameters);      /* 任务函数 */

/* PWM_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define PWM_TASK_PRIO       3           /* 任务优先级 */
#define PWM_STK_SIZE        128         /* 任务堆栈大小 */
TaskHandle_t PWMTask_Handler;           /* 任务句柄 */
void pwm_task(void *pvParameters);      /* 任务函数 */

/* SpinEncoder_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define Encoder_TASK_PRIO       3           /* 任务优先级 */
#define Encoder_STK_SIZE        128         /* 任务堆栈大小 */
TaskHandle_t EncoderTask_Handler;           /* 任务句柄 */
void encoder_task(void *pvParameters);      /* 任务函数 */
/******************************************************************************************************/


void lvgl_demo(void)
{
    lv_init();                                          /* lvgl系统初始化 */
    lv_port_disp_init();                                /* lvgl显示接口初始化,放在lv_init()的后面 */
    lv_port_indev_init();                               /* lvgl输入接口初始化,放在lv_init()的后面 */
    
    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传递给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */

    vTaskStartScheduler();                              /* 开启任务调度 */
}

/**
 * @brief       start_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区 */

    /* 创建LVGL任务 */
    xTaskCreate((TaskFunction_t )lv_demo_task,
                (const char*    )"lv_demo_task",
                (uint16_t       )LV_DEMO_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LV_DEMO_TASK_PRIO,
                (TaskHandle_t*  )&LV_DEMOTask_Handler);

    /* LED测试任务 */
    xTaskCreate((TaskFunction_t )led_task,
                (const char*    )"led_task",
                (uint16_t       )LED_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LED_TASK_PRIO,
                (TaskHandle_t*  )&LEDTask_Handler);
				
	/* PWM测试任务 */
    xTaskCreate((TaskFunction_t )pwm_task,
                (const char*    )"pwm_task",
                (uint16_t       )PWM_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )PWM_TASK_PRIO,
                (TaskHandle_t*  )&PWMTask_Handler);
				
	/* SpinEncoder测试任务 */
    xTaskCreate((TaskFunction_t )encoder_task,
                (const char*    )"encoder_task",
                (uint16_t       )Encoder_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )Encoder_TASK_PRIO,
                (TaskHandle_t*  )&EncoderTask_Handler);

    taskEXIT_CRITICAL();            /* 退出临界区 */
    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
}

/**
 * @brief       LVGL运行例程
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void lv_demo_task(void *pvParameters)
{
    lv_mainstart();  /* 测试的demo */
    
    while(1)
    {
        lv_timer_handler();         /* LVGL计时器 */
        vTaskDelay(5);
    }
}

/**
 * @brief       led_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void led_task(void *pvParameters)
{
	 unsigned portBASE_TYPE uxHighWaterMark;
    while(1)
    {
        LED0_TOGGLE();
        vTaskDelay(1000);
		/* 打印不同任务的剩余空间，剩余空间以字（2字节）为单位 */
		uxHighWaterMark = uxTaskGetStackHighWaterMark(LEDTask_Handler); 
		printf("LEDTask size = %d\r\n",uxHighWaterMark);
		uxHighWaterMark = uxTaskGetStackHighWaterMark(EncoderTask_Handler); 
		printf("EncoderTask size = %d\r\n",uxHighWaterMark);
		uxHighWaterMark = uxTaskGetStackHighWaterMark(PWMTask_Handler); 
		printf("PWMTask size = %d\r\n",uxHighWaterMark);
		uxHighWaterMark = uxTaskGetStackHighWaterMark(LV_DEMOTask_Handler); 
		printf("LV_DEMOTask size = %d\r\n",uxHighWaterMark);
	}
}

/**
 * @brief       pwm_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 * @func		控制管脚产生PWM
 */
void pwm_task(void *pvParameters)
{
    while(1)
    {
		if(Axis_Switch != 0)
		{
			/* 轴向切换:	
							Axis_Switch Value	Axis	PWM输出引脚
									1			X		PA8
									2			Y		PA2
									3			Z		PA3
			*/
			switch (Axis_Switch)
            {
                case (X_Axis_Right):                                         
                {
					LED1_TOGGLE();
					HAL_TIM_PWM_Start(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
					atim_timx_chy_npwm_set(1);              /* PA8 输出5个PWM */
					Axis_Switch = 0;
                    break;
                }
				case (X_Axis_Left):                                         
                {
					LED1_TOGGLE();
					HAL_TIM_PWM_Start(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
					atim_timx_chy_npwm_set(1);              /* PA8 输出5个PWM */
					Axis_Switch = 0;
                    break;
                }
				case Y_Axis_Right:
				{
					HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);	
					HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
					atim_tim15_chy_npwm_set(1);				/* PA2 输出5个PWM 正点原子开发板上有上拉电阻对其电平有影响 */
                    Axis_Switch = 0;
					break;
				}
				case Y_Axis_Left:
				{
					HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);	
					HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
					atim_tim15_chy_npwm_set(1);				/* PA2 输出5个PWM 正点原子开发板上有上拉电阻对其电平有影响 */
                    Axis_Switch = 0;
					break;
				}
				case Z_Axis_Right:
				{
					HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
					HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
					atim_tim15_chy_npwm_set(1);				/* PA3 输出5个PWM */
					Axis_Switch = 0;
					break;
				}
				case Z_Axis_Left:
				{
					HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
					HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
					atim_tim15_chy_npwm_set(1);				/* PA3 输出5个PWM */
					Axis_Switch = 0;
					break;
				}
                default:
                {
                    break;
                }
            }
		}
		
	}
}
		
/**
 * @brief       spinencoder
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 * @func		旋转编码器任务，不同编码器的动作触发PWM输出通道
 */
void encoder_task(void *pvParameters)
{
    while(1)
    {
        if(X_encode_Right == 1 || X_encode_Left == 1)
		{
			if(X_encode_Right)
			{
				Axis_Switch = X_Axis_Right;
				X_encode_Right = 0;
			}
			else
			{
				Axis_Switch = X_Axis_Left;
				X_encode_Left = 0;
			}
		}
		else if(Y_encode_Right == 1 || Y_encode_Left == 1)
		{
			if(Y_encode_Right)
			{
				Axis_Switch = Y_Axis_Right;
				Y_encode_Right = 0;
			}
			else
			{
				Axis_Switch = Y_Axis_Left;
				Y_encode_Left = 0;
			}
		}
		else if(Z_encode_Right == 1 || Z_encode_Left == 1)
		{
			if(Z_encode_Right)
			{
				Axis_Switch = Z_Axis_Right;
				Z_encode_Right = 0;
			}
			else
			{
				Axis_Switch = Z_Axis_Left;
				Z_encode_Left = 0;
			}
		}
//		指示灯		
//		LED1_TOGGLE();
//      vTaskDelay(1000);
    }
}


