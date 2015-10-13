#include "stm32f10x.h"      
#include "hal_IO.h"
#include "hal_uart.h"
#include "MyDefine.h"
#include "Help_Function.h"
#include "AT45DB161.h"

#include "TermMain.h"

#include "arial16b.h"
#include "uni8.h"

#include "DMD2.h"
#include "hal_TIM2.h" 
#include "hal_SPI.h"

#include "TEST_LEDP.h"
/*
     Точка входа в приложение

*/
 
void TermMain(void) {    
  
  //TEST_LEDP_Start();  
  /*
  pinMode(1, OUTPUT); 
  digitalWrite(1, 1);
  pinMode(2, OUTPUT);    
  digitalWrite(2, 1);
  pinMode(3, OUTPUT);
  digitalWrite(3, 1);
  pinMode(5, OUTPUT);
  digitalWrite(5, 1); 
 */ 
  byte pin_noe = 1; //D11  
  byte pin_a = 2;   //D10
  byte pin_b = 3;    //D09    ;
  byte pin_sck = 5;   //D07        
  SPIDMD dmd(1, 1, pin_noe,  pin_a,  pin_b, pin_sck);  
  dmd.setBrightness(255);
  dmd.selectFont(uni8);            
  //Usart2.Init(9600); // Инициализация USART порта на скорости 9600
  bool isStart = false;
  while(1) {
    //dmd.setPixel(1,1,GRAPHICS_ON);
    dmd.fillScreen(false);
  dmd.drawString(0 , 0, "Привет");
    
    //dmd.drawLine(0,0,15,31,GRAPHICS_ON);
    if (!isStart) {  
      hal_SPI_Init();
      hal_TIM2_Init();
      hal_TIM2_Set_OCC1(0xDDDD); // не определен TC_IER_CPCS
     // hal_SPI_Init();
      isStart = true;
    } 
  //  dmd.drawBox(1,1,3,3);
  // MemAT45DB.Init();     // Инициализация интерфейса работы с памятью
  // AT45DB161
  };

}
