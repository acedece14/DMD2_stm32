/*

   file  hal_IO.c

*/



#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"



#include "hal_IO.h"






/*
   Инициализация порта 

  @param RCC_APB2Periph - порт, например RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB
  @param GPIOx     - параметр порта, например GPIOA, GPIOB ....
  @param GPIO_Pin  - номер порта, например GPIO_Pin_0, GPIO_Pin_1 ... GPIO_Pin_15
  @param Mode      - состояние порта HAL_IO_MODE_INPUT = 0, HAL_IO_MODE_OUTPUT = 1

*/
void hal_IO_InitPin(uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t Mode )
{
   GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph, ENABLE);
                         
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  if(Mode == HAL_IO_MODE_INPUT)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  else
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  return;   
}



/*
    Записываем в порт состояние HIGHT или LOW

  @param GPIOx     - параметр порта, например GPIOA, GPIOB ....
  @param GPIO_Pin  - номер порта, например GPIO_Pin_0, GPIO_Pin_1 ... GPIO_Pin_15
  @param Status    - состояние порта HIGHT = 1, LOW = 0

*/
void hal_digitalWrite(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t Status)
{
  if(Status)
    GPIO_SetBits(GPIOx, GPIO_Pin);
  else
    GPIO_ResetBits(GPIOx, GPIO_Pin);
  return;  
}




/*
    Читаем состояние порта

  @param GPIOx     - параметр порта, например GPIOA, GPIOB ....
  @param GPIO_Pin  - номер порта, например GPIO_Pin_0, GPIO_Pin_1 ... GPIO_Pin_15

  @ret возвращаем состояние порта 1-HIGHT, 0-LOW

*/
uint8_t hal_digitalRead(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  return  GPIO_ReadInputDataBit(GPIOx, GPIO_Pin);
}

