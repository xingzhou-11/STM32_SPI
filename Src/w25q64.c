#include "w25q64.h"
#include "spi.h"

extern SPI_HandleTypeDef hspi2;

//SPI Flash 复位


//读取SPI Flash ID
//Date		读取到的ID
uint32_t SPI_FLASH_ReadID(uint32_t Date)
{
	uint8_t temp[3]={0};
	
	W25X_NSS_Enabled();
	SPI_FLASH_Send(W25X_JedecDeviceID);
	
	if(HAL_SPI_Receive(&hspi2, temp, 3, 0xff) == HAL_OK)
	{
		Date = (uint32_t)temp[0] << 16 | (uint32_t)temp[1] << 8 | (uint32_t)temp[2];
		return 0;
	}
	else
		return 1;
	
	W25X_NSS_Disabled();
}


//SPI Flash 写使能
//使能NSS信号线
//发送写使能命令
//失能NSS信号线
void SPI_FLASH_WriteEnable(void)
{
	W25X_NSS_Enabled();
	
	SPI_FLASH_Send(W25X_WriteEnable);
	
	W25X_NSS_Disabled();
}

//读取状态寄存器等待 FLASH 空闲
void SPI_FLASH_WaitEnd(void)
{
	uint8_t temp[3]={0};
	
	W25X_NSS_Enabled();
	
	SPI_FLASH_Send(W25X_ReadStatusRegister);
	
	while(HAL_SPI_Receive(&hspi2, temp, 1, 0xff) == HAL_BUSY);
	
	W25X_NSS_Disabled();
}

//SPI Flash 扇区擦除	输入地址对齐4KB
//SectorAdd	要擦除的扇区地址
void SPI_FLASH_SectorErase(uint32_t SectorAdd)
{
	//发送写使能
	//等待FLASH空闲
	//使能NSS信号线
	SPI_FLASH_WriteEnable();
	SPI_FLASH_WaitEnd();
	W25X_NSS_Enabled();
	
	//发送扇区擦除指令
	SPI_FLASH_Send(W25X_SectorErase);
	SPI_FLASH_Send((SectorAdd & 0xff0000) >> 16);
	SPI_FLASH_Send((SectorAdd & 0xff00) >> 8);
	SPI_FLASH_Send(SectorAdd & 0xff);
	
	//失能NSS信号线
	//等待擦除结束
	W25X_NSS_Disabled();
	SPI_FLASH_WaitEnd();
}


//SPI Flash 页写入
//pBuffer		要写入的数据的指针
//WriteAddr		要写入的数据的地址
//DataLength	要写入的数据长度
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t DataLength)
{
	//使能NSS信号线
	//等待FLASH空闲
	W25X_NSS_Enabled();
	SPI_FLASH_WaitEnd();
	
	//发送写指令
	//分别发送写地址的高位 中位 低位
	SPI_FLASH_Send(W25X_PageProgram);
	SPI_FLASH_Send((WriteAddr & 0xff0000) >> 16);
	SPI_FLASH_Send((WriteAddr & 0xff00) >> 8);
	SPI_FLASH_Send((WriteAddr & 0xff));
	
	//失能NSS信号线
	//等待FLASH空闲
	W25X_NSS_Disabled();
	SPI_FLASH_WaitEnd();
	
	while(DataLength--)
	{
		//发送当前要写入的字节数据
		//指向下一字节数据
		HAL_SPI_Transmit(&hspi2, pBuffer, 1, 0xff);
		pBuffer++;
	}
	
	//失能NSS信号线
	//等待FLASH空闲
	W25X_NSS_Disabled();
	SPI_FLASH_WaitEnd();
}


//SPI Flash 读数据

