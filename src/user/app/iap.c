/**
  ******************************************************************************
  * @file    iap.c
  * @author  eming
  * @version V1.0.0
  * @date    2022-03-21
  * @brief   IAP����,֧��ѹ����ʽ�̼��Ͳ������
  ******************************************************************************
  */  
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "usr_cfg.h"
#include "stm32f10x.h"
#include "core_cm3.h"
#include "bsp.h"
#include "flash.h"
#include "sys_time.h"
#include "mylib.h"
#include "db.h"
#include "iap.h"

/*************************************************************/
#define IH_MAGIC   0x27051956   /* Image Magic Number       */
#define IH_NMLEN   (32 - 4)     /* Image Name Length        */

typedef struct image_header 
{
    uint32_t ih_magic;/* Image Header Magic Number     */
    uint32_t ih_hcrc; /* Image Header CRC Checksum     */
    uint32_t ih_time; /* Image Creation Timestamp */
    uint32_t ih_size; /* Image Data Size     */
    uint32_t ih_load; /* Data Load Address         */
    uint32_t ih_ep;   /* Entry Point Address      */
    uint32_t ih_dcrc; /* Image Data CRC Checksum */
    uint8_t  ih_os;   /* Operating System         */
    uint8_t  ih_arch; /* CPU architecture         */
    uint8_t  ih_type; /* Image Type          */
    uint8_t  ih_comp; /* Compression Type         */
    uint8_t  ih_name[IH_NMLEN]; /* Image Name      */
    uint32_t ih_ocrc; /* Old Image Data CRC Checksum */ 
} image_header_t;

#define UIMAGE_HEADER_LEN   sizeof(image_header_t)
#define UIMAGE_MAX_LEN      (0x80000) 

/**
 * @brief ����FLASH
 * @details �������ص�flash����
 *
 * @param ��
 * @return ��
 *   @retval ��
 */
void iap_download_flash_erase(void)
{
    flash_partition_erase(flash_bak, 0, FLASH_BAK_SIZE);
}

/**
 * @brief ��������
 * @details �������ݵ����ݷ���
 *
 * @param offset ����ƫ����
 * @param datp ����ָ��
 * @param datp ���ݳ���
 * @return �������
 *   @retval ��
 */
int iap_download(uint32_t offset, uint8_t *datp, uint16_t len)
{
    flash_write_without_erase(flash_bak, offset, datp, len);

    return(TRUE);
}

/**
 * @brief �������ݽ���
 * @details У�����ݣ���д��������־
 *
 * @param ��
 * @return ��
 *   @retval ��
 */
void iap_download_done(void)
{
    image_header_t ih;
    uint32_t magic, size;
    IAP_AppBak_stk 	file_bak;
    
    flash_read(flash_bak, IAP_BAK_ADDR, (uint8_t*)&ih, UIMAGE_HEADER_LEN);
    magic = BigtoLittle32(ih.ih_magic);
    
    if(magic == IH_MAGIC)
    {
        file_bak.flg = IAP_MAGIC_FLG;     //������־
        db_write(&file_bak, DB_APPBAK);
    } 
}

/**
 * @brief IAP��������
 * @details �ֶ�����IAPģʽ
 *
 * @param ��
 * @return ��
 *   @retval ��
 */
void iap_upgrade_start(void)
{
    iap_download_done();   
}

/*******************************************************************************************************
**                            End Of File
********************************************************************************************************/

