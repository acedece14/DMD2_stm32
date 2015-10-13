
/*

      file hal_uart.c

*/



#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"



#include "MyDefine.h"
#include "hal_uart.h"
#include "Help_Function.h"

#include "..\mainLoop.c"


static S_USART stUart2_Tx;
static S_USART stUart2_Rx;


S_COM_PIPE_USART Usart2 =
{
  hal_uart2_Init,
  hal_uart2_SendData,
  hal_uart2_ReadData,
  NULL,
  hal_uart2_ReceivedDataAvailable,
  hal_uart2_ReadByte,
  
  { 1500, 50}  
};



/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

char buff[USART_BUFF_SIZE_MAX];
uint16_t usart_count = 0;
char datt[512];
extern "C" void USART2_IRQHandler(void)
{ 
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
      // ������ ��� ����������
      USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    
    if(stUart2_Rx.iuLen >= (USART_BUFF_SIZE_MAX) )
    {
      stUart2_Rx.ucStatus |= UART_OVERFLOW_BUFF; // ������� ������������ ������, ������ ������
      stUart2_Rx.iuLen = USART_BUFF_SIZE_MAX - 1;
    }
      
      
    /* Read one byte from the receive data register */
    //stUart2_Rx.pucData[stUart2_Rx.iuLen++] = USART_ReceiveData(USART2);
    stUart2_Rx.pucData[stUart2_Rx.iuLen++] = (uint8_t)USART2->DR; // USART_ReceiveData(USART2);
   //count++;//= hal_uart2_ReceivedDataAvailable();
    datt[usart_count++] = hal_uart2_ReadByte(); 
   // btProcess();
    //if (count == 4) strncpy(inputStr, datt, 4); 
    __NOP();
//    if(RxCounter2 == NbrOfDataToRead1)
//      USART_ITConfig(USART2, USART_IT_RXNE, DISABLE); /* Disable the USART2 Receive interrupt */

  }
  
  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {   
      USART_ClearITPendingBit(USART2, USART_IT_TXE);
  
  }
}

 

/******************************************************************************/

// ���������� DMA

void DMA1_Channel7_IRQHandler(void)
{
  DMA1->IFCR |= DMA_ISR_TCIF7;  //�������� ���� ��������� ������.
  
  stUart2_Tx.ucStatus &= (~UART_SEND_BY_DMA);
  
  return;
}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/









static void NVIC_Configuration_USART2(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;


  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

  /* Enable the USART2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  return;  
}

/******************************************************************************/

/*
    ������������� COM ����� 

  @param  iBaudRate  �������� �����

  @ret  ���� ��� ������, �� ������������ URC_OK, ����� ������

*/
int hal_uart2_Init(uint16_t iBaudRate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;      

  
  
  
  MemSet((uint8_t*)&stUart2_Tx, 0x00, sizeof(S_USART));
  MemSet((uint8_t*)&stUart2_Rx, 0x00, sizeof(S_USART));
  
  // ��������� ����
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE); 
  
 /* Configure USART2 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_RxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
  
  /* Configure USART2 Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
  

  
  /* Enable USART2 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
  /* Enable the USART2 Pins Software Remapping */
//  GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
  
  /* USART and USART2 configured as follow:
        - BaudRate = xxxxxx baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = iBaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  /* Configure USART2 */
  USART_Init(USART2, &USART_InitStructure);
  
  /* Select the USART2 WakeUp Method */
//  USART_WakeUpConfig(USART2, USART_WakeUp_AddressMark);
  
  // ����������� ��������� ���������� USART2
  NVIC_Configuration_USART2();
  
  // �������� ����������
  NVIC_EnableIRQ(USART2_IRQn);

  //�������� ���������� �� �����.
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  
    /* Enable the USART2 */
  USART_Cmd(USART2, ENABLE);
  
  
  return URC_OK;
}

/******************************************************************************/





/*
    ���������� � ���� ����� DMA, ������������ ������ ������ USART_BUFF_SIZE_MAX
      
  @param pData - ��������� �� ������;
  @param iLen  - ������ ������
*/
static int hal_uart2_Send_DMA (uint8_t *pData, uint16_t iLen)
{
   DMA_InitTypeDef sDMA;
   
   
   if(pData == NULL)
     return HAL_UART_ERROR_INPUT_PARAMETERS;
   
   if(iLen == 0)
     return URC_OK;
   
   // ���������� �� ������������ ������
   if(iLen > USART_BUFF_SIZE_MAX)
     iLen = USART_BUFF_SIZE_MAX;
     
   
   // ����� ��������� ���� �� ����������� ���������� ������
   while(stUart2_Tx.ucStatus & UART_SEND_BY_DMA)
     __no_operation();
   
  // ��������� ���� DMA
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
   
   // �������� ������ �� ���������� �����
   MemCpy( stUart2_Tx.pucData, pData, iLen);
   stUart2_Tx.iuLen = iLen;
   
   // ����������� DMA
   DMA_DeInit (DMA1_Channel7);
   DMA_StructInit (&sDMA);
   sDMA.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR);
   sDMA.DMA_DIR = DMA_DIR_PeripheralDST; 
   sDMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   sDMA.DMA_MemoryInc = DMA_MemoryInc_Enable;
   sDMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   sDMA.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   
   sDMA.DMA_MemoryBaseAddr = (uint32_t)stUart2_Tx.pucData;
   sDMA.DMA_BufferSize = stUart2_Tx.iuLen;
   
   DMA_Init (DMA1_Channel7, &sDMA);


   // ��������� UART �������� � DMA.
   USART_DMACmd (USART2, USART_DMAReq_Tx, ENABLE);
   
// ������������� ���������� �� DMA �� ��������� ��������:
/*
    DMA_IT_TC - �� ��������� ��������.
    DMA_IT_HT - �� �������� �������� ������.
    DMA_IT_TE - ��� �������� �������� ������.
*/
  DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);
   
/*	�������� ����� ���������� � NVIC.	*/
  NVIC_EnableIRQ(DMA1_Channel7_IRQn);

   
  
     // ������������� ������� ���� ��� ���� �������� ������ ����� DMA
   stUart2_Tx.ucStatus |= UART_SEND_BY_DMA;
  
   
   
/*	��������� �������� ������ ����� DMA	*/
   DMA_Cmd (DMA1_Channel7, ENABLE);
   
   
    return URC_OK;
}

/******************************************************************************/


/*
    ���������� ������ � ���� UART2

  @param pData - ��������� �� ������;
  @param iLen  - ������ ������

  @ret ���� ��� ������ �� ���������� URC_OK, ����� ������

*/
int hal_uart2_SendData(uint8_t *pData, uint16_t iLen)
{
  
  if(pData == NULL )
    return HAL_UART_ERROR_INPUT_PARAMETERS;
  
  while(iLen)
  {
    uint16_t PartLen = (iLen < USART_BUFF_SIZE_MAX) ? iLen : (iLen - USART_BUFF_SIZE_MAX);
    
    hal_uart2_Send_DMA (pData, PartLen);
    
    iLen -= PartLen;
    pData += PartLen;
    
  }
  
  
  return URC_OK;  
}

/******************************************************************************/

/*
    ���������� ���������� �������� ������ (����)
*/
uint16_t hal_uart2_ReceivedDataAvailable(void)
{
  return stUart2_Rx.iuLen;  
}

/******************************************************************************/

/*
    ������ ������ ��������� �����

*/
uint8_t hal_uart2_ReadByte(void)
{
   uint8_t ucByte= stUart2_Rx.pucData[0];
 
  
  if(stUart2_Rx.iuLen == 0)
    return 0xFF;
 
  // ��� ����� ������� �������� ������ ������ !!
  // ���� �������� ��� ���������������� � �����������
  
  stUart2_Rx.iuLen--;
  
  if(stUart2_Rx.iuLen)
    MemCpy( &stUart2_Rx.pucData[0], &stUart2_Rx.pucData[1], stUart2_Rx.iuLen);
  
          
  return ucByte; 
}

/******************************************************************************/

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
int hal_uart2_ReadData(uint8_t *pBuffer, uint16_t *puiLen, S_TIME_OUT *pstTO)
{
  
  if(pBuffer == NULL || puiLen == NULL || pstTO == NULL)
    return HAL_UART_ERROR_INPUT_PARAMETERS;
  
//  if(*puiLen == 0)
//    return URC_OK;
  
  
  
  
  
  return HAL_UART_NOT_SUPPORTED;
}



