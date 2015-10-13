/*******************************************************************************

   Help_Function.c

*******************************************************************************/

#include "Help_Function.h"
#include "hal_Defined.h"


/*
  Заполнение буфера pData символом ucValue

*/
void MemSet( unsigned char *pData, unsigned char ucValue, int size)
{
  while( size--)
	*pData++ = ucValue;

  return;  
}





/*
	Копирование данных из одного буфера в другой

	@ pData - буффер куда скопируются данные;
	@ ucValue - буффер откуда скопируются данные;
	@ Size - размер который надо скопировать
*/
void MemCpy( unsigned char *pucData, unsigned char *pucValue, int Size)
{
   while(Size--)
	*pucData++ = *pucValue++;
  
  return;  
}








/*
   Поиск строгки pStr в буфере pData

	@ pData - Буффер вкотором ищетсяч строка
	@ BufSize - размер буффера
	@ pStr - Данные которые ищутся в буфере
	@ size - размер данных

	@ return - если нашли возвращаем указатель на строку, если нет то NULL
*/
void * MemStr( unsigned char *pData, unsigned int BufSize, unsigned char *pStr, int size)
{
  unsigned char *MemStr = NULL;
  int iLen=0;
  
  
  for( ; BufSize > 0 ; BufSize--, pData++)
	if(*pData == pStr[iLen])
	{
	  
	  if(!MemStr)
		MemStr = pData;
	  
	  iLen++;
	  
	  if(iLen >= size)
		break;	  
	}
    else
	{
	  MemStr = NULL;
	  iLen = 0;
	}
  
  return MemStr;  
}



/*
	Копирование подстроки pStr в конец строки pDest
*/
void StrCat(char *pDest, char *pStr)
{
  	char *pTmpDest = pDest;
  	char *pTmpStr = pStr;
  
  	for( ; *pTmpDest != '\0'; pTmpDest++);
  
  	for( ; *pTmpStr != '\0'; pTmpStr++)
		*pTmpDest++ = *pTmpStr;
	
  	*pTmpDest = '\0';
  
	return;  
}


/*
	Копирование строки pStr в cтроку pDest
*/
void StrCpy(char *pDest, char *pStr)
{
  	char *pTmpDest = pDest;
  	char *pTmpStr = pStr;
 
  	for( ; *pTmpStr != '\0'; pTmpStr++)
		*pTmpDest++ = *pTmpStr;
	
  	*pTmpDest = '\0';
  
	return;  
}



/*
	Возвращает количество символов в строке
*/
int StrLen(char *pStr)
{
	int i = 0;
	char *pTmpStr = pStr;
	
	for( ; *pTmpStr != '\0'; pTmpStr++)
	  i++;
  
	return i;  
}


/*
    Преоброзование значения int - буффера в строку

	@ pData - указатель преобразуемое значение
	@ pStr - выхрдная строка
	@ pilen - на входе размер переменной int, на выходе размер строки ( должно быть в два раза больше)

	@ return - если преоброзовали без ошибок то URC_OK иначе ошибка
*/
int IntToHex(UINT8 *pData, char *pStr, int *pilen)
{
  	char *pStrTmp = pStr;
	UINT8 *pDataIn;
    int iSize;
	char pcAscii[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  
	if(pStr == NULL || pilen == NULL)
	  return -2;
	
	
	iSize = *pilen;
	pDataIn = pData + iSize - 1; 
	*pilen = iSize*2;
		
	while(iSize--)
	{
	  *pStrTmp++ = pcAscii[ ((*pDataIn)>>4)&0x0F ];
	  *pStrTmp++ = pcAscii[ (*pDataIn--)&0x0F ];
	}
  
//	*pilen *= 2;
  
	return URC_OK;  
}

/*
    Преоброзование HEX - буффера в строку

	@ pData - Входной hex-буффер
	@ pStr - выхрдная строка
	@ pilen - на входе размер буфера, на выходе размер строки ( должно быть в два раза больше)

	@ return - если преоброзовали без ошибок то URC_OK иначе ошибка
*/
int HexBufToStr(UINT8 *pData, char *pStr, int *pilen)
{
  	char *pStrTmp = pStr;
	UINT8 *pDataIn;
    int iSize, i;
	char pcAscii[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  
	if(pData == NULL || pStr == NULL || pilen == NULL)
	  return -2;
	
	pDataIn = pData; 
	iSize = *pilen;
	*pilen = 0;
		
	for(i = 0; i< iSize; i++)
	{
	  *pStrTmp++ = pcAscii[ ((*pDataIn)>>4)&0x0F ];
	  *pStrTmp++ = pcAscii[ (*pDataIn++)&0x0F ];
	}
  
	*pilen = i*2;
  
	return URC_OK;
}




/*
  Преоброзование строки в целое число
*/
long Atoi(char *pStr)
{
  INT32 lValue = 0;
  
  for( ; *pStr != '\0'; pStr++)
  {
	if(*pStr < '0' || *pStr > '9')
	  break;

	lValue = lValue * 10 + 	(*pStr - '0');
	
  }
  
  return lValue;  
}



/*
    Преоброзование значения int в строку

	@Value - значение;
	@pData - указатель на строку;

	@return - если все хорошо то возвращаем URC_OK, иначе ошибку;

*/
int IntToStr(INT32 Value, char *pData)
{
  	UINT8 Buff[15] = {0x00};//, *pPtr = &Buff[0] + 10;
	UINT8 Count = 14, sim=1;
   // 4 294 967 296
  
  	if(pData == NULL)
	  return -1;
  
	  
  	do
	{ 
	    sim++;
	    Count--;
	    Buff[Count] = (UINT8)(Value % 10) + '0';
	  
//	    Count++;
//      	*(--pPtr) = (Value % 10) + '0';
      	Value = (UINT32)(Value/10);
	  
	}while(Value);
	
	Buff[14]=0x00;
	
//	MemCpy( (uint8_t*)pData, pPtr, Count+1);
	MemCpy( (UINT8*)pData, &Buff[Count], sim);
  
  	return URC_OK;
}






