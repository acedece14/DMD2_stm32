/*

MyDefine.h


*/



#ifndef __MYDEFINE_H__
#define __MYDEFINE_H__


#include "stm32f10x.h"

//acdc +
#define byte uint8_t
#define String string
//acdc -



#define HALL_UART_MODULE	0x1100
#define AT45DB161_MODULE	0x1200


#define URC_OK		0

//#define	NULL		0


#define STRUCT_FIELD_OFFSET(type,field)  ((unsigned int)(&((type *)0)->field)) 
#define STRUCT_FIELD_SIZE(type,field)    (sizeof(((type *)(0))->field)) 



typedef struct
{
  uint32_t TO_Reseive; // таймаут на прием первого символа
  uint32_t TO_Symbol;  // межсимвольный таймаут
  
}S_TIME_OUT;




typedef int 	(*F_Init_USART)	(uint16_t iBaudRate);
typedef void 	(*F_Init)	(void);
typedef int  	(*F_Connect)	(void);
typedef int  	(*F_Send)	(uint8_t *pucData, uint16_t uiSize);//, unsigned short uiTimeOut);
typedef int  	(*F_Reseive)	(uint8_t *pucData, uint16_t *puiSize, S_TIME_OUT *pTO );//, unsigned short uiTimeOut);
typedef void 	(*F_Close)	(void);
typedef uint16_t(*F_IsReceived) (void);
typedef uint8_t (*F_ReadOneByte)(void);



typedef struct 
{
  F_Init_USART 	Init;
  F_Send 	Send;
  F_Reseive 	Reseive;
  F_Close   	Close;
  F_IsReceived	IsReceivedData;
  F_ReadOneByte ReadOneByte;
  
  S_TIME_OUT TimeOut;  
  
}S_COM_PIPE_USART;






#endif // __MYDEFINE_H__


