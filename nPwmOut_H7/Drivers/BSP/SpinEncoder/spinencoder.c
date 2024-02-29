#include "./BSP/SpinEncoder/spinencoder.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"

int g_tim3_encode_count = 0;                                   /* 定时器3编码计数 	*/
int g_tim4_encode_count = 0;                                   /* 定时器4编码计数  	*/
int g_tim5_encode_count = 0;                                   /* 定时器5编码计数  	*/
/**
 * @brief   初始化外部中断
 * @param   无
 * @retval  无
 */

void exti_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能GPIO端口时钟 */
    X_INT_GPIO_CLK_ENABLE();
    Y_INT_GPIO_CLK_ENABLE();
		Z_INT_GPIO_CLK_ENABLE();
//    Z1_INT_GPIO_CLK_ENABLE();
//		Z2_INT_GPIO_CLK_ENABLE();
    
    /* 配置X轴控制引脚 */
    gpio_init_struct.Pin = X1_INT_GPIO_PIN|X2_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(X_INT_GPIO_PORT, &gpio_init_struct);
    
    /* 配置Y轴控制引脚 */
    gpio_init_struct.Pin =Y1_INT_GPIO_PIN|Y2_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(Y_INT_GPIO_PORT, &gpio_init_struct);
    
    /* 配置Z轴控制引脚 */
    gpio_init_struct.Pin = Z1_INT_GPIO_PIN|Z2_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(Z_INT_GPIO_PORT, &gpio_init_struct);
		
//		gpio_init_struct.Pin = Z2_INT_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;
//    gpio_init_struct.Pull = GPIO_PULLUP;
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
//    HAL_GPIO_Init(Z2_INT_GPIO_PORT, &gpio_init_struct);
    
    /* 配置中断优先级并使能中断 */
    HAL_NVIC_SetPriority(XY_INT_IRQn, 0, 0);
		HAL_NVIC_SetPriority(Z_INT_IRQn, 0, 0);
//		HAL_NVIC_SetPriority(Z2_INT_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(XY_INT_IRQn);
    HAL_NVIC_EnableIRQ(Z_INT_IRQn);
//		HAL_NVIC_EnableIRQ(Z2_INT_IRQn);
}

/**
 * @brief   旋钮外部中断服务函数
 * @param   无
 * @retval  无
 */
void XY_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(X1_INT_GPIO_PIN);
		HAL_GPIO_EXTI_IRQHandler(X2_INT_GPIO_PIN);
		HAL_GPIO_EXTI_IRQHandler(Y1_INT_GPIO_PIN);
		HAL_GPIO_EXTI_IRQHandler(Y2_INT_GPIO_PIN);	
}
void Z_INT_IRQHandler(void)
{	
		HAL_GPIO_EXTI_IRQHandler(Z1_INT_GPIO_PIN);
		HAL_GPIO_EXTI_IRQHandler(Z2_INT_GPIO_PIN);		
}

/**
 * @brief   HAL库外部中断回调函数
 * @param   GPIO_Pin: 外部中断线对应的引脚
 * @retval  无
 */



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

    switch (GPIO_Pin)
    {
        case X1_INT_GPIO_PIN: /* X轴旋钮A脉冲下降沿触发中断 -- 顺时针 */
        {
            if(HAL_GPIO_ReadPin(X_INT_GPIO_PORT,X2_INT_GPIO_PIN))
						{
								g_tim3_encode_count ++ ;
								printf("\r\n X轴脉冲计数 %3d\r\n",g_tim3_encode_count);
						}
            break;
        }
        case X2_INT_GPIO_PIN: /* X轴旋钮B脉冲下降沿触发中断 -- 逆时针 */
        {
            if(HAL_GPIO_ReadPin(X_INT_GPIO_PORT,X1_INT_GPIO_PIN))
						{
								g_tim3_encode_count -- ;
								printf("\r\n X轴脉冲计数 %3d\r\n",g_tim3_encode_count);
						}
            break;
        }
        case Y1_INT_GPIO_PIN: /* Y轴旋钮A脉冲下降沿触发中断 */
        {
						if(HAL_GPIO_ReadPin(Y_INT_GPIO_PORT,Y2_INT_GPIO_PIN))
						{
							g_tim4_encode_count ++ ;
							printf("\r\n Y轴脉冲计数 %3d\r\n",g_tim4_encode_count);
						}
            break;
        }
        case Y2_INT_GPIO_PIN: /* Y轴旋钮B脉冲下降沿触发中断 */
        {
						if(HAL_GPIO_ReadPin(Y_INT_GPIO_PORT,Y1_INT_GPIO_PIN))
						{
							g_tim4_encode_count -- ;
							printf("\r\n Y轴脉冲计数 %3d\r\n",g_tim4_encode_count);							
						}
            break;
        }
				case Z1_INT_GPIO_PIN: /* Z轴旋钮A脉冲下降沿触发中断 */
        {
            if(HAL_GPIO_ReadPin(Z_INT_GPIO_PORT,Z2_INT_GPIO_PIN))
						{
							g_tim5_encode_count ++ ;
							printf("\r\n Z轴脉冲计数 %3d\r\n",g_tim5_encode_count);
						}
            break;
        }
        case Z2_INT_GPIO_PIN: /* Z轴旋钮B脉冲下降沿触发中断 */
        {
            if(HAL_GPIO_ReadPin(Z_INT_GPIO_PORT,Z1_INT_GPIO_PIN))
						{
							g_tim5_encode_count -- ;
							printf("\r\n Z轴脉冲计数 %3d\r\n",g_tim5_encode_count);							
						}
            break;
        }
    }

}


/* 方案二已舍弃  */
///******************************* 第二部分  电机编码器测速 ****************************************************/

///********************************* 1 通用定时器 编码器程序 *************************************/

//TIM_HandleTypeDef g_tim3_encode_chy_handle;         /* 定时器x句柄 */
//TIM_HandleTypeDef g_tim4_encode_chy_handle;         /* 定时器4句柄 */
//TIM_HandleTypeDef g_tim5_encode_chy_handle;         /* 定时器5句柄 */
//TIM_Encoder_InitTypeDef g_tim3_encoder_chy_handle;  /* 定时器编码器句柄 */
//TIM_Encoder_InitTypeDef g_tim4_encoder_chy_handle;  /* 定时器编码器句柄 */
//TIM_Encoder_InitTypeDef g_tim5_encoder_chy_handle;  /* 定时器编码器句柄 */

///**
// * @brief       通用定时器TIMX 通道Y 编码器接口模式 初始化函数
// * @note
// *              通用定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
// *              通用定时器的时钟为APB1时钟的2倍, 而APB1为42M, 所以定时器时钟 = 84Mhz
// *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
// *              Ft=定时器工作频率,单位:Mhz
// *
// * @param       arr: 自动重装值。
// * @param       psc: 时钟预分频数
// * @retval      无
// */
//void gtim_tim3_encoder_chy_init(uint16_t arr, uint16_t psc)
//{
//    /* 定时器x配置 */
//    g_tim3_encode_chy_handle.Instance = GTIM_TIM3_ENCODER;                      /* 定时器x */
//    g_tim3_encode_chy_handle.Init.Prescaler = psc;                              /* 定时器分频 */
//    g_tim3_encode_chy_handle.Init.Period = arr;                                 /* 自动重装载值 */
//    g_tim3_encode_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* 时钟分频因子 */
//    
//    /* 定时器x编码器配置 */
//    g_tim3_encoder_chy_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1、TI2都检测，4倍频 */
//    g_tim3_encoder_chy_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
//    g_tim3_encoder_chy_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
//    g_tim3_encoder_chy_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
//    g_tim3_encoder_chy_handle.IC1Filter = 10;                                   /* 滤波器设置 */
//    g_tim3_encoder_chy_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
//    g_tim3_encoder_chy_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
//    g_tim3_encoder_chy_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
//    g_tim3_encoder_chy_handle.IC2Filter = 10;                                   /* 滤波器设置 */
//    HAL_TIM_Encoder_Init(&g_tim3_encode_chy_handle, &g_tim3_encoder_chy_handle);/* 初始化定时器x编码器 */
//     
//    HAL_TIM_Encoder_Start(&g_tim3_encode_chy_handle,GTIM_TIM3_ENCODER_CH1);     /* 使能编码器通道1 */
//    HAL_TIM_Encoder_Start(&g_tim3_encode_chy_handle,GTIM_TIM3_ENCODER_CH2);     /* 使能编码器通道2 */
//    __HAL_TIM_ENABLE_IT(&g_tim3_encode_chy_handle,TIM_IT_UPDATE);               /* 使能更新中断 */
//    __HAL_TIM_CLEAR_FLAG(&g_tim3_encode_chy_handle,TIM_IT_UPDATE);              /* 清除更新中断标志位 */
//    
//}
//void gtim_tim4_encoder_chy_init(uint16_t arr, uint16_t psc)
//{
//    /* 定时器x配置 */
//    g_tim4_encode_chy_handle.Instance = GTIM_TIM4_ENCODER;                      /* 定时器x */
//    g_tim4_encode_chy_handle.Init.Prescaler = psc;                              /* 定时器分频 */
//    g_tim4_encode_chy_handle.Init.Period = arr;                                 /* 自动重装载值 */
//    g_tim4_encode_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* 时钟分频因子 */
//    
//    /* 定时器x编码器配置 */
//    g_tim4_encoder_chy_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1、TI2都检测，4倍频 */
//    g_tim4_encoder_chy_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
//    g_tim4_encoder_chy_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
//    g_tim4_encoder_chy_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
//    g_tim4_encoder_chy_handle.IC1Filter = 10;                                   /* 滤波器设置 */
//    g_tim4_encoder_chy_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
//    g_tim4_encoder_chy_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
//    g_tim4_encoder_chy_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
//    g_tim4_encoder_chy_handle.IC2Filter = 10;                                   /* 滤波器设置 */
//    HAL_TIM_Encoder_Init(&g_tim4_encode_chy_handle, &g_tim4_encoder_chy_handle);/* 初始化定时器x编码器 */
//     
//    HAL_TIM_Encoder_Start(&g_tim4_encode_chy_handle,GTIM_TIM4_ENCODER_CH1);     /* 使能编码器通道1 */
//    HAL_TIM_Encoder_Start(&g_tim4_encode_chy_handle,GTIM_TIM4_ENCODER_CH2);     /* 使能编码器通道2 */
//    __HAL_TIM_ENABLE_IT(&g_tim4_encode_chy_handle,TIM_IT_UPDATE);               /* 使能更新中断 */
//    __HAL_TIM_CLEAR_FLAG(&g_tim4_encode_chy_handle,TIM_IT_UPDATE);              /* 清除更新中断标志位 */
//    
//}
//void gtim_tim5_encoder_chy_init(uint16_t arr, uint16_t psc)
//{
//    /* 定时器x配置 */
//    g_tim5_encode_chy_handle.Instance = GTIM_TIM5_ENCODER;                      /* 定时器x */
//    g_tim5_encode_chy_handle.Init.Prescaler = psc;                              /* 定时器分频 */
//    g_tim5_encode_chy_handle.Init.Period = arr;                                 /* 自动重装载值 */
//    g_tim5_encode_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* 时钟分频因子 */
//    
//    /* 定时器x编码器配置 */
//    g_tim5_encoder_chy_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1、TI2都检测，4倍频 */
//    g_tim5_encoder_chy_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
//    g_tim5_encoder_chy_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
//    g_tim5_encoder_chy_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
//    g_tim5_encoder_chy_handle.IC1Filter = 10;                                   /* 滤波器设置 */
//    g_tim5_encoder_chy_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
//    g_tim5_encoder_chy_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
//    g_tim5_encoder_chy_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
//    g_tim5_encoder_chy_handle.IC2Filter = 10;                                   /* 滤波器设置 */
//    HAL_TIM_Encoder_Init(&g_tim5_encode_chy_handle, &g_tim5_encoder_chy_handle);/* 初始化定时器x编码器 */
//     
//    HAL_TIM_Encoder_Start(&g_tim5_encode_chy_handle,GTIM_TIM5_ENCODER_CH1);     /* 使能编码器通道1 */
//    HAL_TIM_Encoder_Start(&g_tim5_encode_chy_handle,GTIM_TIM5_ENCODER_CH2);     /* 使能编码器通道2 */
//    __HAL_TIM_ENABLE_IT(&g_tim5_encode_chy_handle,TIM_IT_UPDATE);               /* 使能更新中断 */
//    __HAL_TIM_CLEAR_FLAG(&g_tim5_encode_chy_handle,TIM_IT_UPDATE);              /* 清除更新中断标志位 */
//    
//}
///**
// * @brief       定时器底层驱动，时钟使能，引脚配置
//                此函数会被HAL_TIM_Encoder_Init()调用
// * @param       htim:定时器句柄
// * @retval      无
// */
//void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
//{
//    if (htim->Instance == GTIM_TIM3_ENCODER)
//    {
//        GPIO_InitTypeDef gpio_init_struct;
//        GTIM_TIM3_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* 开启通道y的GPIO时钟 */
//        GTIM_TIM3_ENCODER_CH2_GPIO_CLK_ENABLE();
//        GTIM_TIM3_ENCODER_CH1_CLK_ENABLE();                                      /* 开启定时器时钟 */
//        GTIM_TIM3_ENCODER_CH2_CLK_ENABLE();

//        gpio_init_struct.Pin = GTIM_TIM3_ENCODER_CH1_GPIO_PIN;                   /* 通道y的GPIO口 */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 上拉 */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
//        gpio_init_struct.Alternate = GTIM_TIM3_ENCODERCH1_GPIO_AF;               /* 端口复用 */
//        HAL_GPIO_Init(GTIM_TIM3_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
//        
//        gpio_init_struct.Pin = GTIM_TIM3_ENCODER_CH2_GPIO_PIN;                   /* 通道y的GPIO口 */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 上拉 */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
//        gpio_init_struct.Alternate = GTIM_TIM3_ENCODERCH2_GPIO_AF;               /* 端口复用 */
//        HAL_GPIO_Init(GTIM_TIM3_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
//       
//        HAL_NVIC_SetPriority(GTIM_TIM3_ENCODER_INT_IRQn, 2, 0);                  /* 中断优先级设置 */
//        HAL_NVIC_EnableIRQ(GTIM_TIM3_ENCODER_INT_IRQn);                          /* 开启中断 */
//    }
//	else if(htim->Instance == GTIM_TIM4_ENCODER)
//	{
//		GPIO_InitTypeDef gpio_init_struct;
//        GTIM_TIM4_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* 开启通道y的GPIO时钟 */
//        GTIM_TIM4_ENCODER_CH2_GPIO_CLK_ENABLE();
//        GTIM_TIM4_ENCODER_CH1_CLK_ENABLE();                                      /* 开启定时器时钟 */
//        GTIM_TIM4_ENCODER_CH2_CLK_ENABLE();

//        gpio_init_struct.Pin = GTIM_TIM4_ENCODER_CH1_GPIO_PIN;                   /* 通道y的GPIO口 */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 不上拉 */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
//        gpio_init_struct.Alternate = GTIM_TIM4_ENCODERCH1_GPIO_AF;               /* 端口复用 */
//        HAL_GPIO_Init(GTIM_TIM4_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
//        
//        gpio_init_struct.Pin = GTIM_TIM4_ENCODER_CH2_GPIO_PIN;                   /* 通道y的GPIO口 */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 上拉 */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
//        gpio_init_struct.Alternate = GTIM_TIM4_ENCODERCH2_GPIO_AF;               /* 端口复用 */
//        HAL_GPIO_Init(GTIM_TIM4_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
//       
//        HAL_NVIC_SetPriority(GTIM_TIM4_ENCODER_INT_IRQn, 2, 0);                  /* 中断优先级设置 */
//        HAL_NVIC_EnableIRQ(GTIM_TIM4_ENCODER_INT_IRQn);                          /* 开启中断 */
//	}
//	else if(htim->Instance == GTIM_TIM5_ENCODER)
//	{
//		GPIO_InitTypeDef gpio_init_struct;
//        GTIM_TIM5_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* 开启通道y的GPIO时钟 */
//        GTIM_TIM5_ENCODER_CH2_GPIO_CLK_ENABLE();
//        GTIM_TIM5_ENCODER_CH1_CLK_ENABLE();                                      /* 开启定时器时钟 */
//        GTIM_TIM5_ENCODER_CH2_CLK_ENABLE();

//        gpio_init_struct.Pin = GTIM_TIM5_ENCODER_CH1_GPIO_PIN;                   /* 通道y的GPIO口 */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 不上拉 */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
//        gpio_init_struct.Alternate = GTIM_TIM5_ENCODERCH1_GPIO_AF;               /* 端口复用 */
//        HAL_GPIO_Init(GTIM_TIM5_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
//        
//        gpio_init_struct.Pin = GTIM_TIM5_ENCODER_CH2_GPIO_PIN;                   /* 通道y的GPIO口 */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* 复用推挽输出 */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 上拉 */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
//        gpio_init_struct.Alternate = GTIM_TIM5_ENCODERCH2_GPIO_AF;               /* 端口复用 */
//        HAL_GPIO_Init(GTIM_TIM5_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
//       
//        HAL_NVIC_SetPriority(GTIM_TIM5_ENCODER_INT_IRQn, 2, 0);                  /* 中断优先级设置 */
//        HAL_NVIC_EnableIRQ(GTIM_TIM5_ENCODER_INT_IRQn);                          /* 开启中断 */
//	}
//}

///**
// * @brief       定时器中断服务函数
// * @param       无
// * @retval      无
// */
//void GTIM_TIM3_ENCODER_INT_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&g_tim3_encode_chy_handle);
//}
//void GTIM_TIM4_ENCODER_INT_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&g_tim4_encode_chy_handle);
//}
//void GTIM_TIM5_ENCODER_INT_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&g_tim5_encode_chy_handle);
//}



//volatile int g_tim3_encode_count = 0;                                   /* 定时器3溢出次数 */
//volatile int g_tim4_encode_count = 0;                                   /* 定时器4溢出次数 */
//volatile int g_tim5_encode_count = 0;                                   /* 定时器5溢出次数 */



///**
// * @brief       定时器更新中断回调函数
// * @param        htim:定时器句柄指针
// * @note        此函数会被定时器中断函数共同调用的
// * @retval      无
// */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if (htim->Instance == TIM3)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim3_encode_chy_handle))   /* 判断CR1的DIR位 */
//        {
//            g_tim3_encode_count--;                                      /* DIR位为1，也就是递减计数 */
//        }
//        else
//        {
//            g_tim3_encode_count++;                                      /* DIR位为0，也就是递增计数 */
//        }
//    }
//	else if (htim->Instance == TIM4)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim4_encode_chy_handle))   /* 判断CR1的DIR位 */
//        {
//            g_tim4_encode_count--;                                      /* DIR位为1，也就是递减计数 */
//        }
//        else
//        {
//            g_tim4_encode_count++;                                      /* DIR位为0，也就是递增计数 */
//        }
//    }
//	else if (htim->Instance == TIM5)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim5_encode_chy_handle))   /* 判断CR1的DIR位 */
//        {
//            g_tim5_encode_count--;                                      /* DIR位为1，也就是递减计数 */
//        }
//        else
//        {
//            g_tim5_encode_count++;                                      /* DIR位为0，也就是递增计数 */
//        }
//    }
//}





