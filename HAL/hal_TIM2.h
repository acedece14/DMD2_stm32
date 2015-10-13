/*******************************************************************************

    file hal_TIM2.h




*******************************************************************************/




#ifndef __HAL_TIM2_H__
#define __HAL_TIM2_H__



#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"




#define TIM2__PIN0_AND_PIN1     1
#define TIM2__PIN0_AND_PIN2     2





/*
    Инициализация таймера и ШИМ
   
*/
extern "C" void hal_TIM2_Init(void);



/*
    остановка таймера 
*/
extern "C" void hal_TIM2_DeInit(void);



/*
    Установка скважности ШИМ
*/
extern "C" void hal_TIM2_Set_OCC1(uint16_t value);


#endif // __HAL_TIM2_H__




