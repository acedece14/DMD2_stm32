/*******************************************************************************

	AT45DB161.h

*******************************************************************************/



#ifndef __AT45DB161H__
#define __AT45DB161H__



#include "MyDefine.h"



typedef uint8_t  bool_t;
#define TRUE    1
#define FALSE   0



enum
{
  AT45DB161_OK = 0,
  AT45DB161_GENERAL_ERROR = AT45DB161_MODULE,
  AT45DB161_NOT_INIT_SPI,
  AT45DB161_READ_STATUS_ERROR,
  AT45DB161_SELECT_BUFFER_ERROR,
  AT45DB161_NUM_PAGE_IS_OUT_OF_RANGE_ERROR,
    
  
};



typedef void 	(*F_Init_AT45DB)	        (void);
typedef void 	(*F_DeInit_AT45DB)	        (void);
typedef uint32_t(*F_Read_AT45DB)	        (uint32_t uiAdress, uint8_t *pData, uint16_t uiLen);
typedef uint32_t(*F_Write_AT45DB)	        (uint32_t uiAdress, uint8_t *pData, uint16_t uiLen);
typedef void 	(*F_PowerDown_AT45DB)	        (void);
typedef void 	(*F_PowerOn_AT45DB)	        (void);
typedef uint32_t(*F_ReadStatus_AT45DB)	        (uint8_t *pStatus);
typedef uint32_t(*F_ReadManufacturer_AT45DB)	(void);




typedef struct 
{
  F_Init_AT45DB 	Init;
  F_DeInit_AT45DB   	DeInit;
  F_Read_AT45DB 	ReadData;
  F_Write_AT45DB 	WriteData;
  F_PowerDown_AT45DB	PowerDown;
  F_PowerOn_AT45DB      PowerOn;
  F_ReadStatus_AT45DB   ReadStatus;
  F_ReadManufacturer_AT45DB ReadManufacturerID;
  
  S_TIME_OUT TimeOut;  
  
}S_COM_PIPE_AT45DB;



extern S_COM_PIPE_AT45DB MemAT45DB;



/******************************************************************************/




/*
    »нициализаци€ SPI дл€ общени€ с пам€тью AT45DB161
*/
void AT45DB161_Init(void);


/*
    ќтключение SPI дл€ общени€ с пам€тью AT45DB161
*/
void AT45DB161_DeInit(void);




/*
    ѕолучить статус AT45DB161

	@param  pStatus - —татус

	@ret - возвращает AT45DB161_OK если все хорошо иначе ошибку
*/
uint32_t AT45DB161_ReadStatus(uint8_t *pStatus);


/*
    ѕровер€ет готовность пам€ти AT45DB161

	@ret - возвращает true если пам€ть готова, false - зан€та.
*/
bool_t AT45DB161_isReady(void);



/*
	The Deep Power-down command
	allows the device to enter into the lowest power consumption mode.
*/
void AT45DB161_DeepPowerDown(void);

/*
	The Resume from Deep Power-down command takes the device out of the Deep Power-down
	mode and returns it to the normal standby mode.
*/
void AT45DB161_ResumeFromDeepPowerDown(void);



/*
	Identification information.

	@ret - возвращает Identification information если все хорошо иначе 0xFFFFFFFF
*/
uint32_t AT45DB161_ReadManufacturerAndDeviceID(void);



/*
    ѕрочитать данные, начина€ с адреса uiAdress 

	@param  uiAdress - јдрес, с которого начинаем читать
	@param  pData - указатель куда запишутс€ данные
    @param  uiLen - сколько байт необходимо прочитать

	@ret - возвращает AT45DB161_OK если все хорошо иначе ошибку
*/
uint32_t AT45DB161_ReadData(uint32_t uiAdress, uint8_t *pData, uint16_t uiLen);




/*
    «аписать данные, начина€ с адреса uiAdress 

	@param  uiAdress - јдрес начало записи
	@param  pData - указатель на данные
    @param  uiLen - сколько байт необходимо записать

	@ret - возвращает AT45DB161_OK если все хорошо иначе ошибку
*/
uint32_t AT45DB161_WriteData(uint32_t uiAdress, uint8_t *pData, uint16_t uiLen);




#endif // __AT45DB161H__





