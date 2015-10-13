#define TEST
#define __cplusplus
#include "stm32f10x.h" 
#include "ConfigSys.h"
#include "hal_uart.h"

#include "MyDefine.h"

#include "TermMain.h"
 
int main()
{
  RCC_Configuration();  
 // ConfigSys_LedGpioEnable();       
     // Точка входа в приложение;     
  TermMain();
  return 0;
} 