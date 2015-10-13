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
   unsigned char uiNumScript;  	// ����� �������
   unsigned char ucByte;		// ��������� ���� ( ��� - �� ���� ������� ��� �������)
   void *Ptr;
  
}T_FindScript;




/*
  ���������� ������ pData �������� ucValue

*/
void MemSet( unsigned char *pData, unsigned char ucValue, int size);



/*
	����������� ������ �� ������ ������ � ������

	@ pData - ������ ���� ����������� ������;
	@ ucValue - ������ ������ ����������� ������;
	@ Size - ������ ������� ���� �����������
*/
void MemCpy( unsigned char *pucData, unsigned char *pucValue, int Size);


/*
   ����� ������� pStr � ������ pData

	@ pData - ������ �������� ������� ������
	@ BufSize - ������ �������
	@ pStr - ������ ������� ������ � ������
	@ size - ������ ������

	@ return - ���� ����� ���������� ��������� �� ������, ���� ��� �� NULL
*/
void * MemStr( unsigned char *pData, unsigned int BufSize, unsigned char *pStr, int size);


/*
	����������� ��������� pStr � ����� ������ pDest
*/
void StrCat(char *pDest, char *pStr);


/*
	����������� ������ pStr � c����� pDest
*/
void StrCpy(char *pDest, char *pStr);

/*
	���������� ���������� �������� � ������
*/
int StrLen(char *pStr);



/*
    �������������� HEX - ������� � ������

	@ pDataIn - ������� hex-������
	@ pStrOut - �������� ������
	@ pilen - �� ����� ������ ������, �� ������ ������ ������ ( ������ ���� � ��� ���� ������)

	@ return - ���� ������������� ��� ������ �� URC_OK ����� ������
*/
int HexBufToStr(unsigned char *pDataIn, char *pStrOut, int *pilen);


/*
    �������������� �������� int - ������� � ������

	@ pData - ��������� ������������� ��������
	@ pStr - �������� ������
	@ pilen - �� ����� ������ ���������� int, �� ������ ������ ������ ( ������ ���� � ��� ���� ������)

	@ return - ���� ������������� ��� ������ �� URC_OK ����� ������
*/
int IntToHex(UINT8 *pData, char *pStr, int *pilen);



/*
  �������������� ������ � ����� �����
*/
long Atoi(char *pStr);


/*
    �������������� �������� int � ������

	@Value - ��������;
	@pData - ��������� �� ������;

	@return - ���� ��� ������ �� ���������� URC_OK, ����� ������;

*/
int IntToStr(INT32 Value, char *pData);



#endif // __HELP_FUNCTION_H__

