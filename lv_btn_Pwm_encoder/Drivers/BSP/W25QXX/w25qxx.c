/**
 ****************************************************************************************************
 * @file        w25qxx.c
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

#include "./BSP/W25QXX/w25qxx.h"
#include "./BSP/SPI/spi.h"

uint16_t g_w25qxx_type;

/**
 * @brief   ��ʼ��W25QXX
 * @param   ��
 * @retval  ��
 */
void w25qxx_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    uint8_t temp;
    
    /* ʱ��ʹ�� */
    W25QXX_CS_GPIO_CLK_ENABLE();
    
    /* ����CS���� */
    gpio_init_struct.Pin = W25QXX_CS_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(W25QXX_CS_GPIO_PORT, &gpio_init_struct);
    W25QXX_CS(1);
    
    /* ����SPI�ӿ� */
    spi2_init();
    spi2_set_speed(SPI_BAUDRATEPRESCALER_2);
    
    g_w25qxx_type = w25qxx_read_id();                       /* ��ȡW25QXXоƬID */
    if (g_w25qxx_type == W25Q256)                           /* W25Q256��ʹ��4�ֽڵ�ַģʽ */
    {
        temp = w25qxx_read_sr(3);                           /* ��״̬�Ĵ���3���жϵ�ַģʽ */
        if ((temp & 0x01) == 0)                             /* �������4�ֽڵ�ַģʽ�����������Ӧ���� */
        {
            w25qxx_write_enable();                          /* W25QXXдʹ�� */
            temp |= (1 << 1);                               /* ADP=1�������ϵ�4�ֽڵ�ַģʽ */
            w25qxx_write_sr(3, temp);                       /* д״̬�Ĵ���3 */
            
            W25QXX_CS(0);                                   /* ʹ��W25QXXƬѡ */
            spi2_read_write_byte(W25QXX_Enable4ByteAddr);   /* ʹ��4�ֽڵ�ַģʽ */
            W25QXX_CS(1);                                   /* ʧ��W25QXXƬѡ */
        }
    }
}

/**
 * @brief   �ȴ�W25QXX����
 * @param   ��
 * @retval  ��
 */
static void w25qxx_wait_busy(void)
{
    while ((w25qxx_read_sr(1) & 0x01) == 0x01); /* �ȴ�BUSYλ���� */
}

/**
 * @brief   дʹ��W25QXX
 * @note    ��S1�Ĵ�����WEL��λ
 * @param   ��
 * @retval  ��
 */
void w25qxx_write_enable(void)
{
    W25QXX_CS(0);                               /* ʹ��W25QXXƬѡ */
    spi2_read_write_byte(W25QXX_WriteEnable);   /* ����дʹ������ */
    W25QXX_CS(1);                               /* ʧ��W25QXXƬѡ */
}

/**
 * @brief   ��W25QXX���͵�ַ
 * @note    ����оƬ�ͺŵĲ�ͬ������3�ֽڻ�4�ֽڵ�ַ
 * @param   address: �����͵ĵ�ַ
 * @retval  ��
 */
static void w25qxx_send_address(uint32_t address)
{
    if (g_w25qxx_type == W25Q256)                       /* ֻ��W25Q256֧��4�ֽڵ�ַģʽ */
    {
        spi2_read_write_byte((uint8_t)(address >> 24)); /* ����bit31~bit24��ַ */
    }
    spi2_read_write_byte((uint8_t)(address >> 16));     /* ����bit23~bit16��ַ */
    spi2_read_write_byte((uint8_t)(address >> 8));      /* ����bit15~ bit8��ַ */
    spi2_read_write_byte((uint8_t)address);             /* ���� bit7~ bit0��ַ */
}

/**
 * @brief   ��W25QXX��״̬�Ĵ���
 * @note    W25QXXһ����3��״̬�Ĵ���
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
uint8_t w25qxx_read_sr(uint8_t regno)
{
    uint8_t byte;
    uint8_t command;
    
    switch (regno)
    {
        case 1:
        {
            command = W25QXX_ReadStatusReg1;    /* ��״̬�Ĵ���1ָ�� */
            break;
        }
        case 2:
        {
            command = W25QXX_ReadStatusReg2;    /* ��״̬�Ĵ���2ָ�� */
            break;
        }
        case 3:
        {
            command = W25QXX_ReadStatusReg3;    /* ��״̬�Ĵ���3ָ�� */
            break;
        }
        default:
        {
            command = W25QXX_ReadStatusReg1;    /* Ĭ�϶�״̬�Ĵ���1ָ�� */
            break;
        }
    }
    
    W25QXX_CS(0);                               /* ʹ��W25QXXƬѡ */
    spi2_read_write_byte(command);              /* ���Ͷ��Ĵ������� */
    byte = spi2_read_write_byte(0xFF);          /* ��ȡһ���ֽ� */
    W25QXX_CS(1);                               /* ʧ��W25QXXƬѡ */
    
    return byte;
}

/**
 * @brief   дW25QXX��״̬�Ĵ���
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
void w25qxx_write_sr(uint8_t regno, uint8_t sr)
{
    uint8_t command;
    
    switch (regno)
    {
        case 1:
        {
            command = W25QXX_WriteStatusReg1;   /* д״̬�Ĵ���1ָ�� */
            break;
        }
        case 2:
        {
            command = W25QXX_WriteStatusReg2;   /* д״̬�Ĵ���2ָ�� */
            break;
        }
        case 3:
        {
            command = W25QXX_WriteStatusReg3;   /* д״̬�Ĵ���3ָ�� */
            break;
        }
        default:
        {
            command = W25QXX_WriteStatusReg1;   /* Ĭ��д״̬�Ĵ���1ָ�� */
            break;
        }
    }
    
    W25QXX_CS(0);                               /* ʹ��W25QXXƬѡ */
    spi2_read_write_byte(command);              /* ���Ͷ��Ĵ������� */
    spi2_read_write_byte(sr);                   /* д��һ���ֽ� */
    W25QXX_CS(1);                               /* ʧ��W25QXXƬѡ */
}

/**
 * @brief   ��W25QXXоƬID
 * @note    W25QXXоƬID������ļ�w25qxx.h��W25QXXоƬID���岿��
 * @param   ��
 * @retval  W25QXXоƬID
 */
uint16_t w25qxx_read_id(void)
{
    uint16_t deviceid;
    
    W25QXX_CS(0);                                   /* ʹ��W25QXXƬѡ */
    spi2_read_write_byte(W25QXX_ManufactDeviceID);  /* ���Ͷ�ID���� */
    spi2_read_write_byte(0);                        /* д��һ���ֽ� */
    spi2_read_write_byte(0);
    spi2_read_write_byte(0);
    deviceid = spi2_read_write_byte(0xFF) << 8;     /* ��ȡ��8λ�ֽ� */
    deviceid |= spi2_read_write_byte(0xFF);         /* ��ȡ��8λ�ֽ� */
    W25QXX_CS(1);                                   /* ʧ��W25QXXƬѡ */
    
    return deviceid;
}

/**
 * @brief   ��W25QXX
 * @note    ��ָ����ַ��ʼ��ȡָ�����ȵ�����
 * @param   pbuf   : ��ȡ�����ݱ���ĵ�ַ
 * @param   pbuf   : ָ����ʼ��ȡ�ĵ�ַ
 * @param   datalen: ָ����ȡ���ݵ��ֽ���
 * @retval  ��
 */
void w25qxx_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;
    
    W25QXX_CS(0);                               /* ʹ��W25QXXƬѡ */
    spi2_read_write_byte(W25QXX_ReadData);      /* ���Ͷ�ȡ���� */
    w25qxx_send_address(addr);                  /* ���͵�ַ */
    for (i=0; i<datalen; i++)                   /* ѭ����ȡ */
    {
        pbuf[i] = spi2_read_write_byte(0xFF);
    }
    W25QXX_CS(1);                               /* ʧ��W25QXXƬѡ */
}

/**
 * @brief   ��W25QXXָ����ַд��ָ�����ȵ�����
 * @note    д�����ݵĳ��Ȳ��ܳ���ָ����ַ����ҳ��ʣ���ֽ���
 * @param   pbuf   : ��д�����ݵ���ʼ��ַ
 * @param   addr   : ָ����ʼд�����ݵĵ�ַ
 * @param   datalen: ָ��д�����ݵ��ֽ�������Χ��0~ָ����ַ����ҳʣ���ֽ���
 * @retval  ��
 */
static void w25qxx_write_page(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;
    
    w25qxx_write_enable();                      /* W25QXXдʹ�� */
    
    W25QXX_CS(0);                               /* ʹ��W25QXXƬѡ */
    spi2_read_write_byte(W25QXX_PageProgram);   /* ����дҳ���� */
    w25qxx_send_address(addr);                  /* ���͵�ַ */
    for (i = 0; i < datalen; i++)               /* ѭ��д�� */
    {
        spi2_read_write_byte(pbuf[i]);
    }
    W25QXX_CS(1);                               /* ʧ��W25QXXƬѡ */
    
    w25qxx_wait_busy();                         /* �ȴ�д����� */
}

/**
 * @brief   �޼����W25QXXָ����ַд��ָ�����ȵ�����
 * @note    ����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0xFF,�����ڷ�0xFF��д������ݽ�ʧ��
 *          �����Զ���ҳ����
 *          ��ָ����ַ��ʼд��ָ�����ȵ����ݣ�����Ҫȷ����ַ��Խ��
 * @param   pbuf   : ��д�����ݵ���ʼ��ַ
 * @param   addr   : ָ����ʼд�����ݵĵ�ַ
 * @param   datalen: ָ��д�����ݵ��ֽ���
 * @retval  ��
 */
static void w25qxx_write_nocheck(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t pageremain;
    
    pageremain = 256 - (addr % 256);                /* ���㵱ǰҳʣ����ֽ��� */
    if (datalen <= pageremain)                      /* ������256���ֽ� */
    {
        pageremain = datalen;
    }
    
    /* ��д���ֽڱ�ҳ��ʣ���ַ���ٵ�ʱ��һ����д��
     * ��д��ֱ�ӱ�ҳ��ʣ���ַ�����ʱ����д������ҳ��ʣ���ַ��Ȼ�����ʣ�೤�Ƚ��в�ͬ����
     */
    while (1)
    {
        w25qxx_write_page(pbuf, addr, pageremain);  /* ��W25QXXָ����ַд��ָ�����ȵ����� */
        
        if (datalen == pageremain)                  /* д����� */
        {
            break;
        }
        else                                        /* д��δ���� */
        {
            pbuf += pageremain;                     /* ƫ��pbufָ���ַpageremain����д����ֽ��� */
            addr += pageremain;                     /* ƫ��д���ַpageremain����д����ֽ��� */
            datalen -= pageremain;                  /* ����ʣ��д����ֽ��� */
            if (datalen > 256)                      /* ʣ������������256��ֻ����д��һҳ���� */
            {
                pageremain = 256;
            }
            else                                    /* ʣ��������������256����һ����д�� */
            {
                pageremain = datalen;
            }
        }
    }
}

/* �������� */
static uint8_t g_w25qxx_buf[4096];

/**
 * @brief   дW25QXX
 * @note    ��ָ����ַ��ʼд��ָ�����ȵ����ݣ��ú�������������
 *          W25QXXһ���ǣ�256���ֽ�Ϊһ��Page��4096���ֽ�Ϊһ��Sector��16��SectorΪ1��Block
 *          ��������С��λΪSector
 * @param   pbuf   : ��д�����ݵ���ʼ��ַ
 * @param   addr   : ָ����ʼд�����ݵĵ�ַ
 * @param   datalen: ָ��д�����ݵ��ֽ���
 * @retval  ��
 */
void w25qxx_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t *w25qxx_buf;
    
    w25qxx_buf = g_w25qxx_buf;                                      /* �������� */
    secpos = addr / 4096;                                           /* �������� */
    secoff = addr % 4096;                                           /* д����ʼ��ַ�ڵ�ǰ������ƫ���� */
    secremain = 4096 - secoff;                                      /* ���㵱����ʣ����ֽ��� */
    if (datalen <= secremain)                                       /* ������4096���ֽ� */
    {
        secremain = datalen;
    }
    
    while (1)
    {
        w25qxx_read(w25qxx_buf, secpos * 4096, 4096);               /* ������ǰ�������������ݣ����ڲ���������ָ���д����������� */
        
        for (i=0; i<secremain; i++)                                 /* У������ */
        {
            if (w25qxx_buf[secoff + i] != 0xFF)                     /* д���������з�0xFF�����ݣ�����Ҫ���� */
            {
                break;
            }
        }
        
        if (i < secremain)                                          /* ��Ҫ���� */
        {
            w25qxx_erase_sector(secpos);                            /* ������������ */
            
            for (i=0; i<secremain; i++)                             /* ����д������ݣ���д���������� */
            {
                w25qxx_buf[i + secoff] = pbuf[i];
            }
            
            w25qxx_write_nocheck(w25qxx_buf, secpos * 4096, 4096);  /* д���������� */
        }
        else                                                        /* ����Ҫ����������ֱ��д�� */
        {
            w25qxx_write_nocheck(pbuf, addr, secremain);            /* ֱ��д����ʣ��Ŀռ� */
        }
        
        if (datalen == secremain)                                   /* д����� */
        {
            break;
        }
        else                                                        /* д��δ���� */
        {
            secpos++;                                               /* ����������1 */
            secoff = 0;                                             /* ����ƫ��λ��Ϊ0 */
            pbuf += secremain;                                      /* ƫ��pbufָ���ַsecremain����д����ֽ��� */
            addr += secremain;                                      /* ƫ��д���ַsecremain����д����ֽ��� */
            datalen -= secremain;                                   /* ����ʣ��д����ֽ��� */
            if (datalen > 4096)                                     /* ʣ������������4096��ֻ����д��һ���������� */
            {
                secremain = 4096;
            }
            else                                                    /* ʣ��������������4096����һ����д�� */
            {
                secremain = datalen;
            }
        }
    }
}

/**
 * @brief   ��������W25QXXоƬ
 * @note    �ȴ�ʱ�䳬��
 * @param   ��
 * @retval  ��
 */
void w25qxx_erase_chip(void)
{
    w25qxx_write_enable();                  /* W25QXXдʹ�� */
    w25qxx_wait_busy();                     /* �ȴ�W25QXX���� */
    W25QXX_CS(0);                           /* ʹ��W25QXXƬѡ */
    spi2_read_write_byte(W25QXX_ChipErase); /* ���Ͳ���оƬ���� */ 
    W25QXX_CS(1);                           /* ʧ��W25QXXƬѡ */
    w25qxx_wait_busy();                     /* �ȴ�оƬ�������� */
}

/**
 * @brief   ����W25QXXһ������
 * @note    ����һ������������ʱ��Ϊ150����
 * @param   saddr: ���������ţ����ֽڵ�ַ������Χ������ʵ��W25QXX����ȷ��
 * @retval  ��
 */
void w25qxx_erase_sector(uint32_t saddr)
{
    saddr *= 4096;                              /* ��������������Ӧ���ֽڵ�ַ */
    w25qxx_write_enable();                      /* W25QXXдʹ�� */
    w25qxx_wait_busy();                         /* �ȴ�W25QXX���� */
    
    W25QXX_CS(0);                               /* ʹ��W25QXXƬѡ */
    spi2_read_write_byte(W25QXX_SectorErase);   /* ���Ͳ����������� */
    w25qxx_send_address(saddr);                 /* ���͵�ַ */
    W25QXX_CS(1);                               /* ʧ��W25QXXƬѡ */
    w25qxx_wait_busy();                         /* �ȴ������������ */
}
