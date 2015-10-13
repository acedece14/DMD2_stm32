/*******************************************************************************

	AT45DB161.c

*******************************************************************************/


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"


#include "AT45DB161.h"


#define MAX_BYTE_ON_PAGE	        512
#define MAX_PAGES					4095

#define BUFFER_1			1
#define BUFFER_2			2


#define COMAND_GET_STATUS						0xD7
#define COMAND_DEEP_POWER_DOWN					0xB9
#define COMAND_RESUME_FROM_DEEP_POWER_DOWN		0xAB
#define COMAND_READ_IDENTIFICATION_INFO			0x9F

#define COMAND_MAINE_MEMORY_PAGE_READ			0xD2
	
#define COMAND_READ_FROM_BUFF_1					0xD4
#define COMAND_READ_FROM_BUFF_2					0xD6


#define COMAND_MAIN_MEMORY_PAGE_TO_BUF_1		0x53
#define COMAND_MAIN_MEMORY_PAGE_TO_BUF_2		0x55

#define COMAND_WRITE_TO_BUFF_1					0x84
#define COMAND_WRITE_TO_BUFF_2					0x87

#define COMAND_BUFF_1_TO_MAIN_MEMORY_WITH_ERASE	        0x83
#define COMAND_BUFF_2_TO_MAIN_MEMORY_WITH_ERASE         0x86





#define STATUS_READY(x)		((x&0x80) == 0x80)
#define STATUS_CONST(x)		((x&0x2C) == 0x2C)

#define _INIT_MEM_	0x01



#define setStatusInit()		memStatus |= _INIT_MEM_
#define clrStatusInit()		memStatus &= (~_INIT_MEM_)
#define IsStatusInit()		memStatus & _INIT_MEM_

#define CHIP_SELECT()		GPIOB->BRR |= GPIO_Pin_12;     
#define CHIP_UNSELECT()		GPIOB->BSRR |= GPIO_Pin_12;    


//#define SPI2_CS         12 
//#define SPI2_SCK        13 
//#define SPI2_MISO       14 
//#define SPI2_MOSI       15 




static uint8_t  memStatus = 0;



S_COM_PIPE_AT45DB MemAT45DB = 
{
  AT45DB161_Init,
  AT45DB161_DeInit,
  AT45DB161_ReadData,
  AT45DB161_WriteData,
  AT45DB161_DeepPowerDown,
  AT45DB161_ResumeFromDeepPowerDown,
  AT45DB161_ReadStatus,
  AT45DB161_ReadManufacturerAndDeviceID,
  
  {100, 2} 
};









/*
   Прерывание SPI2
*/
void SPI2_IRQHandler (void) 
{
	if (SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==SET) 
	{
		// Прерывание вызвано приемом байта ?
		uint8_t data = SPI2->DR; //Читаем то что пришло
//		GPIOC->ODR ^= (GPIO_Pin_9 | GPIO_Pin_8); //Инвертируем состояние светодиодов
//		SPI1->DR = data; //И отправляем обратно то что приняли
	}
}



static uint8_t SPI2_SendByte(uint8_t ucByte)
{
  while( !( SPI2->SR & SPI_SR_TXE ))
    __no_operation();
  
  SPI2->DR = ucByte;
  
//    while(   SPI2->SR & SPI_I2S_FLAG_BSY);
  while( !( SPI2->SR & SPI_SR_TXE ))
    __no_operation();
  
  while( !(SPI2->SR & SPI_I2S_FLAG_RXNE))
    __no_operation();
  
  
  return SPI2->DR;
}





/*
   Создание команды для памяти
*/
static void aux_MakeAndSendCommand(uint8_t ucComand, uint16_t uiPage, uint16_t uiOffset, bool_t ucCS)
{
  uint32_t retCommand = 0;
  uint8_t *ptr = (uint8_t*)&retCommand;
  
  retCommand  = (ucComand<<24); 
  retCommand |= (0x0FFF&uiPage)<<10;
  retCommand |= (0x03FF&uiOffset);
  
  if(ucCS == TRUE)
  	CHIP_SELECT();
  
  (void)SPI2_SendByte((uint8_t) *(ptr+3) );
  (void)SPI2_SendByte((uint8_t) *(ptr+2) );
  (void)SPI2_SendByte((uint8_t) *(ptr+1) );
  (void)SPI2_SendByte((uint8_t) *ptr );
  
 
  if(ucCS == TRUE)
  	CHIP_UNSELECT();
  
 
  return;
}






/*
    Инициализация SPI для общения с памятью AT45DB161
*/
void AT45DB161_Init(void)
{
  SPI_InitTypeDef    SPI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;  	
  
  
  
	/* SPI2 Periph clock enable */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB1Periph_SPI2, ENABLE);

  /* Configure SPI2 pins: NSS, SCK, MISO and MOSI ----------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  
  
  
  
   /* SPI2 configuration ------------------------------------------------------*/
  SPI_I2S_DeInit(SPI2);	    
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//;Low//; 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; 
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //SPI_NSS_Hard
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //SPI_BaudRatePrescaler_16; 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
//  SPI_InitStructure.SPI_CRCPolynomial = 7; 
  SPI_Init(SPI2,&SPI_InitStructure); 
  SPI_Cmd(SPI2,ENABLE); 

  
  /* Deselect the FLASH: Chip Select high */
   CHIP_UNSELECT();
   
   
   AT45DB161_ResumeFromDeepPowerDown();
   
   setStatusInit();
   
   return;
 
}

		


/*
    Отключение SPI для общения с памятью AT45DB161
*/
void AT45DB161_DeInit(void)
{
    AT45DB161_DeepPowerDown();
    SPI_Cmd(SPI2, DISABLE); // Включаем модуль SPI2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE); // Тактирование модуля SPI2 
    clrStatusInit();
    return;
}



/*
    отослать данные в AT45DB161

   	@param	pData - Указатель на данные, которые надо отправить
	@param  uiLen - Размер данных

	@ret - возвращает AT45DB161_OK если все хорошо иначе ошибку
*/
/*
static uint32_t AT45DB161_SendData(uint8_t *pData, uint16_t uiLen  )
{
    if( !IsStatusInit() )
	return AT45DB161_NOT_INIT_SPI;
	
    while(uiLen--)
      (void)SPI2_SendByte( *pData++ );
	
    return AT45DB161_OK;
}
*/



/*
    принять данные от AT45DB161

   	@param	pData - Указатель на буффер, куда поместятся принятые данные
	@param  puiLen - на входе: сколько надо принять, на выходе: Размер принятых данных

	@ret - возвращает AT45DB161_OK если все хорошо иначе ошибку
*/
/*
static uint32_t AT45DB161_ReceiveData(uint8_t *pData, uint16_t *puiLen )
{
    uint16_t uiMustGetLen = *puiLen;
  

   *puiLen = 0;
  
    if( !IsStatusInit() )
	  return AT45DB161_NOT_INIT_SPI;
  
    while(uiMustGetLen--)
    {
      *pData++ = SPI2_SendByte(0xFF);
      (*puiLen)++;
    }
	
    return AT45DB161_OK;
}
*/




/*
    Получить статус AT45DB161

	@param  pStatus - Статус

	@ret - возвращает AT45DB161_OK если все хорошо иначе ошибку
*/
uint32_t AT45DB161_ReadStatus(uint8_t *pStatus)
{
	*pStatus = 0x00;
	
	if( !IsStatusInit() )
	  return AT45DB161_NOT_INIT_SPI;

	CHIP_SELECT();
        
        SPI2_SendByte(COMAND_GET_STATUS);
        *pStatus = SPI2_SendByte(0xFF);

	CHIP_UNSELECT();
	
	
	if( !STATUS_CONST(*pStatus) )
	  return AT45DB161_READ_STATUS_ERROR;
	
	return AT45DB161_OK;
}


/*
    Проверяет готовность памяти AT45DB161

	@ret - возвращает true если память готова, false - занята.
*/
bool_t AT45DB161_isReady(void)
{
  uint8_t ucStatus = 0x00;
  
  if( AT45DB161_ReadStatus(&ucStatus) != AT45DB161_OK)
	return FALSE;
  
  if( STATUS_READY(ucStatus) )
  	return TRUE;
  
  return FALSE;  
}



/*
	The Deep Power-down command
	allows the device to enter into the lowest power consumption mode.
*/
void AT45DB161_DeepPowerDown(void)
{
    CHIP_SELECT();
    (void)SPI2_SendByte(COMAND_DEEP_POWER_DOWN);
    CHIP_UNSELECT();
    return;	  
}


/*
	The Resume from Deep Power-down command takes the device out of the Deep Power-down
	mode and returns it to the normal standby mode.
*/
void AT45DB161_ResumeFromDeepPowerDown(void)
{
  CHIP_SELECT();
  (void)SPI2_SendByte(COMAND_RESUME_FROM_DEEP_POWER_DOWN);
  CHIP_UNSELECT();
  return;	  
}


/*
	Identification information.

	@ret - возвращает Identification information если все хорошо иначе 0xFFFFFFFF
*/
uint32_t AT45DB161_ReadManufacturerAndDeviceID(void)
{
    uint32_t uiIdenInf = 0xFFFFFFFF;
    uint8_t* pData = (uint8_t*) &uiIdenInf;
    
    CHIP_SELECT();
    
    (void)SPI2_SendByte(COMAND_READ_IDENTIFICATION_INFO);
	
    for(uint8_t k=0; k<4; k++)
      pData[k] = SPI2_SendByte(0xFF);

    CHIP_UNSELECT();
  
    
    return  uiIdenInf; 
}




/*
    Прочитать данные, начиная с адреса uiAdress 

	@param  uiAdress - Адрес, с которого начинаем читать
	@param  pData - указатель куда запишутся данные
    @param  uiLen - сколько байт необходимо прочитать

	@ret - возвращает AT45DB161_OK если все хорошо иначе ошибку
*/
uint32_t AT45DB161_ReadData(uint32_t uiAdress, uint8_t *pData, uint16_t uiLen)
{
   // читаем прямо из FLASH, минуя buffer  // Main Memory Page Read

	uint16_t uiReadBytes = uiLen;
//	uint32_t uiAdr = uiAdress;
	uint16_t uiPage = 0;
	uint16_t offset = 0;
	
	
	if( !IsStatusInit() )
	  return AT45DB161_NOT_INIT_SPI;
	
	
	
	// Считаем начальное смещение
	offset = (uint16_t)(uiAdress - (uint16_t)(uiAdress/MAX_BYTE_ON_PAGE) * MAX_BYTE_ON_PAGE);
	uiPage = (uint16_t)(uiAdress/MAX_BYTE_ON_PAGE);
	
  
	while(uiReadBytes)
	{
		
		aux_MakeAndSendCommand(COMAND_MAIN_MEMORY_PAGE_TO_BUF_1, (uint16_t)uiPage, 0, TRUE);
		
		while(AT45DB161_isReady() == FALSE)
                      __no_operation();
		
		CHIP_SELECT(); 
	
		aux_MakeAndSendCommand(COMAND_READ_FROM_BUFF_1, uiPage,offset, FALSE);
        
              // По документу надо отослать пустой байт после команды, затем читать данные
                (void)SPI2_SendByte( 0xFF );
		
        
                if(uiReadBytes < MAX_BYTE_ON_PAGE) // Если читаем последние байты
                      offset = MAX_BYTE_ON_PAGE - uiReadBytes;
	
                for(uint16_t k=offset; k<MAX_BYTE_ON_PAGE; k++) // читаем данные
                      *pData++ = SPI2_SendByte(0xFF);
		
		CHIP_UNSELECT();
		
//		uiAdr += MAX_BYTE_ON_PAGE - offset;
		uiReadBytes -= (MAX_BYTE_ON_PAGE - offset);
		uiPage++;
		offset = 0;
	}
	
	
	CHIP_UNSELECT();
  
	return AT45DB161_OK;
}




/*
    Записать данные, начиная с адреса uiAdress 

	@param  uiAdress - Адрес начало записи
	@param  pData - указатель на данные
    @param  uiLen - сколько байт необходимо записать

	@ret - возвращает AT45DB161_OK если все хорошо иначе ошибку
*/
uint32_t AT45DB161_WriteData(uint32_t uiAdress, uint8_t *pData, uint16_t uiLen)
{
	uint16_t uiWriteBytes = uiLen;
//	uint32_t uiAdr = uiAdress;
	uint16_t uiPage = 0;
	uint16_t offset = 0;
	
	
	
	if( !IsStatusInit() )
	  return AT45DB161_NOT_INIT_SPI;

	
	// Считаем начальное смещение
	uiPage = (uint16_t)(uiAdress/MAX_BYTE_ON_PAGE);
	offset = (uint16_t)(uiAdress - uiPage * MAX_BYTE_ON_PAGE);
	
	if(offset != 0)
	  aux_MakeAndSendCommand(COMAND_MAIN_MEMORY_PAGE_TO_BUF_1, uiPage, 0, TRUE);
  
	while(uiWriteBytes)
	{
		while(AT45DB161_isReady() == FALSE)
                  __no_operation();
		
		CHIP_SELECT();
		
		aux_MakeAndSendCommand(COMAND_WRITE_TO_BUFF_1, 0, offset, FALSE);
		
		if(uiWriteBytes < MAX_BYTE_ON_PAGE) // Если записываем последние байты 
			offset = MAX_BYTE_ON_PAGE - uiWriteBytes;
	
		for(uint16_t k=offset; k<MAX_BYTE_ON_PAGE; k++) // записываем данные
                        (void)SPI2_SendByte( *pData++ );

		CHIP_UNSELECT();
		
		
		while(AT45DB161_isReady() == FALSE)
                      __no_operation();
		
		// Записываем buffer в Main Memory
		aux_MakeAndSendCommand(COMAND_BUFF_1_TO_MAIN_MEMORY_WITH_ERASE, uiPage, 0, TRUE);
		
        
//		uiAdr += MAX_BYTE_ON_PAGE - offset;
		uiWriteBytes -= (MAX_BYTE_ON_PAGE - offset);
		uiPage++;
		offset = 0;
	}
   
	
	CHIP_UNSELECT();

	return AT45DB161_OK;
}






