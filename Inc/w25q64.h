#ifndef __w25q64_H
#define __w25q64_H

#include "main.h"

extern SPI_HandleTypeDef hspi2;

//FLASHҳ��С
#define SPI_FLASH_PageSize              		256

//FLASH ��������
#define W25X_WriteEnable						0x06	//����д��
#define W25X_WriteDisable						0x04	//����д��
#define W25X_ReadStatusRegister					0x05	//��״̬�Ĵ���
#define W25X_WriteStatusRegister   				0x01	//д״̬�Ĵ���
#define W25X_ReadData							0x03	//��ȡ����
#define W25X_FastRead							0x0B	//���ٶ�ȡ
#define W25X_FastReadDualOutput					0x3B
#define W25X_PageProgram 						0x02
#define W25X_BlockErase 						0xD8	//����� 64KB
#define W25X_SectorErase 						0x20	//�������� 4KB
#define W25X_ChipErase 							0xC7	//оƬ����
#define W25X_PowerDown 							0xB9
#define W25X_ReleasePowerDown 					0xAB	//ID7-ID0
#define W25X_DeviceID 							0xAB	//ID7-ID0
#define W25X_ManufactDeviceID 					0x90	//M7-M0 / 
#define W25X_JedecDeviceID 						0x9F	//��ȡspiID

//spi ID
#define SPI_FLASH_ID 							0XEF4017

//spi nss �ź�
#define W25X_NSS_Enabled()						HAL_GPIO_WritePin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin, GPIO_PIN_SET)
#define W25X_NSS_Disabled()						HAL_GPIO_WritePin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin, GPIO_PIN_RESET)


uint32_t SPI_FLASH_ReadID(uint32_t *p_buffer);
void SPI_FLASH_Sector_Erase(uint32_t SectorAdd);
void SPI_FLASH_Page_Write(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t DataLength);
void SPI_FLASH_Read_Data(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t DataLength);

#endif
