/**
 ****************************************************************************************************
 * @file        norflash.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-12
 * @brief       NOR Flash驱动代码
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

#include "./BSP/NORFLASH/norflash.h"
#include "./BSP/QSPI/qspi.h"

/* QSPI句柄 */
extern QSPI_HandleTypeDef qspi_handle;

/**
 * @brief   读NOR Flash的状态寄存器
 * @note    NOR Flash一共有3个状态寄存器
 *          状态寄存器1：
 *          BIT   7   6   5   4   3   2   1   0
 *               SPR  RV  TB BP2 BP1 BP0 WEL BUSY
 *          SPR：状态寄存器保护位，配合WP使用
 *          TB、BP2、BP1、BP0：Flash区域写保护设置
 *          WEL：写使能锁定
 *          BUSY：忙标记位（1：忙；0：空闲）
 *          默认：0x00
 *          状态寄存器2：
 *          BIT   7   6   5   4   3   2   1   0
 *               SUS CMP LB3 LB2 LB1 (R)  QE SRP1
 *          状态寄存器3：
 *          BIT   7       6    5    4   3   2   1   0
 *             HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 * @param   regno: 状态寄存器索引号，范围：1~3
 * @retval  状态寄存器的值
 */
static uint8_t norflash_read_sr(uint8_t regno)
{
    uint8_t byte;
    uint8_t command;
    QSPI_CommandTypeDef qspi_command_struct = {0};
    
    switch (regno)
    {
        case 1:
        {
            command = NORFLASH_ReadStatusReg1;  /* 读状态寄存器1指令 */
            break;
        }
        case 2:
        {
            command = NORFLASH_ReadStatusReg2;  /* 读状态寄存器2指令 */
            break;
        }
        case 3:
        {
            command = NORFLASH_ReadStatusReg3;  /* 读状态寄存器3指令 */
            break;
        }
        default:
        {
            command = NORFLASH_ReadStatusReg1;  /* 默认读状态寄存器1指令 */
            break;
        }
    }
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = command;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.NbData = 1;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&qspi_handle, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    HAL_QSPI_Receive(&qspi_handle, &byte, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    return byte;
}

/**
 * @brief   写NOR Flash的状态寄存器
 * @note    状态寄存器1：
 *          BIT   7   6   5   4   3   2   1   0
 *               SPR  RV  TB BP2 BP1 BP0 WEL BUSY
 *          SPR：状态寄存器保护位，配合WP使用
 *          TB、BP2、BP1、BP0：Flash区域写保护设置
 *          WEL：写使能锁定
 *          BUSY：忙标记位（1：忙；0：空闲）
 *          默认：0x00
 *          状态寄存器2：
 *          BIT   7   6   5   4   3   2   1   0
 *               SUS CMP LB3 LB2 LB1 (R)  QE SRP1
 *          状态寄存器3：
 *          BIT   7       6    5    4   3   2   1   0
 *             HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 * @param   regno: 状态寄存器索引号，范围：1~3
 * @param   sr   : 待写入状态寄存器的值
 * @retval  无
 */
static void norflash_write_sr(uint8_t regno, uint8_t byte)
{
    uint8_t command;
    QSPI_CommandTypeDef qspi_command_struct = {0};
    
    switch (regno)
    {
        case 1:
        {
            command = NORFLASH_WriteStatusReg1; /* 读状态寄存器1指令 */
            break;
        }
        case 2:
        {
            command = NORFLASH_WriteStatusReg2; /* 读状态寄存器2指令 */
            break;
        }
        case 3:
        {
            command = NORFLASH_WriteStatusReg3; /* 读状态寄存器3指令 */
            break;
        }
        default:
        {
            command = NORFLASH_WriteStatusReg1; /* 默认读状态寄存器1指令 */
            break;
        }
    }
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = command;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.NbData = 1;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&qspi_handle, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    HAL_QSPI_Transmit(&qspi_handle, &byte, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
}

/**
 * @brief   写使能NOR Flash
 * @param   无
 * @retval  无
 */
static void norflash_write_enable(void)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    QSPI_AutoPollingTypeDef qspi_autopolling_struct = {0};
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_WriteEnable;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&qspi_handle, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_ReadStatusReg1;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    qspi_autopolling_struct.Match = 0x02;
    qspi_autopolling_struct.Mask = 0x02;
    qspi_autopolling_struct.Interval = 0x10;
    qspi_autopolling_struct.StatusBytesSize = 1;
    qspi_autopolling_struct.MatchMode = QSPI_MATCH_MODE_AND;
    qspi_autopolling_struct.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
    HAL_QSPI_AutoPolling(&qspi_handle, &qspi_command_struct, &qspi_autopolling_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
}

/**
 * @brief   使能Quad SPI操作模式
 * @param   无
 * @retval  无
 */
static void norflash_qspi_enable(void)
{
    uint8_t stareg2;
    
    stareg2 = norflash_read_sr(2);
    if ((stareg2 & (1 << 1)) == 0)
    {
        stareg2 |= (1 << 1);
        norflash_write_enable();
        norflash_write_sr(2, stareg2);
    }
}

/**
 * @brief   初始化NOR Flash
 * @param   无
 * @retval  无
 */
void norflash_init(void)
{
    qspi_init();
    norflash_qspi_enable();
}

/**
 * @brief   读NOR Flash芯片ID
 * @param   无
 * @retval  NOR Flash芯片ID
 */
uint16_t norflash_read_id(void)
{
    uint8_t id[2];
    QSPI_CommandTypeDef qspi_command_struct = {0};
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_ManufactDeviceID;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_command_struct.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_command_struct.Address = 0x000000;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.NbData = 2;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&qspi_handle, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    HAL_QSPI_Receive(&qspi_handle, id, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    return (((uint16_t)id[0] << 8) | id[1]);
}

/**
 * @brief   读NOR Flash
 * @note    从指定地址开始读取指定长度的数据
 * @param   pbuf   : 读取到数据保存的地址
 * @param   pbuf   : 指定开始读取的地址
 * @param   datalen: 指定读取数据的字节数
 * @retval  无
 */
void norflash_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_FastReadQuadIO;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_4_LINES;
    qspi_command_struct.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_command_struct.Address = addr;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 6;
    qspi_command_struct.DataMode = QSPI_DATA_4_LINES;
    qspi_command_struct.NbData = datalen;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&qspi_handle, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    HAL_QSPI_Receive(&qspi_handle, pbuf, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
}

/**
 * @brief   NOR Flash指定地址写入指定长度的数据
 * @note    写入数据的长度不能超过指定地址所在页的剩余字节数
 * @param   pbuf   : 待写入数据的起始地址
 * @param   addr   : 指定开始写入数据的地址
 * @param   datalen: 指定写入数据的字节数，范围：0~指定地址所在页剩余字节数
 * @retval  无
 */
static void norflash_write_page(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    QSPI_AutoPollingTypeDef qspi_autopolling_struct = {0};
    
    norflash_write_enable();
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_PageProgram;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_command_struct.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_command_struct.Address = addr;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.NbData = datalen;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&qspi_handle, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    HAL_QSPI_Transmit(&qspi_handle, pbuf, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_ReadStatusReg1;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    qspi_autopolling_struct.Match = 0x00;
    qspi_autopolling_struct.Mask = 0x01;
    qspi_autopolling_struct.Interval = 0x10;
    qspi_autopolling_struct.StatusBytesSize = 1;
    qspi_autopolling_struct.MatchMode = QSPI_MATCH_MODE_AND;
    qspi_autopolling_struct.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
    HAL_QSPI_AutoPolling(&qspi_handle, &qspi_command_struct, &qspi_autopolling_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
}

/**
 * @brief   无检验从NOR Flash指定地址写入指定长度的数据
 * @note    必须确保所写的地址范围内的数据全部为0xFF,否则在非0xFF处写入的数据将失败
 *          具有自动换页功能
 *          在指定地址开始写入指定长度的数据，但是要确保地址不越界
 * @param   pbuf   : 待写入数据的起始地址
 * @param   addr   : 指定开始写入数据的地址
 * @param   datalen: 指定写入数据的字节数
 * @retval  无
 */
static void norflash_write_nocheck(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t pageremain;
    
    pageremain = 256 - (addr % 256);                    /* 计算当前页剩余的字节数 */
    if (datalen <= pageremain)                          /* 不大于256个字节 */
    {
        pageremain = datalen;
    }
    
    /* 当写入字节比页内剩余地址还少的时候，一次性写完
     * 当写入直接比页内剩余地址还多的时候，先写完整个页内剩余地址，然后根据剩余长度进行不同处理
     */
    while (1)
    {
        norflash_write_page(pbuf, addr, pageremain);    /* 从NOR Flash指定地址写入指定长度的数据 */
        
        if (datalen == pageremain)                      /* 写入结束 */
        {
            break;
        }
        else                                            /* 写入未结束 */
        {
            pbuf += pageremain;                         /* 偏移pbuf指针地址pageremain个已写入的字节数 */
            addr += pageremain;                         /* 偏移写入地址pageremain个已写入的字节数 */
            datalen -= pageremain;                      /* 计算剩余写入的字节数 */
            if (datalen > 256)                          /* 剩余数据量超过256，只能先写入一页数据 */
            {
                pageremain = 256;
            }
            else                                        /* 剩余数据量不超过256，可一次性写入 */
            {
                pageremain = datalen;
            }
        }
    }
}

/* 扇区缓存 */
static uint8_t g_norflash_buf[4096];

/**
 * @brief   写NOR Flash
 * @note    在指定地址开始写入指定长度的数据，该函数带擦除操作
 *          NOR Flash一般是：256个字节为一个Page，4096个字节为一个Sector，16个Sector为1个Block
 *          擦除的最小单位为Sector
 * @param   pbuf   : 待写入数据的起始地址
 * @param   addr   : 指定开始写入数据的地址
 * @param   datalen: 指定写入数据的字节数
 * @retval  无
 */
void norflash_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t *norflash_buf;
    
    norflash_buf = g_norflash_buf;                                      /* 扇区缓存 */
    secpos = addr / 4096;                                               /* 扇区索引 */
    secoff = addr % 4096;                                               /* 写入起始地址在当前扇区的偏移量 */
    secremain = 4096 - secoff;                                          /* 计算当扇区剩余的字节数 */
    if (datalen <= secremain)                                           /* 不大于4096个字节 */
    {
        secremain = datalen;
    }
    
    while (1)
    {
        norflash_read(norflash_buf, secpos * 4096, 4096);               /* 读出当前整个扇区的内容，用于擦除扇区后恢复非写入区域的数据 */
        
        for (i=0; i<secremain; i++)                                     /* 校验数据 */
        {
            if (norflash_buf[secoff + i] != 0xFF)                       /* 写入区域中有非0xFF的数据，就需要擦除 */
            {
                break;
            }
        }
        
        if (i < secremain)                                              /* 需要擦除 */
        {
            norflash_erase_sector(secpos);                              /* 擦除整个扇区 */
            
            for (i=0; i<secremain; i++)                                 /* 将待写入的数据，先写入扇区缓存 */
            {
                norflash_buf[i + secoff] = pbuf[i];
            }
            
            norflash_write_nocheck(norflash_buf, secpos * 4096, 4096);  /* 写入整个扇区 */
        }
        else                                                            /* 不需要擦除，可以直接写入 */
        {
            norflash_write_nocheck(pbuf, addr, secremain);              /* 直接写扇区剩余的空间 */
        }
        
        if (datalen == secremain)                                       /* 写入结束 */
        {
            break;
        }
        else                                                            /* 写入未结束 */
        {
            secpos++;                                                   /* 扇区索引增1 */
            secoff = 0;                                                 /* 扇区偏移位置为0 */
            pbuf += secremain;                                          /* 偏移pbuf指针地址secremain个已写入的字节数 */
            addr += secremain;                                          /* 偏移写入地址secremain个已写入的字节数 */
            datalen -= secremain;                                       /* 计算剩余写入的字节数 */
            if (datalen > 4096)                                         /* 剩余数据量超过4096，只能先写入一个扇区数据 */
            {
                secremain = 4096;
            }
            else                                                        /* 剩余数据量不超过4096，可一次性写入 */
            {
                secremain = datalen;
            }
        }
    }
}

/**
 * @brief   擦除整个NOR Flash芯片
 * @param   无
 * @retval  无
 */
void norflash_erase_chip(void)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    QSPI_AutoPollingTypeDef qspi_autopolling_struct = {0};
    
    norflash_write_enable();
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_ChipErase;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&qspi_handle, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_ReadStatusReg1;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    qspi_autopolling_struct.Match = 0x00;
    qspi_autopolling_struct.Mask = 0x01;
    qspi_autopolling_struct.Interval = 0x10;
    qspi_autopolling_struct.StatusBytesSize = 1;
    qspi_autopolling_struct.MatchMode = QSPI_MATCH_MODE_AND;
    qspi_autopolling_struct.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
    HAL_QSPI_AutoPolling(&qspi_handle, &qspi_command_struct, &qspi_autopolling_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
}

/**
 * @brief   擦除NOR Flash一个扇区
 * @param   saddr: 扇区索引号（非字节地址），范围：根据实际W25QXX容量确定
 * @retval  无
 */
void norflash_erase_sector(uint32_t saddr)
{
    QSPI_CommandTypeDef qspi_command_struct = {0};
    QSPI_AutoPollingTypeDef qspi_autopolling_struct = {0};
    
    norflash_write_enable();
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_SectorErase;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_1_LINE;
    qspi_command_struct.AddressSize = QSPI_ADDRESS_24_BITS;
    qspi_command_struct.Address = saddr << 12;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_NONE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    HAL_QSPI_Command(&qspi_handle, &qspi_command_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
    
    qspi_command_struct.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    qspi_command_struct.Instruction = NORFLASH_ReadStatusReg1;
    qspi_command_struct.AddressMode = QSPI_ADDRESS_NONE;
    qspi_command_struct.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    qspi_command_struct.DummyCycles = 0;
    qspi_command_struct.DataMode = QSPI_DATA_1_LINE;
    qspi_command_struct.DdrMode = QSPI_DDR_MODE_DISABLE;
    qspi_command_struct.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    qspi_command_struct.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    qspi_autopolling_struct.Match = 0x00;
    qspi_autopolling_struct.Mask = 0x01;
    qspi_autopolling_struct.Interval = 0x10;
    qspi_autopolling_struct.StatusBytesSize = 1;
    qspi_autopolling_struct.MatchMode = QSPI_MATCH_MODE_AND;
    qspi_autopolling_struct.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
    HAL_QSPI_AutoPolling(&qspi_handle, &qspi_command_struct, &qspi_autopolling_struct, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
}
