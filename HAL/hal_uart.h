
/*

      file hal_uart.h


*/


#ifndef __HAL_UART_H__
#define __HAL_UART_H__



#include "MyDefine.h"






#define USART_BUFF_SIZE_MAX    512


#define UART_SEND_BY_DMA       0x02     // Если бит установлен значит идет отправка данных через DMA
#define UART_OVERFLOW_BUFF     0x04     // Если бит установлен значит gпроизошло переполнение буффера
                                        // Приняли данных больше чем размер буффера. Произошла потеря данных.



#define  GPIOx                    GPIOA
#define  RCC_APB2Periph_GPIOx     RCC_APB2Periph_GPIOA
#define  GPIO_TxPin               GPIO_Pin_2
#define  GPIO_RxPin               GPIO_Pin_3



typedef struct
{
  	uint8_t pucData[USART_BUFF_SIZE_MAX];
	uint16_t iuLen;
	uint8_t ucStatus;					// если отправили в порт то установиться в 1

} S_USART;

void btProcess2();

enum
{
  HAL_UART_GENERAL_ERROR = HALL_UART_MODULE,
  HAL_UART_NOT_SUPPORTED,
  
  HAL_RECEIVED_TIMEOUT,                 // Таймаут приема данных
  HAL_UART_ERROR_INPUT_PARAMETERS,      // Неверные входные параметры
  
    
};




 // методы работы с портом USART2
 extern S_COM_PIPE_USART Usart2;




/*
    Инициализация COM порта 

  @param  iBaudRate  скорость порта

  @ret  если все хорошо, то возвращается URC_OK, иначе ошибку

*/
int hal_uart2_Init(uint16_t iBaudRate);



/*
    Отправляем данные в порт UART2

  @param pData - указатель на данные;
  @param iLen  - размер данных

  @ret если все хорошо то возвращаем URC_OK, иначе ошибку

*/
int hal_uart2_SendData(uint8_t *pData, uint16_t iLen);


/*
    Возвращает количество принятых данных (байт)
*/
uint16_t hal_uart2_ReceivedDataAvailable(void);




/*
    Чтение одного принятого байта

*/
uint8_t hal_uart2_ReadByte(void);






/*
    Чтение данных из порта USART2

    @param pBuffer - буффер куда будут скопированы данные;
    @param puiLen  - на входе: размер буфера ( сколько надо принять), 
                     на выходе: размер принятых данных;
    @param pstTO  - таймаут на прием первого байта, и межсимвольный таймаут.

    @ret   если приняли столько же сколько задоно но возвращаем URC_OK,
           если нет приема в указанных пределах таймаута, то вернем ошибку таймаута
           в других случаях ошибку.
*/
int hal_uart2_ReadData(uint8_t *pBuffer, uint16_t *puiLen, S_TIME_OUT *pstTO);

#endif //__HAL_UART_H__
