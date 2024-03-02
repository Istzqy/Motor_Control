/**
 ****************************************************************************************************
 * @file        qspi.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       QSPI驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 北极星 H750开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#include "./BSP/QSPI/qspi.h"

/* QSPI句柄 */
QSPI_HandleTypeDef qspi_handle = {0};

/**
 * @brief   初始化QSPI
 * @param   无
 * @retval  无
 */
void qspi_init(void)
{
    qspi_handle.Instance = QUADSPI;
    qspi_handle.Init.ClockPrescaler = 2 - 1;                            /* 时钟预分频系数 */
    qspi_handle.Init.FifoThreshold = 32;                                /* FiFo阈值 */
    qspi_handle.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;   /* 采样位移 */
    qspi_handle.Init.FlashSize = 23 - 1;                                /* Flash大小 */
    qspi_handle.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_6_CYCLE;    /* 片选高电平时间 */
    qspi_handle.Init.ClockMode = QSPI_CLOCK_MODE_0;                     /* 时钟模式 */
    qspi_handle.Init.FlashID = QSPI_FLASH_ID_1;                         /* Flash ID */
    qspi_handle.Init.DualFlash = QSPI_DUALFLASH_DISABLE;                /* 双Flash模式 */
    HAL_QSPI_Init(&qspi_handle);
}

/**
 * @brief   HAL库QSPI初始化MSP函数
 * @param   无
 * @retval  无
 */
void HAL_QSPI_MspInit(QSPI_HandleTypeDef *hqspi)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    if (hqspi->Instance == QUADSPI)
    {
        /* 配置时钟 */
        rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_QSPI;
        rcc_periph_clk_init_struct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
        HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
        
        /* 使能时钟 */
        __HAL_RCC_QSPI_CLK_ENABLE();
        QSPI_CLK_GPIO_CLK_ENABLE();
        QSPI_BK1_NCS_GPIO_CLK_ENABLE();
        QSPI_BK1_IO0_GPIO_CLK_ENABLE();
        QSPI_BK1_IO1_GPIO_CLK_ENABLE();
        QSPI_BK1_IO2_GPIO_CLK_ENABLE();
        QSPI_BK1_IO3_GPIO_CLK_ENABLE();
        
        /* 初始化CLK引脚 */
        gpio_init_struct.Pin = QSPI_CLK_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_CLK_GPIO_AF;
        HAL_GPIO_Init(QSPI_CLK_GPIO_PORT, &gpio_init_struct);
        
        /* 初始化BK1_NCS引脚 */
        gpio_init_struct.Pin = QSPI_BK1_NCS_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_NCS_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_NCS_GPIO_PORT, &gpio_init_struct);
        
        /* 初始化BK1_IO0引脚 */
        gpio_init_struct.Pin = QSPI_BK1_IO0_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_IO0_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_IO0_GPIO_PORT, &gpio_init_struct);
        
        /* 初始化BK1_IO1引脚 */
        gpio_init_struct.Pin = QSPI_BK1_IO1_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_IO1_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_IO1_GPIO_PORT, &gpio_init_struct);
        
        /* 初始化BK1_IO2引脚 */
        gpio_init_struct.Pin = QSPI_BK1_IO2_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_IO2_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_IO2_GPIO_PORT, &gpio_init_struct);
        
        /* 初始化BK1_IO3引脚 */
        gpio_init_struct.Pin = QSPI_BK1_IO3_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_IO3_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_IO3_GPIO_PORT, &gpio_init_struct);
    }
}
