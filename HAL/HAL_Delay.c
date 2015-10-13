/*


  HAL_Delay.c



*/

#include "stm32f10x.h"
#include "HAL_Delay.h"


volatile unsigned int *DWT_CYCCNT   = (volatile unsigned int *)0xE0001004; //address of the register
volatile unsigned int *DWT_CONTROL  = (volatile unsigned int *)0xE0001000; //address of the register
volatile unsigned int *SCB_DEMCR    = (volatile unsigned int *)0xE000EDFC; //address of the register


volatile static T_Timer Timers[TIMERS_COUNT];



/******************************************************************************/
/******************************************************************************/
/*
    Сбросить системный счетчик
*/
void hal_delay_ClearCycCnt(void)
{
    *DWT_CYCCNT = 0;  //if need to start from zero
    //DWT initialization:
    *SCB_DEMCR |=  0x01000000; 
    *DWT_CONTROL |= 1; // enable the counter  
    
         //включаем DWT
	 *SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	 *DWT_CYCCNT  = 0;
	 *DWT_CONTROL|= DWT_CTRL_CYCCNTENA_Msk; 
}

/*
    Получить значение системного счетчика
*/
uint32_t hal_delay_getValueOfCycCnt(void)
{
    return (uint32_t)(*DWT_CYCCNT); 
}

/******************************************************************************/
/******************************************************************************/
 
/**
 * @brief Delay the given number of microseconds.
 *
 * @param us Number of microseconds to delay.
 */
void HAL_Delay_us(uint32_t delay) 
{
    RCC_ClocksTypeDef RCC_Clocks;
    uint32_t  Tmp;
    
    
    *DWT_CYCCNT = 0;  //if need to start from zero
    //DWT initialization:
    *SCB_DEMCR = *SCB_DEMCR | 0x01000000; 
    *DWT_CONTROL |= 1; // enable the counter

    RCC_GetClocksFreq(&RCC_Clocks);
    Tmp = (RCC_Clocks.HCLK_Frequency / 1000000) * delay;
    
    while(*DWT_CYCCNT <= Tmp)
      asm("nop");

    return;
}

/******************************************************************************/
/******************************************************************************/

/**
 * @brief Delay the given number of microseconds.
 *
 * @param us Number of miliseconds to delay.
 */
void HAL_Delay_ms(uint32_t delay) 
{
      while(delay--)
        HAL_Delay_us(999); 
      
      return;
}







/******************************************************************************/
/******************************************************************************/

/*
	Данный метод необходимо поместить в прерывание таймера
*/
void Timer_CountTime(void)
{
    for(uint8_t i =0; i < TIMERS_COUNT; i++)
        if(Timers[i].Status == TIMER_ENABEL && Timers[i].iTimeout >0 )
            Timers[i].iTimeout--;
	
	return;
}
/******************************************************************************/
/******************************************************************************/
/*
    Создание таймера.

    @ iTimeout  - значение в милисекундах

    Если создался то возвращается номер таймера, иначе возвращает 0;
*/
TTIMER Timer_Create(uint32_t iTimeout)
{
  
  for(uint8_t i = 0; i<TIMERS_COUNT; i++)
    if(Timers[i].Status == TIMER_DISAIBLE)
    {
       Timers[i].Status = TIMER_ENABEL;
       Timers[i].iTimeout = iTimeout;
       
       return (i+1);
    }
    
   return 0;
}

/******************************************************************************/
/******************************************************************************/
/*
    Удалить созданный таймер

    @ Timer - параметр возвращенный методом Timer_Create(...)
*/
void Timer_Delete(TTIMER Timer)
{
  if(Timer > TIMERS_COUNT || !Timer)
    return;
    
   Timers[Timer-1].Status = TIMER_DISAIBLE;
  
  return;
}
/******************************************************************************/
/******************************************************************************/
/*
   Проверка таймера 

   @ Timer  - параметр возвращенный методом Timer_Create(...)

    возвращает оставшееся время в милисек.
*/
uint32_t Timer_CheckStatus(TTIMER Timer)
{
  if(Timer > TIMERS_COUNT || Timer==0)
    return TIMER_ERROR_NUM_TIMER;
  
  return Timers[Timer-1].iTimeout;
}
/******************************************************************************/
/******************************************************************************/
/*
   Установить время таймера уже созданного методом Timer_Create(...)

   @ Timer  - параметр возвращенный методом Timer_Create(...)

   @ iTimeOut - Время в милисекундах

    возвращает 0 если обновили, иначе ошибку
*/
int Timer_SetTimeout(TTIMER Timer, uint32_t iTimeOut)
{
  if(Timer > TIMERS_COUNT || !Timer)
    return TIMER_ERROR_NUM_TIMER;
  
  Timers[Timer-1].iTimeout = iTimeOut;
  
  return URC_OK;
}
/******************************************************************************/
/******************************************************************************/


