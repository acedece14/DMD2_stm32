
/*

      file hal_uart.h


*/


#ifndef __HAL_UART_H__
#define __HAL_UART_H__



#include "MyDefine.h"






#define USART_BUFF_SIZE_MAX    512


#define UART_SEND_BY_DMA       0x02     // ���� ��� ���������� ������ ���� �������� ������ ����� DMA
#define UART_OVERFLOW_BUFF     0x04     // ���� ��� ���������� ������ g��������� ������������ �������
                                        // ������� ������ ������ ��� ������ �������. ��������� ������ ������.



#define  GPIOx                    GPIOA
#define  RCC_APB2Periph_GPIOx     RCC_APB2Periph_GPIOA
#define  GPIO_TxPin               GPIO_Pin_2
#define  GPIO_RxPin               GPIO_Pin_3



typedef struct
{
  	uint8_t pucData[USART_BUFF_SIZE_MAX];
	uint16_t iuLen;
	uint8_t ucStatus;					// ���� ��������� � ���� �� ������������ � 1

} S_USART;

void btProcess2();

enum
{
  HAL_UART_GENERAL_ERROR = HALL_UART_MODULE,
  HAL_UART_NOT_SUPPORTED,
  
  HAL_RECEIVED_TIMEOUT,                 // ������� ������ ������
  HAL_UART_ERROR_INPUT_PARAMETERS,      // �������� ������� ���������
  
    
};




 // ������ ������ � ������ USART2
 extern S_COM_PIPE_USART Usart2;




/*
    ������������� COM ����� 

  @param  iBaudRate  �������� �����

  @ret  ���� ��� ������, �� ������������ URC_OK, ����� ������

*/
int hal_uart2_Init(uint16_t iBaudRate);



/*
    ���������� ������ � ���� UART2

  @param pData - ��������� �� ������;
  @param iLen  - ������ ������

  @ret ���� ��� ������ �� ���������� URC_OK, ����� ������

*/
int hal_uart2_SendData(uint8_t *pData, uint16_t iLen);


/*
    ���������� ���������� �������� ������ (����)
*/
uint16_t hal_uart2_ReceivedDataAvailable(void);




/*
    ������ ������ ��������� �����

*/
uint8_t hal_uart2_ReadByte(void);






/*
    ������ ������ �� ����� USART2

    @param pBuffer - ������ ���� ����� ����������� ������;
    @param puiLen  - �� �����: ������ ������ ( ������� ���� �������), 
                     �� ������: ������ �������� ������;
    @param pstTO  - ������� �� ����� ������� �����, � ������������� �������.

    @ret   ���� ������� ������� �� ������� ������ �� ���������� URC_OK,
           ���� ��� ������ � ��������� �������� ��������, �� ������ ������ ��������
           � ������ ������� ������.
*/
int hal_uart2_ReadData(uint8_t *pBuffer, uint16_t *puiLen, S_TIME_OUT *pstTO);

#endif //__HAL_UART_H__
