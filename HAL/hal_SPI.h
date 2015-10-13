
/*******************************************************************************


  hal_SPI.h



*******************************************************************************/


#ifndef __HAL_SPI_H__
#define __HAL_SPI_H__
#include "stm32f10x.h"
/*
   ������������� ������ SPI
*/
extern "C" void hal_SPI_Init(void);
/*
    ���������� SPI
*/
extern "C" void hal_SPI_DeInit(void);
/*
   ��������� ����

   @param ucByte - ���� ��� �������� � SPI

   @ret - ���������� �������� ����
*/
extern "C" uint8_t hal_SPI_SendByte(uint8_t ucByte);
#endif // __HAL_SPI_H__



