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
#include "HAL_Delay.h"

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
  SPIDMD dmd(2, 1, pin_noe,  pin_a,  pin_b, pin_sck);  
  dmd.setBrightness(255);
  dmd.selectFont(uni8);            
  //Usart2.Init(9600); // Инициализация USART порта на скорости 9600
  dmd.fillScreen(false);
  dmd.drawString(0 , 0, "Привет");
  hal_SPI_Init();
  hal_TIM2_Init();
  hal_TIM2_Set_OCC1(0xDDDD); 
  
  static int volatile drawMode = 0;     
  TTIMER  tim1 =  Timer_Create(1000);
  
  //String scrollText = "text";  
  
  //String  str = "string";
 
//  dmd.drawString(0,0, "test");   
 
  
  //dmd.drawString(0, 0, scrollText.c_str());
 // uint16_t scrollTextLen = dmd.stringWidth( scrollText.c_str(), uni8);
 
  while(1)   
  if(Timer_CheckStatus(tim1) == 0) {
    switch (drawMode) {
      case 0 : 
        dmd.drawString(0, 0, "Федо ");                       
        dmd.drawString(0, 8, "   М ");
        break;  
      case 1 : 
        dmd.clearScreen();          
        dmd.drawString(32, 0, "Федо 2 ");                       
        dmd.drawString(32, 8, "   М ");
        break;
      case 2 : 
        dmd.drawString(0, 0, "Тест");                       
        dmd.drawString(0, 8, "экрана");
        break;
      case 3 : 
        dmd.clearScreen();
        drawMode = -1;
        break;
      }          
      drawMode++;  
    Timer_SetTimeout(tim1, 1000);
    
  // MemAT45DB.Init();     // Инициализация интерфейса работы с памятью
  // AT45DB161
  };

}
