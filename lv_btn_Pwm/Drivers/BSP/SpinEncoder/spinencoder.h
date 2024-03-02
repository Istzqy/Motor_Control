#ifndef __SPINENCODER_H
#define __SPINENCODER_H


#include "./SYSTEM/sys/sys.h"

/* 引脚、中断编号和中断服务函数定义 */
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
#define XY_INT_IRQn              EXTI9_5_IRQn	/* 因为中断线9~5共用一个终端服务函数，因此无需重复定义 */
#define XY_INT_IRQHandler        EXTI9_5_IRQHandler
#define Z_INT_IRQn				 EXTI15_10_IRQn
/* 函数声明 */
void exti_init(void);   /* 外部中断初始化 */
/* 变量声明 */
extern volatile int g_tim3_encode_count ;                                   /* 定时器3编码计数 	*/
extern volatile int g_tim4_encode_count ;                                   /* 定时器4编码计数  	*/
extern volatile int g_tim5_encode_count ;                                   /* 定时器5编码计数  	*/

///* 通用定时器 定义  */
//#define GTIM_TIM3_ENCODER_CH1_GPIO_PORT         GPIOA
//#define GTIM_TIM3_ENCODER_CH1_GPIO_PIN          GPIO_PIN_6
//#define GTIM_TIM3_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA口时钟使能 */

//#define GTIM_TIM3_ENCODER_CH2_GPIO_PORT         GPIOA
//#define GTIM_TIM3_ENCODER_CH2_GPIO_PIN          GPIO_PIN_7
//#define GTIM_TIM3_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA口时钟使能 */

//#define GTIM_TIM4_ENCODER_CH1_GPIO_PORT         GPIOD
//#define GTIM_TIM4_ENCODER_CH1_GPIO_PIN          GPIO_PIN_12
//#define GTIM_TIM4_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)  /* PD口时钟使能 */

//#define GTIM_TIM4_ENCODER_CH2_GPIO_PORT         GPIOD
//#define GTIM_TIM4_ENCODER_CH2_GPIO_PIN          GPIO_PIN_13
//#define GTIM_TIM4_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)  /* PD口时钟使能 */

//#define GTIM_TIM5_ENCODER_CH1_GPIO_PORT         GPIOH
//#define GTIM_TIM5_ENCODER_CH1_GPIO_PIN          GPIO_PIN_10
//#define GTIM_TIM5_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOH_CLK_ENABLE(); }while(0)  /* PH口时钟使能 */

//#define GTIM_TIM5_ENCODER_CH2_GPIO_PORT         GPIOH
//#define GTIM_TIM5_ENCODER_CH2_GPIO_PIN          GPIO_PIN_11
//#define GTIM_TIM5_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOH_CLK_ENABLE(); }while(0)  /* PH口时钟使能 */

///* TIMX 引脚复用设置
// * 因为PC6/PC7, 默认并不是TIM3的功能脚, 必须开启复用, 才可以用作TIM3的CH1/CH2功能
// */
//#define GTIM_TIM3_ENCODERCH1_GPIO_AF            GPIO_AF2_TIM3                                /* 端口复用到TIM3 */
//#define GTIM_TIM3_ENCODERCH2_GPIO_AF            GPIO_AF2_TIM3                                /* 端口复用到TIM3 */
//#define GTIM_TIM4_ENCODERCH1_GPIO_AF            GPIO_AF2_TIM4                                /* 端口复用到TIM4 */
//#define GTIM_TIM4_ENCODERCH2_GPIO_AF            GPIO_AF2_TIM4                                /* 端口复用到TIM4 */
//#define GTIM_TIM5_ENCODERCH1_GPIO_AF            GPIO_AF2_TIM5                                /* 端口复用到TIM5 */
//#define GTIM_TIM5_ENCODERCH2_GPIO_AF            GPIO_AF2_TIM5                                /* 端口复用到TIM5 */

//#define GTIM_TIM3_ENCODER                       TIM3                                         /* TIM3 */
//#define GTIM_TIM3_ENCODER_INT_IRQn              TIM3_IRQn
//#define GTIM_TIM3_ENCODER_INT_IRQHandler        TIM3_IRQHandler
//#define GTIM_TIM4_ENCODER                       TIM4                                         /* TIM4 */
//#define GTIM_TIM4_ENCODER_INT_IRQn              TIM4_IRQn
//#define GTIM_TIM4_ENCODER_INT_IRQHandler        TIM4_IRQHandler
//#define GTIM_TIM5_ENCODER                       TIM5                                         /* TIM5 */
//#define GTIM_TIM5_ENCODER_INT_IRQn              TIM5_IRQn
//#define GTIM_TIM5_ENCODER_INT_IRQHandler        TIM5_IRQHandler



//#define GTIM_TIM3_ENCODER_CH1                   TIM_CHANNEL_1                                /* 通道1 */
//#define GTIM_TIM3_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)   /* TIM3 时钟使能 */

//#define GTIM_TIM3_ENCODER_CH2                   TIM_CHANNEL_2                                /* 通道2 */
//#define GTIM_TIM3_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)   /* TIM3 时钟使能 */

//#define GTIM_TIM4_ENCODER_CH1                   TIM_CHANNEL_1                                /* 通道1 */
//#define GTIM_TIM4_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)   /* TIM4 时钟使能 */

//#define GTIM_TIM4_ENCODER_CH2                   TIM_CHANNEL_2                                /* 通道2 */
//#define GTIM_TIM4_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)   /* TIM4 时钟使能 */

//#define GTIM_TIM5_ENCODER_CH1                   TIM_CHANNEL_1                                /* 通道1 */
//#define GTIM_TIM5_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM5_CLK_ENABLE(); }while(0)   /* TIM5 时钟使能 */

//#define GTIM_TIM5_ENCODER_CH2                   TIM_CHANNEL_2                                /* 通道2 */
//#define GTIM_TIM5_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM5_CLK_ENABLE(); }while(0)   /* TIM5 时钟使能 */



#endif
