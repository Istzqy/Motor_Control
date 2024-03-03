#include "./BSP/SpinEncoder/spinencoder.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"

 uint8_t X_encode_Right = 0;                                  	/* X����ת��־ 	*/
 uint8_t X_encode_Left = 0;                                   	/* X����ת��־ 	*/
 uint8_t Y_encode_Right = 0;                             		/* Y����ת��־  	*/
 uint8_t Y_encode_Left = 0;                             		/* Y����ת��־  	*/
 uint8_t Z_encode_Right = 0;                             		/* Z����ת��־  	*/
 uint8_t Z_encode_Left = 0;                             		/* Z����ת��־  	*/

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
    
    /* �����ж����ȼ���ʹ���ж� */
    HAL_NVIC_SetPriority(XY_INT_IRQn, 0, 0);
	HAL_NVIC_SetPriority(Z_INT_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(XY_INT_IRQn);
    HAL_NVIC_EnableIRQ(Z_INT_IRQn);
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
		/* X����ť  A�ࡪ��PB8 	B�ࡪ��PB9 */
		/* Y����ť  A�ࡪ��PC5 	B�ࡪ��PC6 */
		/* Z����ť  A�ࡪ��PG13 	B�ࡪ��PG14 */
        case X1_INT_GPIO_PIN: /* X����ťA�����½��ش����ж� -- ˳ʱ�� */
        {
            if(HAL_GPIO_ReadPin(X_INT_GPIO_PORT,X2_INT_GPIO_PIN))
						{
								X_encode_Right = 1;
								LED1_TOGGLE();
						}
            break;
        }
        case X2_INT_GPIO_PIN: /* X����ťB�����½��ش����ж� -- ��ʱ�� */
        {
            if(HAL_GPIO_ReadPin(X_INT_GPIO_PORT,X1_INT_GPIO_PIN))
						{
								X_encode_Left = 1;
								LED1_TOGGLE();	
						}
            break;
        }
        case Y1_INT_GPIO_PIN: /* Y����ťA�����½��ش����ж� */
        {
						if(HAL_GPIO_ReadPin(Y_INT_GPIO_PORT,Y2_INT_GPIO_PIN))
						{
							Y_encode_Right = 1;
							LED1_TOGGLE();
						}
            break;
        }
        case Y2_INT_GPIO_PIN: /* Y����ťB�����½��ش����ж� */
        {
						if(HAL_GPIO_ReadPin(Y_INT_GPIO_PORT,Y1_INT_GPIO_PIN))
						{
							Y_encode_Left = 1;
							LED1_TOGGLE();					
						}
            break;
        }
				case Z1_INT_GPIO_PIN: /* Z����ťA�����½��ش����ж� */
        {
            if(HAL_GPIO_ReadPin(Z_INT_GPIO_PORT,Z2_INT_GPIO_PIN))
						{
							Z_encode_Right = 1;
							LED1_TOGGLE();
						}
            break;
        }
        case Z2_INT_GPIO_PIN: /* Z����ťB�����½��ش����ж� */
        {
            if(HAL_GPIO_ReadPin(Z_INT_GPIO_PORT,Z1_INT_GPIO_PIN))
						{
							Z_encode_Left = 1;
							LED1_TOGGLE();						
						}
            break;
        }
    }

}






