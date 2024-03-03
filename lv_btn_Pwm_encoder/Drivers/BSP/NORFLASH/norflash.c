/**
 ****************************************************************************************************
 * @file        norflash.c
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

#include "./BSP/NORFLASH/norflash.h"
#include "./BSP/QSPI/qspi.h"

/* QSPI��� */
extern QSPI_HandleTypeDef qspi_handle;

/**
 * @brief   ��NOR Flash��״̬�Ĵ���
 * @note    NOR Flashһ����3��״̬�Ĵ���
 *          ״̬�Ĵ���1��
 *          BIT   7   6   5   4   3   2   1   0
 *               SPR  RV  TB BP2 BP1 BP0 WEL BUSY
 *          SPR��״̬�Ĵ�������λ�����WPʹ��
 *          TB��BP2��BP1��BP0��Flash����д��������
 *          WEL��дʹ������
 *          BUSY��æ���λ��1��æ��0�����У�
 *          Ĭ�ϣ�0x00
 *          ״̬�Ĵ���2��
 *          BIT   7   6   5   4   3   2   1   0
 *               SUS CMP LB3 LB2 LB1 (R)  QE SRP1
 *          ״̬�Ĵ���3��
 *          BIT   7       6    5    4   3   2   1   0
 *             HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 * @param   regno: ״̬�Ĵ��������ţ���Χ��1~3
 * @retval  ״̬�Ĵ�����ֵ
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
            command = NORFLASH_ReadStatusReg1;  /* ��״̬�Ĵ���1ָ�� */
            break;
        }
        case 2:
        {
            command = NORFLASH_ReadStatusReg2;  /* ��״̬�Ĵ���2ָ�� */
            break;
        }
        case 3:
        {
            command = NORFLASH_ReadStatusReg3;  /* ��״̬�Ĵ���3ָ�� */
            break;
        }
        default:
        {
            command = NORFLASH_ReadStatusReg1;  /* Ĭ�϶�״̬�Ĵ���1ָ�� */
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
 * @brief   дNOR Flash��״̬�Ĵ���
 * @note    ״̬�Ĵ���1��
 *          BIT   7   6   5   4   3   2   1   0
 *               SPR  RV  TB BP2 BP1 BP0 WEL BUSY
 *          SPR��״̬�Ĵ�������λ�����WPʹ��
 *          TB��BP2��BP1��BP0��Flash����д��������
 *          WEL��дʹ������
 *          BUSY��æ���λ��1��æ��0�����У�
 *          Ĭ�ϣ�0x00
 *          ״̬�Ĵ���2��
 *          BIT   7   6   5   4   3   2   1   0
 *               SUS CMP LB3 LB2 LB1 (R)  QE SRP1
 *          ״̬�Ĵ���3��
 *          BIT   7       6    5    4   3   2   1   0
 *             HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 * @param   regno: ״̬�Ĵ��������ţ���Χ��1~3
 * @param   sr   : ��д��״̬�Ĵ�����ֵ
 * @retval  ��
 */
static void norflash_write_sr(uint8_t regno, uint8_t byte)
{
    uint8_t command;
    QSPI_CommandTypeDef qspi_command_struct = {0};
    
    switch (regno)
    {
        case 1:
        {
            command = NORFLASH_WriteStatusReg1; /* ��״̬�Ĵ���1ָ�� */
            break;
        }
        case 2:
        {
            command = NORFLASH_WriteStatusReg2; /* ��״̬�Ĵ���2ָ�� */
            break;
        }
        case 3:
        {
            command = NORFLASH_WriteStatusReg3; /* ��״̬�Ĵ���3ָ�� */
            break;
        }
        default:
        {
            command = NORFLASH_WriteStatusReg1; /* Ĭ�϶�״̬�Ĵ���1ָ�� */
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
 * @brief   дʹ��NOR Flash
 * @param   ��
 * @retval  ��
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
 * @brief   ʹ��Quad SPI����ģʽ
 * @param   ��
 * @retval  ��
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
 * @brief   ��ʼ��NOR Flash
 * @param   ��
 * @retval  ��
 */
void norflash_init(void)
{
    qspi_init();
    norflash_qspi_enable();
}

/**
 * @brief   ��NOR FlashоƬID
 * @param   ��
 * @retval  NOR FlashоƬID
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
 * @brief   ��NOR Flash
 * @note    ��ָ����ַ��ʼ��ȡָ�����ȵ�����
 * @param   pbuf   : ��ȡ�����ݱ���ĵ�ַ
 * @param   pbuf   : ָ����ʼ��ȡ�ĵ�ַ
 * @param   datalen: ָ����ȡ���ݵ��ֽ���
 * @retval  ��
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
 * @brief   NOR Flashָ����ַд��ָ�����ȵ�����
 * @note    д�����ݵĳ��Ȳ��ܳ���ָ����ַ����ҳ��ʣ���ֽ���
 * @param   pbuf   : ��д�����ݵ���ʼ��ַ
 * @param   addr   : ָ����ʼд�����ݵĵ�ַ
 * @param   datalen: ָ��д�����ݵ��ֽ�������Χ��0~ָ����ַ����ҳʣ���ֽ���
 * @retval  ��
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
 * @brief   �޼����NOR Flashָ����ַд��ָ�����ȵ�����
 * @note    ����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0xFF,�����ڷ�0xFF��д������ݽ�ʧ��
 *          �����Զ���ҳ����
 *          ��ָ����ַ��ʼд��ָ�����ȵ����ݣ�����Ҫȷ����ַ��Խ��
 * @param   pbuf   : ��д�����ݵ���ʼ��ַ
 * @param   addr   : ָ����ʼд�����ݵĵ�ַ
 * @param   datalen: ָ��д�����ݵ��ֽ���
 * @retval  ��
 */
static void norflash_write_nocheck(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t pageremain;
    
    pageremain = 256 - (addr % 256);                    /* ���㵱ǰҳʣ����ֽ��� */
    if (datalen <= pageremain)                          /* ������256���ֽ� */
    {
        pageremain = datalen;
    }
    
    /* ��д���ֽڱ�ҳ��ʣ���ַ���ٵ�ʱ��һ����д��
     * ��д��ֱ�ӱ�ҳ��ʣ���ַ�����ʱ����д������ҳ��ʣ���ַ��Ȼ�����ʣ�೤�Ƚ��в�ͬ����
     */
    while (1)
    {
        norflash_write_page(pbuf, addr, pageremain);    /* ��NOR Flashָ����ַд��ָ�����ȵ����� */
        
        if (datalen == pageremain)                      /* д����� */
        {
            break;
        }
        else                                            /* д��δ���� */
        {
            pbuf += pageremain;                         /* ƫ��pbufָ���ַpageremain����д����ֽ��� */
            addr += pageremain;                         /* ƫ��д���ַpageremain����д����ֽ��� */
            datalen -= pageremain;                      /* ����ʣ��д����ֽ��� */
            if (datalen > 256)                          /* ʣ������������256��ֻ����д��һҳ���� */
            {
                pageremain = 256;
            }
            else                                        /* ʣ��������������256����һ����д�� */
            {
                pageremain = datalen;
            }
        }
    }
}

/* �������� */
static uint8_t g_norflash_buf[4096];

/**
 * @brief   дNOR Flash
 * @note    ��ָ����ַ��ʼд��ָ�����ȵ����ݣ��ú�������������
 *          NOR Flashһ���ǣ�256���ֽ�Ϊһ��Page��4096���ֽ�Ϊһ��Sector��16��SectorΪ1��Block
 *          ��������С��λΪSector
 * @param   pbuf   : ��д�����ݵ���ʼ��ַ
 * @param   addr   : ָ����ʼд�����ݵĵ�ַ
 * @param   datalen: ָ��д�����ݵ��ֽ���
 * @retval  ��
 */
void norflash_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t *norflash_buf;
    
    norflash_buf = g_norflash_buf;                                      /* �������� */
    secpos = addr / 4096;                                               /* �������� */
    secoff = addr % 4096;                                               /* д����ʼ��ַ�ڵ�ǰ������ƫ���� */
    secremain = 4096 - secoff;                                          /* ���㵱����ʣ����ֽ��� */
    if (datalen <= secremain)                                           /* ������4096���ֽ� */
    {
        secremain = datalen;
    }
    
    while (1)
    {
        norflash_read(norflash_buf, secpos * 4096, 4096);               /* ������ǰ�������������ݣ����ڲ���������ָ���д����������� */
        
        for (i=0; i<secremain; i++)                                     /* У������ */
        {
            if (norflash_buf[secoff + i] != 0xFF)                       /* д���������з�0xFF�����ݣ�����Ҫ���� */
            {
                break;
            }
        }
        
        if (i < secremain)                                              /* ��Ҫ���� */
        {
            norflash_erase_sector(secpos);                              /* ������������ */
            
            for (i=0; i<secremain; i++)                                 /* ����д������ݣ���д���������� */
            {
                norflash_buf[i + secoff] = pbuf[i];
            }
            
            norflash_write_nocheck(norflash_buf, secpos * 4096, 4096);  /* д���������� */
        }
        else                                                            /* ����Ҫ����������ֱ��д�� */
        {
            norflash_write_nocheck(pbuf, addr, secremain);              /* ֱ��д����ʣ��Ŀռ� */
        }
        
        if (datalen == secremain)                                       /* д����� */
        {
            break;
        }
        else                                                            /* д��δ���� */
        {
            secpos++;                                                   /* ����������1 */
            secoff = 0;                                                 /* ����ƫ��λ��Ϊ0 */
            pbuf += secremain;                                          /* ƫ��pbufָ���ַsecremain����д����ֽ��� */
            addr += secremain;                                          /* ƫ��д���ַsecremain����д����ֽ��� */
            datalen -= secremain;                                       /* ����ʣ��д����ֽ��� */
            if (datalen > 4096)                                         /* ʣ������������4096��ֻ����д��һ���������� */
            {
                secremain = 4096;
            }
            else                                                        /* ʣ��������������4096����һ����д�� */
            {
                secremain = datalen;
            }
        }
    }
}

/**
 * @brief   ��������NOR FlashоƬ
 * @param   ��
 * @retval  ��
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
 * @brief   ����NOR Flashһ������
 * @param   saddr: ���������ţ����ֽڵ�ַ������Χ������ʵ��W25QXX����ȷ��
 * @retval  ��
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
