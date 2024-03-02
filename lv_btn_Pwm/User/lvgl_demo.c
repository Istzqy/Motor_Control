/**
 ****************************************************************************************************
 * @file        lvgl_demo.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-01
 * @brief       LVGL lv_btn(��ť) ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ������ H750������
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

#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "LVGL/GUI_APP/lv_mainstart.h"

extern TIM_HandleTypeDef g_timx_npwm_handle;						/* ��ʱ��1���ͨ����� */
extern TIM_HandleTypeDef g_tim15_npwm_handle ;						/* ��ʱ��15���ͨ����� */
uint8_t Axis_Switch = 0 ;  		/* ���������л���־ */

/******************************************************************************************************/
/*FreeRTOS����*/

/* START_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define START_TASK_PRIO     1           /* �������ȼ� */
#define START_STK_SIZE      128         /* �����ջ��С */
TaskHandle_t StartTask_Handler;         /* ������ */
void start_task(void *pvParameters);    /* ������ */

/* LV_DEMO_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define LV_DEMO_TASK_PRIO   3           /* �������ȼ� */
#define LV_DEMO_STK_SIZE    2048        /* �����ջ��С */
TaskHandle_t LV_DEMOTask_Handler;       /* ������ */
void lv_demo_task(void *pvParameters);  /* ������ */

/* LED_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define LED_TASK_PRIO       4           /* �������ȼ� */
#define LED_STK_SIZE        128         /* �����ջ��С */
TaskHandle_t LEDTask_Handler;           /* ������ */
void led_task(void *pvParameters);      /* ������ */

/* PWM_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define PWM_TASK_PRIO       3           /* �������ȼ� */
#define PWM_STK_SIZE        1024         /* �����ջ��С */
TaskHandle_t PWMTask_Handler;           /* ������ */
void pwm_task(void *pvParameters);      /* ������ */
/******************************************************************************************************/


void lvgl_demo(void)
{
    lv_init();                                          /* lvglϵͳ��ʼ�� */
    lv_port_disp_init();                                /* lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ��� */
    lv_port_indev_init();                               /* lvgl����ӿڳ�ʼ��,����lv_init()�ĺ��� */
    
    xTaskCreate((TaskFunction_t )start_task,            /* ������ */
                (const char*    )"start_task",          /* �������� */
                (uint16_t       )START_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ���ݸ��������Ĳ��� */
                (UBaseType_t    )START_TASK_PRIO,       /* �������ȼ� */
                (TaskHandle_t*  )&StartTask_Handler);   /* ������ */

    vTaskStartScheduler();                              /* ����������� */
}

/**
 * @brief       start_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* �����ٽ��� */

    /* ����LVGL���� */
    xTaskCreate((TaskFunction_t )lv_demo_task,
                (const char*    )"lv_demo_task",
                (uint16_t       )LV_DEMO_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LV_DEMO_TASK_PRIO,
                (TaskHandle_t*  )&LV_DEMOTask_Handler);

    /* LED�������� */
    xTaskCreate((TaskFunction_t )led_task,
                (const char*    )"led_task",
                (uint16_t       )LED_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LED_TASK_PRIO,
                (TaskHandle_t*  )&LEDTask_Handler);
				
	/* PWM�������� */
    xTaskCreate((TaskFunction_t )pwm_task,
                (const char*    )"pwm_task",
                (uint16_t       )PWM_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )PWM_TASK_PRIO,
                (TaskHandle_t*  )&PWMTask_Handler);

    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
}

/**
 * @brief       LVGL��������
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void lv_demo_task(void *pvParameters)
{
    lv_mainstart();  /* ���Ե�demo */
    
    while(1)
    {
        lv_timer_handler();         /* LVGL��ʱ�� */
        vTaskDelay(5);
    }
}

/**
 * @brief       led_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void led_task(void *pvParameters)
{
    while(1)
    {
        LED0_TOGGLE();
        vTaskDelay(1000);
    }
}

/**
 * @brief       pwm_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void pwm_task(void *pvParameters)
{
    while(1)
    {
		if(Axis_Switch != 0)
		{
			/* �����л�:	
							Axis_Switch Value	Axis
									1			X
									2			Y
									3			Z
			*/
			switch (Axis_Switch)
            {
                case X_Axis:                                         
                {
					LED1_TOGGLE();
					HAL_TIM_PWM_Start(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
					atim_timx_chy_npwm_set(2);              /* PA8 ���5��PWM */
					Axis_Switch = 0;
                    break;
                }
				case Y_Axis:
				{
					HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);	
					HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
					atim_tim15_chy_npwm_set(3);				/* PA2 ���5��PWM ����ԭ�ӿ���������������������ƽ��Ӱ�� */
                    Axis_Switch = 0;
					break;
				}
				case Z_Axis:
				{
					HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
					HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
					HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
					atim_tim15_chy_npwm_set(4);				/* PA3 ���5��PWM */
					Axis_Switch = 0;
					break;
				}
                default:
                {
                    break;
                }
            }
		}
//		key = key_scan(0);
//        if (key == KEY0_PRES)
//        {
//				LED1_TOGGLE();
//				HAL_TIM_PWM_Start(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
//				HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
//				HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
//				atim_timx_chy_npwm_set(2);              /* PA8 ���5��PWM */
//        }
//		else if( key == KEY1_PRES)
//		{
//				LED1_TOGGLE();
//				HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);	
//				HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
//				HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
//				atim_tim15_chy_npwm_set(3);				/* PA2 ���5��PWM ����ԭ�ӿ���������������������ƽ��Ӱ�� */                                                                                                                                
//		}
//		else if( key == KEY2_PRES )
//		{
//				LED1_TOGGLE();
//				HAL_TIM_PWM_Start(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH2);
//				HAL_TIM_PWM_Stop(&g_timx_npwm_handle, ATIM_TIMX_NPWM_CHY);
//				HAL_TIM_PWM_Stop(&g_tim15_npwm_handle, ATIM_TIM15_NPWM_CH1);
//				atim_tim15_chy_npwm_set(4);				/* PA3 ���5��PWM */
//		}
//		/* ��ʾ�������������� */
//				if (++t == 20)
//				{
//						t = 0;
//						LED1_TOGGLE();
//				}
    }
}


