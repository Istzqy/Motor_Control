#include "./BSP/SpinEncoder/spinencoder.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"

int g_tim3_encode_count = 0;                                   /* ��ʱ��3������� 	*/
int g_tim4_encode_count = 0;                                   /* ��ʱ��4�������  	*/
int g_tim5_encode_count = 0;                                   /* ��ʱ��5�������  	*/
/**
 * @brief   ��ʼ���ⲿ�ж�
 * @param   ��
 * @retval  ��
 */

void exti_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* ʹ��GPIO�˿�ʱ�� */
    X_INT_GPIO_CLK_ENABLE();
    Y_INT_GPIO_CLK_ENABLE();
		Z_INT_GPIO_CLK_ENABLE();
//    Z1_INT_GPIO_CLK_ENABLE();
//		Z2_INT_GPIO_CLK_ENABLE();
    
    /* ����X��������� */
    gpio_init_struct.Pin = X1_INT_GPIO_PIN|X2_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(X_INT_GPIO_PORT, &gpio_init_struct);
    
    /* ����Y��������� */
    gpio_init_struct.Pin =Y1_INT_GPIO_PIN|Y2_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(Y_INT_GPIO_PORT, &gpio_init_struct);
    
    /* ����Z��������� */
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
    
    /* �����ж����ȼ���ʹ���ж� */
    HAL_NVIC_SetPriority(XY_INT_IRQn, 0, 0);
		HAL_NVIC_SetPriority(Z_INT_IRQn, 0, 0);
//		HAL_NVIC_SetPriority(Z2_INT_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(XY_INT_IRQn);
    HAL_NVIC_EnableIRQ(Z_INT_IRQn);
//		HAL_NVIC_EnableIRQ(Z2_INT_IRQn);
}

/**
 * @brief   ��ť�ⲿ�жϷ�����
 * @param   ��
 * @retval  ��
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
 * @brief   HAL���ⲿ�жϻص�����
 * @param   GPIO_Pin: �ⲿ�ж��߶�Ӧ������
 * @retval  ��
 */



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

    switch (GPIO_Pin)
    {
        case X1_INT_GPIO_PIN: /* X����ťA�����½��ش����ж� -- ˳ʱ�� */
        {
            if(HAL_GPIO_ReadPin(X_INT_GPIO_PORT,X2_INT_GPIO_PIN))
						{
								g_tim3_encode_count ++ ;
								printf("\r\n X��������� %3d\r\n",g_tim3_encode_count);
						}
            break;
        }
        case X2_INT_GPIO_PIN: /* X����ťB�����½��ش����ж� -- ��ʱ�� */
        {
            if(HAL_GPIO_ReadPin(X_INT_GPIO_PORT,X1_INT_GPIO_PIN))
						{
								g_tim3_encode_count -- ;
								printf("\r\n X��������� %3d\r\n",g_tim3_encode_count);
						}
            break;
        }
        case Y1_INT_GPIO_PIN: /* Y����ťA�����½��ش����ж� */
        {
						if(HAL_GPIO_ReadPin(Y_INT_GPIO_PORT,Y2_INT_GPIO_PIN))
						{
							g_tim4_encode_count ++ ;
							printf("\r\n Y��������� %3d\r\n",g_tim4_encode_count);
						}
            break;
        }
        case Y2_INT_GPIO_PIN: /* Y����ťB�����½��ش����ж� */
        {
						if(HAL_GPIO_ReadPin(Y_INT_GPIO_PORT,Y1_INT_GPIO_PIN))
						{
							g_tim4_encode_count -- ;
							printf("\r\n Y��������� %3d\r\n",g_tim4_encode_count);							
						}
            break;
        }
				case Z1_INT_GPIO_PIN: /* Z����ťA�����½��ش����ж� */
        {
            if(HAL_GPIO_ReadPin(Z_INT_GPIO_PORT,Z2_INT_GPIO_PIN))
						{
							g_tim5_encode_count ++ ;
							printf("\r\n Z��������� %3d\r\n",g_tim5_encode_count);
						}
            break;
        }
        case Z2_INT_GPIO_PIN: /* Z����ťB�����½��ش����ж� */
        {
            if(HAL_GPIO_ReadPin(Z_INT_GPIO_PORT,Z1_INT_GPIO_PIN))
						{
							g_tim5_encode_count -- ;
							printf("\r\n Z��������� %3d\r\n",g_tim5_encode_count);							
						}
            break;
        }
    }

}


/* ������������  */
///******************************* �ڶ�����  ������������� ****************************************************/

///********************************* 1 ͨ�ö�ʱ�� ���������� *************************************/

//TIM_HandleTypeDef g_tim3_encode_chy_handle;         /* ��ʱ��x��� */
//TIM_HandleTypeDef g_tim4_encode_chy_handle;         /* ��ʱ��4��� */
//TIM_HandleTypeDef g_tim5_encode_chy_handle;         /* ��ʱ��5��� */
//TIM_Encoder_InitTypeDef g_tim3_encoder_chy_handle;  /* ��ʱ����������� */
//TIM_Encoder_InitTypeDef g_tim4_encoder_chy_handle;  /* ��ʱ����������� */
//TIM_Encoder_InitTypeDef g_tim5_encoder_chy_handle;  /* ��ʱ����������� */

///**
// * @brief       ͨ�ö�ʱ��TIMX ͨ��Y �������ӿ�ģʽ ��ʼ������
// * @note
// *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
// *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ42M, ���Զ�ʱ��ʱ�� = 84Mhz
// *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
// *              Ft=��ʱ������Ƶ��,��λ:Mhz
// *
// * @param       arr: �Զ���װֵ��
// * @param       psc: ʱ��Ԥ��Ƶ��
// * @retval      ��
// */
//void gtim_tim3_encoder_chy_init(uint16_t arr, uint16_t psc)
//{
//    /* ��ʱ��x���� */
//    g_tim3_encode_chy_handle.Instance = GTIM_TIM3_ENCODER;                      /* ��ʱ��x */
//    g_tim3_encode_chy_handle.Init.Prescaler = psc;                              /* ��ʱ����Ƶ */
//    g_tim3_encode_chy_handle.Init.Period = arr;                                 /* �Զ���װ��ֵ */
//    g_tim3_encode_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* ʱ�ӷ�Ƶ���� */
//    
//    /* ��ʱ��x���������� */
//    g_tim3_encoder_chy_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1��TI2����⣬4��Ƶ */
//    g_tim3_encoder_chy_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
//    g_tim3_encoder_chy_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
//    g_tim3_encoder_chy_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
//    g_tim3_encoder_chy_handle.IC1Filter = 10;                                   /* �˲������� */
//    g_tim3_encoder_chy_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
//    g_tim3_encoder_chy_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
//    g_tim3_encoder_chy_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
//    g_tim3_encoder_chy_handle.IC2Filter = 10;                                   /* �˲������� */
//    HAL_TIM_Encoder_Init(&g_tim3_encode_chy_handle, &g_tim3_encoder_chy_handle);/* ��ʼ����ʱ��x������ */
//     
//    HAL_TIM_Encoder_Start(&g_tim3_encode_chy_handle,GTIM_TIM3_ENCODER_CH1);     /* ʹ�ܱ�����ͨ��1 */
//    HAL_TIM_Encoder_Start(&g_tim3_encode_chy_handle,GTIM_TIM3_ENCODER_CH2);     /* ʹ�ܱ�����ͨ��2 */
//    __HAL_TIM_ENABLE_IT(&g_tim3_encode_chy_handle,TIM_IT_UPDATE);               /* ʹ�ܸ����ж� */
//    __HAL_TIM_CLEAR_FLAG(&g_tim3_encode_chy_handle,TIM_IT_UPDATE);              /* ��������жϱ�־λ */
//    
//}
//void gtim_tim4_encoder_chy_init(uint16_t arr, uint16_t psc)
//{
//    /* ��ʱ��x���� */
//    g_tim4_encode_chy_handle.Instance = GTIM_TIM4_ENCODER;                      /* ��ʱ��x */
//    g_tim4_encode_chy_handle.Init.Prescaler = psc;                              /* ��ʱ����Ƶ */
//    g_tim4_encode_chy_handle.Init.Period = arr;                                 /* �Զ���װ��ֵ */
//    g_tim4_encode_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* ʱ�ӷ�Ƶ���� */
//    
//    /* ��ʱ��x���������� */
//    g_tim4_encoder_chy_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1��TI2����⣬4��Ƶ */
//    g_tim4_encoder_chy_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
//    g_tim4_encoder_chy_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
//    g_tim4_encoder_chy_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
//    g_tim4_encoder_chy_handle.IC1Filter = 10;                                   /* �˲������� */
//    g_tim4_encoder_chy_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
//    g_tim4_encoder_chy_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
//    g_tim4_encoder_chy_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
//    g_tim4_encoder_chy_handle.IC2Filter = 10;                                   /* �˲������� */
//    HAL_TIM_Encoder_Init(&g_tim4_encode_chy_handle, &g_tim4_encoder_chy_handle);/* ��ʼ����ʱ��x������ */
//     
//    HAL_TIM_Encoder_Start(&g_tim4_encode_chy_handle,GTIM_TIM4_ENCODER_CH1);     /* ʹ�ܱ�����ͨ��1 */
//    HAL_TIM_Encoder_Start(&g_tim4_encode_chy_handle,GTIM_TIM4_ENCODER_CH2);     /* ʹ�ܱ�����ͨ��2 */
//    __HAL_TIM_ENABLE_IT(&g_tim4_encode_chy_handle,TIM_IT_UPDATE);               /* ʹ�ܸ����ж� */
//    __HAL_TIM_CLEAR_FLAG(&g_tim4_encode_chy_handle,TIM_IT_UPDATE);              /* ��������жϱ�־λ */
//    
//}
//void gtim_tim5_encoder_chy_init(uint16_t arr, uint16_t psc)
//{
//    /* ��ʱ��x���� */
//    g_tim5_encode_chy_handle.Instance = GTIM_TIM5_ENCODER;                      /* ��ʱ��x */
//    g_tim5_encode_chy_handle.Init.Prescaler = psc;                              /* ��ʱ����Ƶ */
//    g_tim5_encode_chy_handle.Init.Period = arr;                                 /* �Զ���װ��ֵ */
//    g_tim5_encode_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* ʱ�ӷ�Ƶ���� */
//    
//    /* ��ʱ��x���������� */
//    g_tim5_encoder_chy_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1��TI2����⣬4��Ƶ */
//    g_tim5_encoder_chy_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
//    g_tim5_encoder_chy_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
//    g_tim5_encoder_chy_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
//    g_tim5_encoder_chy_handle.IC1Filter = 10;                                   /* �˲������� */
//    g_tim5_encoder_chy_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
//    g_tim5_encoder_chy_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
//    g_tim5_encoder_chy_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
//    g_tim5_encoder_chy_handle.IC2Filter = 10;                                   /* �˲������� */
//    HAL_TIM_Encoder_Init(&g_tim5_encode_chy_handle, &g_tim5_encoder_chy_handle);/* ��ʼ����ʱ��x������ */
//     
//    HAL_TIM_Encoder_Start(&g_tim5_encode_chy_handle,GTIM_TIM5_ENCODER_CH1);     /* ʹ�ܱ�����ͨ��1 */
//    HAL_TIM_Encoder_Start(&g_tim5_encode_chy_handle,GTIM_TIM5_ENCODER_CH2);     /* ʹ�ܱ�����ͨ��2 */
//    __HAL_TIM_ENABLE_IT(&g_tim5_encode_chy_handle,TIM_IT_UPDATE);               /* ʹ�ܸ����ж� */
//    __HAL_TIM_CLEAR_FLAG(&g_tim5_encode_chy_handle,TIM_IT_UPDATE);              /* ��������жϱ�־λ */
//    
//}
///**
// * @brief       ��ʱ���ײ�������ʱ��ʹ�ܣ���������
//                �˺����ᱻHAL_TIM_Encoder_Init()����
// * @param       htim:��ʱ�����
// * @retval      ��
// */
//void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
//{
//    if (htim->Instance == GTIM_TIM3_ENCODER)
//    {
//        GPIO_InitTypeDef gpio_init_struct;
//        GTIM_TIM3_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* ����ͨ��y��GPIOʱ�� */
//        GTIM_TIM3_ENCODER_CH2_GPIO_CLK_ENABLE();
//        GTIM_TIM3_ENCODER_CH1_CLK_ENABLE();                                      /* ������ʱ��ʱ�� */
//        GTIM_TIM3_ENCODER_CH2_CLK_ENABLE();

//        gpio_init_struct.Pin = GTIM_TIM3_ENCODER_CH1_GPIO_PIN;                   /* ͨ��y��GPIO�� */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* ���� */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
//        gpio_init_struct.Alternate = GTIM_TIM3_ENCODERCH1_GPIO_AF;               /* �˿ڸ��� */
//        HAL_GPIO_Init(GTIM_TIM3_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
//        
//        gpio_init_struct.Pin = GTIM_TIM3_ENCODER_CH2_GPIO_PIN;                   /* ͨ��y��GPIO�� */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* ���� */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
//        gpio_init_struct.Alternate = GTIM_TIM3_ENCODERCH2_GPIO_AF;               /* �˿ڸ��� */
//        HAL_GPIO_Init(GTIM_TIM3_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
//       
//        HAL_NVIC_SetPriority(GTIM_TIM3_ENCODER_INT_IRQn, 2, 0);                  /* �ж����ȼ����� */
//        HAL_NVIC_EnableIRQ(GTIM_TIM3_ENCODER_INT_IRQn);                          /* �����ж� */
//    }
//	else if(htim->Instance == GTIM_TIM4_ENCODER)
//	{
//		GPIO_InitTypeDef gpio_init_struct;
//        GTIM_TIM4_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* ����ͨ��y��GPIOʱ�� */
//        GTIM_TIM4_ENCODER_CH2_GPIO_CLK_ENABLE();
//        GTIM_TIM4_ENCODER_CH1_CLK_ENABLE();                                      /* ������ʱ��ʱ�� */
//        GTIM_TIM4_ENCODER_CH2_CLK_ENABLE();

//        gpio_init_struct.Pin = GTIM_TIM4_ENCODER_CH1_GPIO_PIN;                   /* ͨ��y��GPIO�� */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* ������ */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
//        gpio_init_struct.Alternate = GTIM_TIM4_ENCODERCH1_GPIO_AF;               /* �˿ڸ��� */
//        HAL_GPIO_Init(GTIM_TIM4_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
//        
//        gpio_init_struct.Pin = GTIM_TIM4_ENCODER_CH2_GPIO_PIN;                   /* ͨ��y��GPIO�� */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* ���� */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
//        gpio_init_struct.Alternate = GTIM_TIM4_ENCODERCH2_GPIO_AF;               /* �˿ڸ��� */
//        HAL_GPIO_Init(GTIM_TIM4_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
//       
//        HAL_NVIC_SetPriority(GTIM_TIM4_ENCODER_INT_IRQn, 2, 0);                  /* �ж����ȼ����� */
//        HAL_NVIC_EnableIRQ(GTIM_TIM4_ENCODER_INT_IRQn);                          /* �����ж� */
//	}
//	else if(htim->Instance == GTIM_TIM5_ENCODER)
//	{
//		GPIO_InitTypeDef gpio_init_struct;
//        GTIM_TIM5_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* ����ͨ��y��GPIOʱ�� */
//        GTIM_TIM5_ENCODER_CH2_GPIO_CLK_ENABLE();
//        GTIM_TIM5_ENCODER_CH1_CLK_ENABLE();                                      /* ������ʱ��ʱ�� */
//        GTIM_TIM5_ENCODER_CH2_CLK_ENABLE();

//        gpio_init_struct.Pin = GTIM_TIM5_ENCODER_CH1_GPIO_PIN;                   /* ͨ��y��GPIO�� */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* ������ */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
//        gpio_init_struct.Alternate = GTIM_TIM5_ENCODERCH1_GPIO_AF;               /* �˿ڸ��� */
//        HAL_GPIO_Init(GTIM_TIM5_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
//        
//        gpio_init_struct.Pin = GTIM_TIM5_ENCODER_CH2_GPIO_PIN;                   /* ͨ��y��GPIO�� */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                                 /* ����������� */
//        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* ���� */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
//        gpio_init_struct.Alternate = GTIM_TIM5_ENCODERCH2_GPIO_AF;               /* �˿ڸ��� */
//        HAL_GPIO_Init(GTIM_TIM5_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
//       
//        HAL_NVIC_SetPriority(GTIM_TIM5_ENCODER_INT_IRQn, 2, 0);                  /* �ж����ȼ����� */
//        HAL_NVIC_EnableIRQ(GTIM_TIM5_ENCODER_INT_IRQn);                          /* �����ж� */
//	}
//}

///**
// * @brief       ��ʱ���жϷ�����
// * @param       ��
// * @retval      ��
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



//volatile int g_tim3_encode_count = 0;                                   /* ��ʱ��3������� */
//volatile int g_tim4_encode_count = 0;                                   /* ��ʱ��4������� */
//volatile int g_tim5_encode_count = 0;                                   /* ��ʱ��5������� */



///**
// * @brief       ��ʱ�������жϻص�����
// * @param        htim:��ʱ�����ָ��
// * @note        �˺����ᱻ��ʱ���жϺ�����ͬ���õ�
// * @retval      ��
// */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if (htim->Instance == TIM3)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim3_encode_chy_handle))   /* �ж�CR1��DIRλ */
//        {
//            g_tim3_encode_count--;                                      /* DIRλΪ1��Ҳ���ǵݼ����� */
//        }
//        else
//        {
//            g_tim3_encode_count++;                                      /* DIRλΪ0��Ҳ���ǵ������� */
//        }
//    }
//	else if (htim->Instance == TIM4)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim4_encode_chy_handle))   /* �ж�CR1��DIRλ */
//        {
//            g_tim4_encode_count--;                                      /* DIRλΪ1��Ҳ���ǵݼ����� */
//        }
//        else
//        {
//            g_tim4_encode_count++;                                      /* DIRλΪ0��Ҳ���ǵ������� */
//        }
//    }
//	else if (htim->Instance == TIM5)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim5_encode_chy_handle))   /* �ж�CR1��DIRλ */
//        {
//            g_tim5_encode_count--;                                      /* DIRλΪ1��Ҳ���ǵݼ����� */
//        }
//        else
//        {
//            g_tim5_encode_count++;                                      /* DIRλΪ0��Ҳ���ǵ������� */
//        }
//    }
//}





