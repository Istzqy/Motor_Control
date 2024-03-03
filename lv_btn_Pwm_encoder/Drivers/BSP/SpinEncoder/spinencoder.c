#include "./BSP/SpinEncoder/spinencoder.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"

 uint8_t X_encode_Right = 0;                                  	/* X轴右转标志 	*/
 uint8_t X_encode_Left = 0;                                   	/* X轴左转标志 	*/
 uint8_t Y_encode_Right = 0;                             		/* Y轴右转标志  	*/
 uint8_t Y_encode_Left = 0;                             		/* Y轴左转标志  	*/
 uint8_t Z_encode_Right = 0;                             		/* Z轴右转标志  	*/
 uint8_t Z_encode_Left = 0;                             		/* Z轴左转标志  	*/

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
    
    /* 配置中断优先级并使能中断 */
    HAL_NVIC_SetPriority(XY_INT_IRQn, 0, 0);
	HAL_NVIC_SetPriority(Z_INT_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(XY_INT_IRQn);
    HAL_NVIC_EnableIRQ(Z_INT_IRQn);
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
		/* X轴旋钮  A相——PB8 	B相——PB9 */
		/* Y轴旋钮  A相——PC5 	B相——PC6 */
		/* Z轴旋钮  A相——PG13 	B相——PG14 */
        case X1_INT_GPIO_PIN: /* X轴旋钮A脉冲下降沿触发中断 -- 顺时针 */
        {
            if(HAL_GPIO_ReadPin(X_INT_GPIO_PORT,X2_INT_GPIO_PIN))
						{
								X_encode_Right = 1;
								LED1_TOGGLE();
						}
            break;
        }
        case X2_INT_GPIO_PIN: /* X轴旋钮B脉冲下降沿触发中断 -- 逆时针 */
        {
            if(HAL_GPIO_ReadPin(X_INT_GPIO_PORT,X1_INT_GPIO_PIN))
						{
								X_encode_Left = 1;
								LED1_TOGGLE();	
						}
            break;
        }
        case Y1_INT_GPIO_PIN: /* Y轴旋钮A脉冲下降沿触发中断 */
        {
						if(HAL_GPIO_ReadPin(Y_INT_GPIO_PORT,Y2_INT_GPIO_PIN))
						{
							Y_encode_Right = 1;
							LED1_TOGGLE();
						}
            break;
        }
        case Y2_INT_GPIO_PIN: /* Y轴旋钮B脉冲下降沿触发中断 */
        {
						if(HAL_GPIO_ReadPin(Y_INT_GPIO_PORT,Y1_INT_GPIO_PIN))
						{
							Y_encode_Left = 1;
							LED1_TOGGLE();					
						}
            break;
        }
				case Z1_INT_GPIO_PIN: /* Z轴旋钮A脉冲下降沿触发中断 */
        {
            if(HAL_GPIO_ReadPin(Z_INT_GPIO_PORT,Z2_INT_GPIO_PIN))
						{
							Z_encode_Right = 1;
							LED1_TOGGLE();
						}
            break;
        }
        case Z2_INT_GPIO_PIN: /* Z轴旋钮B脉冲下降沿触发中断 */
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






