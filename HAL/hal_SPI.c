
/*******************************************************************************


  hal_SPI.c



*******************************************************************************/








#include "stm32f10x.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_spi.h"
//#include "stm32f10x_dma.h"



#include "hal_SPI.h"








/*
   инициализация модуля SPI
*/
extern "C" void hal_SPI_Init(void)
{
  SPI_InitTypeDef    SPI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;  	
  
  
  
	/* SPI1 Periph clock enable */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1,  ENABLE);

  /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  /* Configure SPI1 pins: NSS ----------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;                    // GPIO_Pin_4 = CS        
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  
  
   /* SPI1 configuration ------------------------------------------------------*/
  SPI_I2S_DeInit(SPI1);	    
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // SPI_Direction_1Line_Tx
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//;Low//; 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; 
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //SPI_NSS_Hard
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; //SPI_BaudRatePrescaler_16; 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
//  SPI_InitStructure.SPI_CRCPolynomial = 7; 
  SPI_Init(SPI1,&SPI_InitStructure); 
  SPI_Cmd(SPI1,ENABLE); 
   return;  
}




/*
    Отключение SPI
*/
extern "C" void hal_SPI_DeInit(void)
{
    SPI_Cmd(SPI1, DISABLE); // Выключаем модуль SPI2
    return;
}



/*
   отправить байт

   @param ucByte - байт для отправки в SPI

   @ret - возвращает принятый байт
*/
extern "C" uint8_t hal_SPI_SendByte(uint8_t ucByte)
{ 
    //hal_SPI_Init();
    /* Wait for SPI1 Tx buffer empty */
  while( !( SPI1->SR & SPI_I2S_FLAG_TXE /*SPI_SR_TXE */ ))
    __no_operation();
  
  SPI1->DR = ucByte;
  
  /* Wait for SPI1 Tx buffer empty */
 // while( !( SPI1->SR & SPI_I2S_FLAG_TXE /*SPI_SR_TXE */ ))
 //   __no_operation();
  
  
  /* Wait for SPI1 data reception */
 // while( !(SPI1->SR & SPI_I2S_FLAG_RXNE))
 //   __no_operation();
  
  
  return 0xFF; //SPI1->DR;
}

