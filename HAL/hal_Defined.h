/*******************************************************************************

	hal_Defined.h

*******************************************************************************/


#ifndef  __HAL_DEFINED_H_
#define  __HAL_DEFINED_H_



typedef char			INT8;
typedef char*			PINT8;

typedef unsigned char	UINT8;
typedef unsigned char*	PUINT8;

typedef short			INT16;
typedef short*			PINT16;

typedef unsigned short	UINT16;
typedef unsigned short*	PUINT16;

typedef long long		INT32;
typedef long long*		PINT32;

typedef unsigned long long	UINT32;
typedef unsigned long long*	PUINT32;

typedef unsigned char	BOOL;

#define	TRUE	1
#define	FALSE	0

#ifndef NULL
#define NULL	0
#endif


typedef INT32	URC;



#define URC_OK	0


#define DIM(x)	sizeof(x)/sizeof(x[0])



#endif // __HAL_DEFINED_H_


