/**
 ****************************************************************************************************
 * @file        sdmmc_sdcard.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       SD����������
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

#include "./BSP/SDMMC/sdmmc_sdcard.h"
#include "./SYSTEM/delay/delay.h"

/* SD��� */
SD_HandleTypeDef g_sd_handle = {0};
HAL_SD_CardInfoTypeDef g_sd_card_info_struct = {0};

/**
 * @brief   ��ʼ��SD��
 * @param   ��
 * @retval  ��
 */
uint8_t sd_init(void)
{
    g_sd_handle.Instance = SD_SDMMCX;
    g_sd_handle.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;                       /* ʱ����λ */
    g_sd_handle.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;           /* ����ģʽ */
    g_sd_handle.Init.BusWide = SDMMC_BUS_WIDE_4B;                               /* ������ģʽ */
    g_sd_handle.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_ENABLE;  /* Ӳ������ */
    g_sd_handle.Init.ClockDiv = 5;                                              /* ʱ�ӷ�Ƶϵ�� */
    HAL_SD_DeInit(&g_sd_handle);
    if (HAL_SD_Init(&g_sd_handle) != HAL_OK)
    {
        return 1;
    }
    
    if (HAL_SD_GetCardInfo(&g_sd_handle, &g_sd_card_info_struct) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief   HAL��SD��ʼ��MSP����
 * @param   ��
 * @retval  ��
 */
void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    if (hsd->Instance == SD_SDMMCX)
    {
        /* ����ʱ�� */
        rcc_periph_clk_init_struct.PeriphClockSelection |= RCC_PERIPHCLK_SDMMC;
        rcc_periph_clk_init_struct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
        
        /* ʹ��ʱ�� */
        SD_SDMMCX_CLK_ENABLE();
        SD_SDMMCX_CK_GPIO_CLK_ENABLE();
        SD_SDMMCX_CMD_GPIO_CLK_ENABLE();
        SD_SDMMCX_D0_GPIO_CLK_ENABLE();
        SD_SDMMCX_D1_GPIO_CLK_ENABLE();
        SD_SDMMCX_D2_GPIO_CLK_ENABLE();
        SD_SDMMCX_D3_GPIO_CLK_ENABLE();
        
        /* ��ʼ��CK���� */
        gpio_init_struct.Pin = SD_SDMMCX_CK_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = SD_SDMMCX_CK_GPIO_AF;
        HAL_GPIO_Init(SD_SDMMCX_CK_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��CMD���� */
        gpio_init_struct.Pin = SD_SDMMCX_CMD_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = SD_SDMMCX_CMD_GPIO_AF;
        HAL_GPIO_Init(SD_SDMMCX_CMD_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��D0���� */
        gpio_init_struct.Pin = SD_SDMMCX_D0_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = SD_SDMMCX_D0_GPIO_AF;
        HAL_GPIO_Init(SD_SDMMCX_D0_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��D1���� */
        gpio_init_struct.Pin = SD_SDMMCX_D1_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = SD_SDMMCX_D1_GPIO_AF;
        HAL_GPIO_Init(SD_SDMMCX_D1_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��D2���� */
        gpio_init_struct.Pin = SD_SDMMCX_D2_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = SD_SDMMCX_D2_GPIO_AF;
        HAL_GPIO_Init(SD_SDMMCX_D2_GPIO_PORT, &gpio_init_struct);
        
        /* ��ʼ��D3���� */
        gpio_init_struct.Pin = SD_SDMMCX_D3_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = SD_SDMMCX_D3_GPIO_AF;
        HAL_GPIO_Init(SD_SDMMCX_D3_GPIO_PORT, &gpio_init_struct);
    }
}

/**
 * @brief   HAL��SD����ʼ��MSP����
 * @param   ��
 * @retval  ��
 */
void HAL_SD_MspDeInit(SD_HandleTypeDef *hsd)
{
    if (hsd->Instance == SD_SDMMCX)
    {
        /* ʧ��ʱ�� */
        SD_SDMMCX_CLK_DISABLE();
        
        /* ����ʼ������ */
        HAL_GPIO_DeInit(SD_SDMMCX_CK_GPIO_PORT, SD_SDMMCX_CK_GPIO_PIN);
        HAL_GPIO_DeInit(SD_SDMMCX_CMD_GPIO_PORT, SD_SDMMCX_CMD_GPIO_PIN);
        HAL_GPIO_DeInit(SD_SDMMCX_D0_GPIO_PORT, SD_SDMMCX_D0_GPIO_PIN);
        HAL_GPIO_DeInit(SD_SDMMCX_D1_GPIO_PORT, SD_SDMMCX_D1_GPIO_PIN);
        HAL_GPIO_DeInit(SD_SDMMCX_D2_GPIO_PORT, SD_SDMMCX_D2_GPIO_PIN);
        HAL_GPIO_DeInit(SD_SDMMCX_D3_GPIO_PORT, SD_SDMMCX_D3_GPIO_PIN);
    }
}

/**
 * @brief   ��SD��ָ�������������
 * @param   buf: ���ݱ������ʼ��ַ
 * @param   address: ���ַ
 * @param   count: ������
 * @retval  ��ȡ���
 * @arg     0: ���ɹ�
 * @arg     1: ��ʧ��
 */
uint8_t sd_read_disk(uint8_t *buf, uint32_t address, uint32_t count)
{
    uint32_t timeout = SD_TIMEOUT;
    
    if (HAL_SD_ReadBlocks(&g_sd_handle, buf, address, count, SD_TIMEOUT) != HAL_OK)
    {
        return 1;
    }
    
    while ((HAL_SD_GetCardState(&g_sd_handle) != HAL_SD_CARD_TRANSFER) && (--timeout != 0));
    
    if (timeout == 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief   дSD��ָ�������������
 * @param   buf: ���ݱ������ʼ��ַ
 * @param   address: ���ַ
 * @param   count: ������
 * @retval  д����
 * @arg     0: �ɹ�
 * @arg     1: ʧ��
 */
uint8_t sd_write_disk(uint8_t *buf, uint32_t address, uint32_t count)
{
    uint32_t timeout = SD_TIMEOUT;
    
    if (HAL_SD_WriteBlocks(&g_sd_handle, buf, address, count, SD_TIMEOUT) != HAL_OK)
    {
        return 1;
    }
    
    while ((HAL_SD_GetCardState(&g_sd_handle) != HAL_SD_CARD_TRANSFER) && (--timeout != 0));
    
    if (timeout == 0)
    {
        return 1;
    }
    
    return 0;
}
