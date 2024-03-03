/**
 ****************************************************************************************************
 * @file        spi.h
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

#ifndef __SPI_H
#define __SPI_H

#include "./SYSTEM/sys/sys.h"

/* SPI���� */
#define SPI2_SPI                    SPI2
#define SPI2_SPI_CLK_ENABLE()       do { __HAL_RCC_SPI2_CLK_ENABLE(); } while (0)
#define SPI2_SCK_GPIO_PORT          GPIOB
#define SPI2_SCK_GPIO_PIN           GPIO_PIN_13
#define SPI2_SCK_GPIO_AF            GPIO_AF5_SPI2
#define SPI2_SCK_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)
#define SPI2_MISO_GPIO_PORT         GPIOB
#define SPI2_MISO_GPIO_PIN          GPIO_PIN_14
#define SPI2_MISO_GPIO_AF            GPIO_AF5_SPI2
#define SPI2_MISO_GPIO_CLK_ENABLE() do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)
#define SPI2_MOSI_GPIO_PORT         GPIOB
#define SPI2_MOSI_GPIO_PIN          GPIO_PIN_15
#define SPI2_MOSI_GPIO_AF            GPIO_AF5_SPI2
#define SPI2_MOSI_GPIO_CLK_ENABLE() do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)

/* �������� */
void spi2_init(void);                           /* ��ʼ��SPI2 */
void spi2_set_speed(uint32_t speed);            /* ����SPI2ͨ�Ų����� */
uint8_t spi2_read_write_byte(uint8_t txdata);   /* SPI2��дһ�ֽ����� */

#endif
