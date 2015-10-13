/*
    File ConfigSys.h

*/


#ifndef __CONFIG_SYS_H__
#define __CONFIG_SYS_H__


/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void);



/*
   Инициализация порта светодиода
*/
void ConfigSys_LedGpioEnable(void);



#endif // __CONFIG_SYS_H__

