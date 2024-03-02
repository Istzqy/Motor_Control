/**
 ****************************************************************************************************
 * @file        sdram.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       SDRAM��������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
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

#ifndef __SDRAM_H
#define __SDRAM_H

#include "./SYSTEM/sys/sys.h"

/* SDRAM���ַ���� */
#define SDRAM_BANK_ADDR (0xC0000000UL)

/* �������� */
void sdram_init(void);

#endif