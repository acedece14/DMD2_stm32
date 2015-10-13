/*

   HAL_Delay.h





*/


#ifndef  __DELAY_CONFIG_H__
#define  __DELAY_CONFIG_H__


#include "stm32f10x.h"
#include "MyDefine.h"

enum
{
   TIMER_GENERAL_ERROR = 110000, //TIMER_ERROR,
   TIMER_ERROR_TIME_OUT,
   TIMER_ERROR_NUM_TIMER
 
};


#define TIMER_ENABEL    1
#define TIMER_DISAIBLE  0


#define TIMERS_COUNT    20


typedef  uint8_t    TTIMER;


typedef struct ST_Timers
{
  uint8_t   Status;     // определяет задействован таймер или нет
  uint32_t  iTimeout;   // значение таймера в милисекундах
}T_Timer;




/*
    Сбросить системный счетчик
*/
void hal_delay_ClearCycCnt(void);


/*
    Получить значение системного счетчика
*/
uint32_t hal_delay_getValueOfCycCnt(void);


/*
	Данный метод необходимо поместить в прерывание таймера
*/
void Timer_CountTime(void);


/*
    Создание таймера.

    @ iTimeout  - значение в милисекундах

    Если создался то возвращается номер таймера, иначе возвращает 0;
*/
TTIMER Timer_Create(uint32_t iTimeout);


/*
    Удалить созданный таймер

    @ Timer - параметр возвращенный методом Timer_Create(...)
*/
void Timer_Delete(TTIMER Timer);



/*
   Проверка таймера 

   @ Timer  - параметр возвращенный методом Timer_Create(...)

    возвращает оставшееся время в милисек.
*/
uint32_t Timer_CheckStatus(TTIMER Timer);



/*
   Установить время таймера уже созданного методом Timer_Create(...)

   @ Timer  - параметр возвращенный методом Timer_Create(...)

   @ iTimeOut - Время в милисекундах

    возвращает 0 если обновили, иначе ошибку
*/
int Timer_SetTimeout(TTIMER Timer, uint32_t iTimeOut);







 
/**
 * @brief Delay the given number of microseconds.
 *
 * @param us Number of microseconds to delay.
 */
void HAL_Delay_us(uint32_t delay);



/**
 * @brief Delay the given number of microseconds.
 *
 * @param us Number of miliseconds to delay.
 */
void HAL_Delay_ms(uint32_t delay);


#endif // __DELAY_CONFIG_H__


