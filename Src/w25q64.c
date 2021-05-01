#include "w25q64.h"
#include "spi.h"

extern SPI_HandleTypeDef hspi2;

//SPI Flash ��λ


//��ȡSPI Flash ID
//Date		��ȡ����ID
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


//SPI Flash дʹ��
//ʹ��NSS�ź���
//����дʹ������
//ʧ��NSS�ź���
void SPI_FLASH_WriteEnable(void)
{
	W25X_NSS_Enabled();
	
	SPI_FLASH_Send(W25X_WriteEnable);
	
	W25X_NSS_Disabled();
}

//��ȡ״̬�Ĵ����ȴ� FLASH ����
void SPI_FLASH_WaitEnd(void)
{
	uint8_t temp[3]={0};
	
	W25X_NSS_Enabled();
	
	SPI_FLASH_Send(W25X_ReadStatusRegister);
	
	while(HAL_SPI_Receive(&hspi2, temp, 1, 0xff) == HAL_BUSY);
	
	W25X_NSS_Disabled();
}

//SPI Flash ��������	�����ַ����4KB
//SectorAdd	Ҫ������������ַ
void SPI_FLASH_SectorErase(uint32_t SectorAdd)
{
	//����дʹ��
	//�ȴ�FLASH����
	//ʹ��NSS�ź���
	SPI_FLASH_WriteEnable();
	SPI_FLASH_WaitEnd();
	W25X_NSS_Enabled();
	
	//������������ָ��
	SPI_FLASH_Send(W25X_SectorErase);
	SPI_FLASH_Send((SectorAdd & 0xff0000) >> 16);
	SPI_FLASH_Send((SectorAdd & 0xff00) >> 8);
	SPI_FLASH_Send(SectorAdd & 0xff);
	
	//ʧ��NSS�ź���
	//�ȴ���������
	W25X_NSS_Disabled();
	SPI_FLASH_WaitEnd();
}


//SPI Flash ҳд��
//pBuffer		Ҫд������ݵ�ָ��
//WriteAddr		Ҫд������ݵĵ�ַ
//DataLength	Ҫд������ݳ���
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t DataLength)
{
	//ʹ��NSS�ź���
	//�ȴ�FLASH����
	W25X_NSS_Enabled();
	SPI_FLASH_WaitEnd();
	
	//����дָ��
	//�ֱ���д��ַ�ĸ�λ ��λ ��λ
	SPI_FLASH_Send(W25X_PageProgram);
	SPI_FLASH_Send((WriteAddr & 0xff0000) >> 16);
	SPI_FLASH_Send((WriteAddr & 0xff00) >> 8);
	SPI_FLASH_Send((WriteAddr & 0xff));
	
	//ʧ��NSS�ź���
	//�ȴ�FLASH����
	W25X_NSS_Disabled();
	SPI_FLASH_WaitEnd();
	
	while(DataLength--)
	{
		//���͵�ǰҪд����ֽ�����
		//ָ����һ�ֽ�����
		HAL_SPI_Transmit(&hspi2, pBuffer, 1, 0xff);
		pBuffer++;
	}
	
	//ʧ��NSS�ź���
	//�ȴ�FLASH����
	W25X_NSS_Disabled();
	SPI_FLASH_WaitEnd();
}


//SPI Flash ������

