#ifndef __w25q64_H
#define __w25q64_H

#include "main.h"

extern SPI_HandleTypeDef hspi2;

//FLASH 常用命令
#define W25X_WriteEnable						0x06
#define W25X_WriteDisable						0x04
#define W25X_ReadStatusRegister					0x05
#define W25X_WriteStatusRegister   				0x01
#define W25X_ReadData							0x03
#define W25X_FastRead							0x0B
#define W25X_FastReadDualOutput					0x3B
#define W25X_PageProgram 						0x02
#define W25X_BlockErase 						0xD8	//64KB
#define W25X_SectorErase 						0x20	//4KB
#define W25X_ChipErase 							0xC7
#define W25X_PowerDown 							0xB9
#define W25X_ReleasePowerDown 					0xAB	//ID7-ID0
#define W25X_DeviceID 							0xAB	//ID7-ID0
#define W25X_ManufactDeviceID 					0x90	//M7-M0 / 
#define W25X_JedecDeviceID 						0x9F	//读取spiID

//spi ID
#define SPI_FLASH_ID 							0XEF4017

//spi nss 信号
#define W25X_NSS_Enabled()						HAL_GPIO_WritePin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin, GPIO_PIN_SET)
#define W25X_NSS_Disabled()						HAL_GPIO_WritePin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin, GPIO_PIN_RESET)

#endif