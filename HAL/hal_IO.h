/*

   file  hal_IO.h

*/


#ifndef __HAL_IO_H__
#define __HAL_IO_H__


enum
{
  HAL_IO_MODE_INPUT = 0,
  HAL_IO_MODE_OUTPUT = 1,
};




#include "stm32f10x.h"
#include "stm32f10x_gpio.h"





/*
   ������������� ����� 

  @param RCC_APB2Periph - ����, �������� RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB
  @param GPIOx     - �������� �����, �������� GPIOA, GPIOB ....
  @param GPIO_Pin  - ����� �����, �������� GPIO_Pin_0, GPIO_Pin_1 ... GPIO_Pin_15
  @param Mode      - ��������� ����� HAL_IO_MODE_INPUT = 0, HAL_IO_MODE_OUTPUT = 1

*/
void hal_IO_InitPin(uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t Mode );


/*
    ���������� � ���� ��������� HIGHT ��� LOW

  @param GPIOx     - �������� �����, �������� GPIOA, GPIOB ....
  @param GPIO_Pin  - ����� �����, �������� GPIO_Pin_0, GPIO_Pin_1 ... GPIO_Pin_15
  @param Status    - ��������� ����� HIGHT = 1, LOW = 0

*/
void hal_digitalWrite(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t Status);






/*
    ������ ��������� �����

  @param GPIOx     - �������� �����, �������� GPIOA, GPIOB ....
  @param GPIO_Pin  - ����� �����, �������� GPIO_Pin_0, GPIO_Pin_1 ... GPIO_Pin_15

  @ret ���������� ��������� ����� 1-HIGHT, 0-LOW

*/
uint8_t hal_digitalRead(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);



#endif // __HAL_IO_H__

