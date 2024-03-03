/**
 ****************************************************************************************************
 * @file        qspi.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       QSPI��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� ������ H750������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#include "./BSP/QSPI/qspi.h"

/* QSPI��� */
QSPI_HandleTypeDef qspi_handle = {0};

/**
 * @brief   ��ʼ��QSPI
 * @param   ��
 * @retval  ��
 */
void qspi_init(void)
{
    qspi_handle.Instance = QUADSPI;
    qspi_handle.Init.ClockPrescaler = 2 - 1;                            /* ʱ��Ԥ��Ƶϵ�� */
    qspi_handle.Init.FifoThreshold = 32;                                /* FiFo��ֵ */
    qspi_handle.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;   /* ����λ�� */
    qspi_handle.Init.FlashSize = 23 - 1;                                /* Flash��С */
    qspi_handle.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_6_CYCLE;    /* Ƭѡ�ߵ�ƽʱ�� */
    qspi_handle.Init.ClockMode = QSPI_CLOCK_MODE_0;                     /* ʱ��ģʽ */
    qspi_handle.Init.FlashID = QSPI_FLASH_ID_1;                         /* Flash ID */
    qspi_handle.Init.DualFlash = QSPI_DUALFLASH_DISABLE;                /* ˫Flashģʽ */
    HAL_QSPI_Init(&qspi_handle);
}

/**
 * @brief   HAL��QSPI��ʼ��MSP����
 * @param   ��
 * @retval  ��
 */
void HAL_QSPI_MspInit(QSPI_HandleTypeDef *hqspi)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    if (hqspi->Instance == QUADSPI)
    {
        /* ����ʱ�� */
        rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_QSPI;
        rcc_periph_clk_init_struct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
        HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
        
        /* ʹ��ʱ�� */
        __HAL_RCC_QSPI_CLK_ENABLE();
        QSPI_CLK_GPIO_CLK_ENABLE();
        QSPI_BK1_NCS_GPIO_CLK_ENABLE();
        QSPI_BK1_IO0_GPIO_CLK_ENABLE();
        QSPI_BK1_IO1_GPIO_CLK_ENABLE();
        QSPI_BK1_IO2_GPIO_CLK_ENABLE();
        QSPI_BK1_IO3_GPIO_CLK_ENABLE();
        
        /* ��ʼ��CLK���� */
        gpio_init_struct.Pin = QSPI_CLK_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_CLK_GPIO_AF;
        HAL_GPIO_Init(QSPI_CLK_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��BK1_NCS���� */
        gpio_init_struct.Pin = QSPI_BK1_NCS_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_NCS_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_NCS_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��BK1_IO0���� */
        gpio_init_struct.Pin = QSPI_BK1_IO0_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_IO0_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_IO0_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��BK1_IO1���� */
        gpio_init_struct.Pin = QSPI_BK1_IO1_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_IO1_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_IO1_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��BK1_IO2���� */
        gpio_init_struct.Pin = QSPI_BK1_IO2_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_IO2_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_IO2_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��BK1_IO3���� */
        gpio_init_struct.Pin = QSPI_BK1_IO3_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Alternate = QSPI_BK1_IO3_GPIO_AF;
        HAL_GPIO_Init(QSPI_BK1_IO3_GPIO_PORT, &gpio_init_struct);
    }
}
