/**
 ****************************************************************************************************
 * @file        sdmmc_sdcard.h
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

#ifndef __SDMMC_SDCARD_H
#define __SDMMC_SDCARD_H

#include "./SYSTEM/sys/sys.h"

/* SD��ض��� */
#define SD_SDMMCX                       SDMMC1
#define SD_SDMMCX_CLK_ENABLE()          do { __HAL_RCC_SDMMC1_CLK_ENABLE(); } while (0)
#define SD_SDMMCX_CLK_DISABLE()         do { __HAL_RCC_SDMMC1_CLK_DISABLE(); } while (0)
#define SD_SDMMCX_CK_GPIO_PORT          GPIOC
#define SD_SDMMCX_CK_GPIO_PIN           GPIO_PIN_12
#define SD_SDMMCX_CK_GPIO_AF            GPIO_AF12_SDMMC1
#define SD_SDMMCX_CK_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)
#define SD_SDMMCX_CMD_GPIO_PORT         GPIOD
#define SD_SDMMCX_CMD_GPIO_PIN          GPIO_PIN_2
#define SD_SDMMCX_CMD_GPIO_AF           GPIO_AF12_SDMMC1
#define SD_SDMMCX_CMD_GPIO_CLK_ENABLE() do { __HAL_RCC_GPIOD_CLK_ENABLE(); } while (0)
#define SD_SDMMCX_D0_GPIO_PORT          GPIOC
#define SD_SDMMCX_D0_GPIO_PIN           GPIO_PIN_8
#define SD_SDMMCX_D0_GPIO_AF            GPIO_AF12_SDMMC1
#define SD_SDMMCX_D0_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)
#define SD_SDMMCX_D1_GPIO_PORT          GPIOC
#define SD_SDMMCX_D1_GPIO_PIN           GPIO_PIN_9
#define SD_SDMMCX_D1_GPIO_AF            GPIO_AF12_SDMMC1
#define SD_SDMMCX_D1_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)
#define SD_SDMMCX_D2_GPIO_PORT          GPIOC
#define SD_SDMMCX_D2_GPIO_PIN           GPIO_PIN_10
#define SD_SDMMCX_D2_GPIO_AF            GPIO_AF12_SDMMC1
#define SD_SDMMCX_D2_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)
#define SD_SDMMCX_D3_GPIO_PORT          GPIOC
#define SD_SDMMCX_D3_GPIO_PIN           GPIO_PIN_11
#define SD_SDMMCX_D3_GPIO_AF            GPIO_AF12_SDMMC1
#define SD_SDMMCX_D3_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOC_CLK_ENABLE(); } while (0)

/* SD��������ʱʱ�䶨�� */
#define SD_TIMEOUT                      ((uint32_t)0x00100000)

/* ����SD��� */
extern SD_HandleTypeDef g_sd_handle;
extern HAL_SD_CardInfoTypeDef g_sd_card_info_struct;

/* �������� */
uint8_t sd_init(void);                                                  /* ��ʼ��SD�� */
uint8_t sd_read_disk(uint8_t *buf, uint32_t address, uint32_t count);   /* ��SD��ָ������������� */
uint8_t sd_write_disk(uint8_t *buf, uint32_t address, uint32_t count);  /* дSD��ָ������������� */

#endif
