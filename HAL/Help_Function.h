/*******************************************************************************

   Help_Function.h

*******************************************************************************/

#ifndef __HELP_FUNCTION_H__
#define __HELP_FUNCTION_H__


#include "hal_Defined.h"


#ifndef NULL
  #define NULL          0
#endif /* NULL */



typedef struct ST_FindScript
{
   unsigned char uiNumScript;  	// Номер скрипта
   unsigned char ucByte;		// Служебный байт ( кол - во байт которые уже совпали)
   void *Ptr;
  
}T_FindScript;




/*
  Заполнение буфера pData символом ucValue

*/
void MemSet( unsigned char *pData, unsigned char ucValue, int size);



/*
	Копирование данных из одного буфера в другой

	@ pData - буффер куда скопируются данные;
	@ ucValue - буффер откуда скопируются данные;
	@ Size - размер который надо скопировать
*/
void MemCpy( unsigned char *pucData, unsigned char *pucValue, int Size);


/*
   Поиск строгки pStr в буфере pData

	@ pData - Буффер вкотором ищетсяч строка
	@ BufSize - размер буффера
	@ pStr - Данные которые ищутся в буфере
	@ size - размер данных

	@ return - если нашли возвращаем указатель на строку, если нет то NULL
*/
void * MemStr( unsigned char *pData, unsigned int BufSize, unsigned char *pStr, int size);


/*
	Копирование подстроки pStr в конец строки pDest
*/
void StrCat(char *pDest, char *pStr);


/*
	Копирование строки pStr в cтроку pDest
*/
void StrCpy(char *pDest, char *pStr);

/*
	Возвращает количество символов в строке
*/
int StrLen(char *pStr);



/*
    Преоброзование HEX - буффера в строку

	@ pDataIn - Входной hex-буффер
	@ pStrOut - выхрдная строка
	@ pilen - на входе размер буфера, на выходе размер строки ( должно быть в два раза больше)

	@ return - если преоброзовали без ошибок то URC_OK иначе ошибка
*/
int HexBufToStr(unsigned char *pDataIn, char *pStrOut, int *pilen);


/*
    Преоброзование значения int - буффера в строку

	@ pData - указатель преобразуемое значение
	@ pStr - выхрдная строка
	@ pilen - на входе размер переменной int, на выходе размер строки ( должно быть в два раза больше)

	@ return - если преоброзовали без ошибок то URC_OK иначе ошибка
*/
int IntToHex(UINT8 *pData, char *pStr, int *pilen);



/*
  Преоброзование строки в целое число
*/
long Atoi(char *pStr);


/*
    Преоброзование значения int в строку

	@Value - значение;
	@pData - указатель на строку;

	@return - если все хорошо то возвращаем URC_OK, иначе ошибку;

*/
int IntToStr(INT32 Value, char *pData);



#endif // __HELP_FUNCTION_H__

