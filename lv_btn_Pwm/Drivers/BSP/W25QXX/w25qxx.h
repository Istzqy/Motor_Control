/**
 ****************************************************************************************************
 * @file        w25qxx.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       W25QXX��������
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

#ifndef __W25QXX_H
#define __W25QXX_H

#include "./SYSTEM/sys/sys.h"

/* ���Ŷ��� */
#define W25QXX_CS_GPIO_PORT         GPIOF
#define W25QXX_CS_GPIO_PIN          GPIO_PIN_10
#define W25QXX_CS_GPIO_CLK_ENABLE() do { __HAL_RCC_GPIOF_CLK_ENABLE(); } while (0)

/* IO���� */
#define W25QXX_CS(x)                do { (x) ?                                                                      \
                                        HAL_GPIO_WritePin(W25QXX_CS_GPIO_PORT, W25QXX_CS_GPIO_PIN, GPIO_PIN_SET):   \
                                        HAL_GPIO_WritePin(W25QXX_CS_GPIO_PORT, W25QXX_CS_GPIO_PIN, GPIO_PIN_RESET); \
                                    } while (0)

/* W25QXXоƬID���� */
#define W25Q80                      0xEF13
#define W25Q16                      0xEF14
#define W25Q32                      0xEF15
#define W25Q64                      0xEF16
#define W25Q128                     0xEF17
#define W25Q256                     0xEF18

/* W25QXXָ��� */
#define W25QXX_WriteEnable          0x06
#define W25QXX_WriteDisable         0x04
#define W25QXX_ReadStatusReg1       0x05
#define W25QXX_ReadStatusReg2       0x35
#define W25QXX_ReadStatusReg3       0x15
#define W25QXX_WriteStatusReg1      0x01
#define W25QXX_WriteStatusReg2      0x31
#define W25QXX_WriteStatusReg3      0x11
#define W25QXX_ReadData             0x03
#define W25QXX_FastReadData         0x0B
#define W25QXX_FastReadDual         0x3B
#define W25QXX_FastReadQuad         0xEB
#define W25QXX_PageProgram          0x02
#define W25QXX_PageProgramQuad      0x32
#define W25QXX_BlockErase           0xD8
#define W25QXX_SectorErase          0x20
#define W25QXX_ChipErase            0xC7
#define W25QXX_PowerDown            0xB9
#define W25QXX_ReleasePowerDown     0xAB
#define W25QXX_DeviceID             0xAB
#define W25QXX_ManufactDeviceID     0x90
#define W25QXX_JedecDeviceID        0x9F
#define W25QXX_Enable4ByteAddr      0xB7
#define W25QXX_Exit4ByteAddr        0xE9
#define W25QXX_SetReadParam         0xC0
#define W25QXX_EnterQPIMode         0x38
#define W25QXX_ExitQPIMode          0xFF

/* �������� */
void w25qxx_init(void);                                             /* ��ʼ��W25QXX */
void w25qxx_write_enable(void);                                     /* дʹ��W25QXX */
uint8_t w25qxx_read_sr(uint8_t regno);                              /* ��W25QXX��״̬�Ĵ��� */
void w25qxx_write_sr(uint8_t regno, uint8_t sr);                    /* дW25QXX��״̬�Ĵ��� */
uint16_t w25qxx_read_id(void);                                      /* ��W25QXXоƬID */
void w25qxx_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen);   /* ��W25QXX */
void w25qxx_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen);  /* дW25QXX */
void w25qxx_erase_chip(void);                                       /* ��������W25QXXоƬ */
void w25qxx_erase_sector(uint32_t saddr);                           /* ����W25QXXһ������ */

#endif
