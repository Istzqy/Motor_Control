/**
 ****************************************************************************************************
 * @file        spi.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       SPI��������
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

#include "./BSP/SPI/spi.h"

/* SPI��� */
SPI_HandleTypeDef g_spi2_handle = {0};

/**
 * @brief   ��ʼ��SPI2
 * @param   ��
 * @retval  ��
 */
void spi2_init(void)
{
    /* ����SPI2 */
    g_spi2_handle.Instance = SPI2_SPI;
    g_spi2_handle.Init.Mode = SPI_MODE_MASTER;                                                  /* ����ģʽ */
    g_spi2_handle.Init.Direction = SPI_DIRECTION_2LINES;                                        /* ͨ��ģʽ */
    g_spi2_handle.Init.DataSize = SPI_DATASIZE_8BIT;                                            /* ����֡��С */
    g_spi2_handle.Init.CLKPolarity = SPI_POLARITY_LOW;                                          /* ʱ�Ӽ��� */
    g_spi2_handle.Init.CLKPhase = SPI_PHASE_1EDGE;                                              /* ʱ����λ */
    g_spi2_handle.Init.NSS = SPI_NSS_SOFT;                                                      /* Ƭѡ�ź� */
    g_spi2_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;                           /* �����ʷ�Ƶϵ�� */
    g_spi2_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;                                             /* MSB��LSB���� */
    g_spi2_handle.Init.TIMode = SPI_TIMODE_DISABLE;                                             /* TIģʽ */
    g_spi2_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;                             /* CRCУ�� */
    g_spi2_handle.Init.CRCPolynomial = 0;                                                       /* CRC����ʽ */
    g_spi2_handle.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;                                     /* CRC���� */
    g_spi2_handle.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;                                        /* NSSP�ź� */
    g_spi2_handle.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;                                      /* NSSP���� */
    g_spi2_handle.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;                               /* FiFo��ֵ */
    g_spi2_handle.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;    /* ����CRC�����ʼ��ģʽ */
    g_spi2_handle.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;    /* ����CRC�����ʼ��ģʽ */
    g_spi2_handle.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;                       /* ���ݴ���ǰ��ʱ */
    g_spi2_handle.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;         /* ���ݴ������ʱ */
    g_spi2_handle.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;                 /* �Զ������������� */
    g_spi2_handle.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;                     /* ����ʱ����IO״̬ */
    g_spi2_handle.Init.IOSwap = SPI_IO_SWAP_DISABLE;                                            /* ����MISO��MOSI���� */
    HAL_SPI_Init(&g_spi2_handle);
}

/**
 * @brief   HAL��SPI2��ʼ��MSP����
 * @param   ��
 * @retval  ��
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    if (hspi->Instance == SPI2_SPI)
    {
        /* ����ʱ�� */
        rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_SPI123;
        rcc_periph_clk_init_struct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL2;
        HAL_RCCEx_PeriphCLKConfig(&rcc_periph_clk_init_struct);
        
        /* ʱ��ʹ�� */
        SPI2_SPI_CLK_ENABLE();
        SPI2_SCK_GPIO_CLK_ENABLE();
        SPI2_MISO_GPIO_CLK_ENABLE();
        SPI2_MOSI_GPIO_CLK_ENABLE();
        
        /* ����SCK���� */
        gpio_init_struct.Pin = SPI2_SCK_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = SPI2_SCK_GPIO_AF;
        HAL_GPIO_Init(SPI2_SCK_GPIO_PORT, &gpio_init_struct);
        
        /* ����MISO���� */
        gpio_init_struct.Pin = SPI2_MISO_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = SPI2_MISO_GPIO_AF;
        HAL_GPIO_Init(SPI2_MISO_GPIO_PORT, &gpio_init_struct);
        
        /* ����MOSI���� */
        gpio_init_struct.Pin = SPI2_MOSI_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = SPI2_MOSI_GPIO_AF;
        HAL_GPIO_Init(SPI2_MOSI_GPIO_PORT, &gpio_init_struct);
    }
}

/**
 * @brief   ����SPI2ͨ�Ų�����
 * @param   speed: SPI2�����ʷ�Ƶϵ��
 * @arg     SPI_BAUDRATEPRESCALER_2: 2��Ƶ
 * @arg     SPI_BAUDRATEPRESCALER_4: 2��Ƶ
 * @arg     SPI_BAUDRATEPRESCALER_8: 8��Ƶ
 * @arg     SPI_BAUDRATEPRESCALER_16: 16��Ƶ
 * @arg     SPI_BAUDRATEPRESCALER_32: 32��Ƶ
 * @arg     SPI_BAUDRATEPRESCALER_64: 64��Ƶ
 * @arg     SPI_BAUDRATEPRESCALER_128: 128��Ƶ
 * @arg     SPI_BAUDRATEPRESCALER_256: 256��Ƶ
 * @retval  ��
 */
void spi2_set_speed(uint32_t speed)
{
    __HAL_SPI_DISABLE(&g_spi2_handle);
    g_spi2_handle.Instance->CFG1 &= ~SPI_CFG1_MBR_Msk;
    g_spi2_handle.Instance->CFG1 |= speed;
    __HAL_SPI_ENABLE(&g_spi2_handle);
}
/**
 * @brief   SPI2��дһ�ֽ�����
 * @param   txdata: ��д���һ�ֽ�����
 * @retval  ��ȡ����һ�ֽ�����
 */
uint8_t spi2_read_write_byte(uint8_t txdata)
{
    uint8_t rxdata;
    
    if (HAL_SPI_TransmitReceive(&g_spi2_handle, &txdata, &rxdata, 1, 1000) != HAL_OK)
    {
        return 0;
    }
    
    return rxdata;
}
