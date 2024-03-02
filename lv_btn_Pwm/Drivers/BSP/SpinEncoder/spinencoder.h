#ifndef __SPINENCODER_H
#define __SPINENCODER_H


#include "./SYSTEM/sys/sys.h"

/* ���š��жϱ�ź��жϷ��������� */
#define X_INT_GPIO_PORT          GPIOB
#define X1_INT_GPIO_PIN          GPIO_PIN_8
#define X2_INT_GPIO_PIN          GPIO_PIN_9
#define X_INT_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)
#define Y_INT_GPIO_PORT          GPIOC
#define Y1_INT_GPIO_PIN          GPIO_PIN_5
#define Y2_INT_GPIO_PIN          GPIO_PIN_6
#define Y_INT_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)
#define Z_INT_GPIO_PORT          GPIOG
#define Z1_INT_GPIO_PIN          GPIO_PIN_13
#define Z2_INT_GPIO_PIN          GPIO_PIN_14
#define Z_INT_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOG_CLK_ENABLE(); } while (0)
#define XY_INT_IRQn              EXTI9_5_IRQn	/* ��Ϊ�ж���9~5����һ���ն˷���������������ظ����� */
#define XY_INT_IRQHandler        EXTI9_5_IRQHandler
#define Z_INT_IRQn				 EXTI15_10_IRQn
/* �������� */
void exti_init(void);   /* �ⲿ�жϳ�ʼ�� */
/* �������� */
extern volatile int g_tim3_encode_count ;                                   /* ��ʱ��3������� 	*/
extern volatile int g_tim4_encode_count ;                                   /* ��ʱ��4�������  	*/
extern volatile int g_tim5_encode_count ;                                   /* ��ʱ��5�������  	*/

///* ͨ�ö�ʱ�� ����  */
//#define GTIM_TIM3_ENCODER_CH1_GPIO_PORT         GPIOA
//#define GTIM_TIM3_ENCODER_CH1_GPIO_PIN          GPIO_PIN_6
//#define GTIM_TIM3_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA��ʱ��ʹ�� */

//#define GTIM_TIM3_ENCODER_CH2_GPIO_PORT         GPIOA
//#define GTIM_TIM3_ENCODER_CH2_GPIO_PIN          GPIO_PIN_7
//#define GTIM_TIM3_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA��ʱ��ʹ�� */

//#define GTIM_TIM4_ENCODER_CH1_GPIO_PORT         GPIOD
//#define GTIM_TIM4_ENCODER_CH1_GPIO_PIN          GPIO_PIN_12
//#define GTIM_TIM4_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)  /* PD��ʱ��ʹ�� */

//#define GTIM_TIM4_ENCODER_CH2_GPIO_PORT         GPIOD
//#define GTIM_TIM4_ENCODER_CH2_GPIO_PIN          GPIO_PIN_13
//#define GTIM_TIM4_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)  /* PD��ʱ��ʹ�� */

//#define GTIM_TIM5_ENCODER_CH1_GPIO_PORT         GPIOH
//#define GTIM_TIM5_ENCODER_CH1_GPIO_PIN          GPIO_PIN_10
//#define GTIM_TIM5_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOH_CLK_ENABLE(); }while(0)  /* PH��ʱ��ʹ�� */

//#define GTIM_TIM5_ENCODER_CH2_GPIO_PORT         GPIOH
//#define GTIM_TIM5_ENCODER_CH2_GPIO_PIN          GPIO_PIN_11
//#define GTIM_TIM5_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOH_CLK_ENABLE(); }while(0)  /* PH��ʱ��ʹ�� */

///* TIMX ���Ÿ�������
// * ��ΪPC6/PC7, Ĭ�ϲ�����TIM3�Ĺ��ܽ�, ���뿪������, �ſ�������TIM3��CH1/CH2����
// */
//#define GTIM_TIM3_ENCODERCH1_GPIO_AF            GPIO_AF2_TIM3                                /* �˿ڸ��õ�TIM3 */
//#define GTIM_TIM3_ENCODERCH2_GPIO_AF            GPIO_AF2_TIM3                                /* �˿ڸ��õ�TIM3 */
//#define GTIM_TIM4_ENCODERCH1_GPIO_AF            GPIO_AF2_TIM4                                /* �˿ڸ��õ�TIM4 */
//#define GTIM_TIM4_ENCODERCH2_GPIO_AF            GPIO_AF2_TIM4                                /* �˿ڸ��õ�TIM4 */
//#define GTIM_TIM5_ENCODERCH1_GPIO_AF            GPIO_AF2_TIM5                                /* �˿ڸ��õ�TIM5 */
//#define GTIM_TIM5_ENCODERCH2_GPIO_AF            GPIO_AF2_TIM5                                /* �˿ڸ��õ�TIM5 */

//#define GTIM_TIM3_ENCODER                       TIM3                                         /* TIM3 */
//#define GTIM_TIM3_ENCODER_INT_IRQn              TIM3_IRQn
//#define GTIM_TIM3_ENCODER_INT_IRQHandler        TIM3_IRQHandler
//#define GTIM_TIM4_ENCODER                       TIM4                                         /* TIM4 */
//#define GTIM_TIM4_ENCODER_INT_IRQn              TIM4_IRQn
//#define GTIM_TIM4_ENCODER_INT_IRQHandler        TIM4_IRQHandler
//#define GTIM_TIM5_ENCODER                       TIM5                                         /* TIM5 */
//#define GTIM_TIM5_ENCODER_INT_IRQn              TIM5_IRQn
//#define GTIM_TIM5_ENCODER_INT_IRQHandler        TIM5_IRQHandler



//#define GTIM_TIM3_ENCODER_CH1                   TIM_CHANNEL_1                                /* ͨ��1 */
//#define GTIM_TIM3_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)   /* TIM3 ʱ��ʹ�� */

//#define GTIM_TIM3_ENCODER_CH2                   TIM_CHANNEL_2                                /* ͨ��2 */
//#define GTIM_TIM3_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)   /* TIM3 ʱ��ʹ�� */

//#define GTIM_TIM4_ENCODER_CH1                   TIM_CHANNEL_1                                /* ͨ��1 */
//#define GTIM_TIM4_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)   /* TIM4 ʱ��ʹ�� */

//#define GTIM_TIM4_ENCODER_CH2                   TIM_CHANNEL_2                                /* ͨ��2 */
//#define GTIM_TIM4_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)   /* TIM4 ʱ��ʹ�� */

//#define GTIM_TIM5_ENCODER_CH1                   TIM_CHANNEL_1                                /* ͨ��1 */
//#define GTIM_TIM5_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM5_CLK_ENABLE(); }while(0)   /* TIM5 ʱ��ʹ�� */

//#define GTIM_TIM5_ENCODER_CH2                   TIM_CHANNEL_2                                /* ͨ��2 */
//#define GTIM_TIM5_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM5_CLK_ENABLE(); }while(0)   /* TIM5 ʱ��ʹ�� */



#endif
