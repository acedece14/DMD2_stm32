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
  uint8_t   Status;     // ���������� ������������ ������ ��� ���
  uint32_t  iTimeout;   // �������� ������� � ������������
}T_Timer;




/*
    �������� ��������� �������
*/
void hal_delay_ClearCycCnt(void);


/*
    �������� �������� ���������� ��������
*/
uint32_t hal_delay_getValueOfCycCnt(void);


/*
	������ ����� ���������� ��������� � ���������� �������
*/
void Timer_CountTime(void);


/*
    �������� �������.

    @ iTimeout  - �������� � ������������

    ���� �������� �� ������������ ����� �������, ����� ���������� 0;
*/
TTIMER Timer_Create(uint32_t iTimeout);


/*
    ������� ��������� ������

    @ Timer - �������� ������������ ������� Timer_Create(...)
*/
void Timer_Delete(TTIMER Timer);



/*
   �������� ������� 

   @ Timer  - �������� ������������ ������� Timer_Create(...)

    ���������� ���������� ����� � �������.
*/
uint32_t Timer_CheckStatus(TTIMER Timer);



/*
   ���������� ����� ������� ��� ���������� ������� Timer_Create(...)

   @ Timer  - �������� ������������ ������� Timer_Create(...)

   @ iTimeOut - ����� � ������������

    ���������� 0 ���� ��������, ����� ������
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


