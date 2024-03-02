/**
 ****************************************************************************************************
 * @file        norflash.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       NOR Flash��������
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

#ifndef __NORFLASH_H
#define __NORFLASH_H

#include "./SYSTEM/sys/sys.h"

/* NOR FlashоƬID���� */
#define W25Q80                      0xEF13
#define W25Q16                      0xEF14
#define W25Q32                      0xEF15
#define W25Q64                      0xEF16
#define W25Q128                     0xEF17
#define W25Q256                     0xEF18

/* NOR Flashָ��� */
#define NORFLASH_WriteEnable        0x06
#define NORFLASH_ReadStatusReg1     0x05
#define NORFLASH_ReadStatusReg2     0x35
#define NORFLASH_ReadStatusReg3     0x15
#define NORFLASH_WriteStatusReg1    0x01
#define NORFLASH_WriteStatusReg2    0x31
#define NORFLASH_WriteStatusReg3    0x11
#define NORFLASH_ManufactDeviceID   0x90
#define NORFLASH_FastReadQuadIO     0xEB
#define NORFLASH_PageProgram        0x02
#define NORFLASH_ChipErase          0xC7
#define NORFLASH_SectorErase        0x20

/* �������� */
void norflash_init(void);                                               /* ��ʼ��NOR Flash */
uint16_t norflash_read_id(void);                                        /* ��NOR FlashоƬID */
void norflash_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen);     /* ��NOR Flash */
void norflash_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen);    /* дNOR Flash */
void norflash_erase_chip(void);                                         /* ��������NOR FlashоƬ */
void norflash_erase_sector(uint32_t saddr);                             /* ����NOR Flashһ������ */

#endif
