/**
 ****************************************************************************************************
 * @file        qspi.h
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

#ifndef __QSPI_H
#define __QSPI_H

#include "./SYSTEM/sys/sys.h"

/* 引脚定义 */
#define QSPI_CLK_GPIO_PORT              GPIOB
#define QSPI_CLK_GPIO_PIN               GPIO_PIN_2
#define QSPI_CLK_GPIO_AF                GPIO_AF9_QUADSPI
#define QSPI_CLK_GPIO_CLK_ENABLE()      do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)
#define QSPI_BK1_NCS_GPIO_PORT          GPIOB
#define QSPI_BK1_NCS_GPIO_PIN           GPIO_PIN_6
#define QSPI_BK1_NCS_GPIO_AF            GPIO_AF10_QUADSPI
#define QSPI_BK1_NCS_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)
#define QSPI_BK1_IO0_GPIO_PORT          GPIOF
#define QSPI_BK1_IO0_GPIO_PIN           GPIO_PIN_8
#define QSPI_BK1_IO0_GPIO_AF            GPIO_AF10_QUADSPI
#define QSPI_BK1_IO0_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOF_CLK_ENABLE(); } while (0)
#define QSPI_BK1_IO1_GPIO_PORT          GPIOF
#define QSPI_BK1_IO1_GPIO_PIN           GPIO_PIN_9
#define QSPI_BK1_IO1_GPIO_AF            GPIO_AF10_QUADSPI
#define QSPI_BK1_IO1_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOF_CLK_ENABLE(); } while (0)
#define QSPI_BK1_IO2_GPIO_PORT          GPIOF
#define QSPI_BK1_IO2_GPIO_PIN           GPIO_PIN_7
#define QSPI_BK1_IO2_GPIO_AF            GPIO_AF9_QUADSPI
#define QSPI_BK1_IO2_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOF_CLK_ENABLE(); } while (0)
#define QSPI_BK1_IO3_GPIO_PORT          GPIOF
#define QSPI_BK1_IO3_GPIO_PIN           GPIO_PIN_6
#define QSPI_BK1_IO3_GPIO_AF            GPIO_AF9_QUADSPI
#define QSPI_BK1_IO3_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOF_CLK_ENABLE(); } while (0)

/* 函数声明 */
void qspi_init(void);   /* 初始化QSPI */

#endif
