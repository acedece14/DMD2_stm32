/*

   file  TEST_LEDP.c

*/



#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


#include "HAL_Delay.h"
#include "hal_SPI.h"

#include "TEST_LEDP.h"





#define EN_PIN    GPIO_Pin_0
#define A_PIN     GPIO_Pin_1
#define B_PIN     GPIO_Pin_2
#define NSS_PIN   GPIO_Pin_4


#define NSS_PIN_clr()   GPIO_ResetBits(GPIOA, NSS_PIN);
#define NSS_PIN_Set()   GPIO_SetBits(GPIOA, NSS_PIN);


#define EN_PIN_clr()   GPIO_ResetBits(GPIOA, EN_PIN);
#define EN_PIN_Set()   GPIO_SetBits(GPIOA, EN_PIN);


#define A_PIN_clr()   GPIO_ResetBits(GPIOA, A_PIN);
#define A_PIN_Set()   GPIO_SetBits(GPIOA, A_PIN);
#define B_PIN_clr()   GPIO_ResetBits(GPIOA, B_PIN);
#define B_PIN_Set()   GPIO_SetBits(GPIOA, B_PIN);


#define SHOW_EN(x)    EN_PIN_Set(); \
                      HAL_Delay_ms(x); \
                      EN_PIN_clr()

                        
                        
                        
                        
                        
                        
                        
                        
                        
static void aux_init_Periph(void)
{
   GPIO_InitTypeDef   GPIO_InitStructure;  
   
   
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
   
    //                             
   GPIO_InitStructure.GPIO_Pin = EN_PIN | A_PIN | B_PIN | NSS_PIN;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   
   hal_SPI_Init();

   NSS_PIN_Set();
   EN_PIN_clr();
   
   A_PIN_clr();
   B_PIN_clr();
   
   
   return;
}




void TEST_LEDP_Start(void)
{
   uint8_t repeat = 10;
  
     // инициализируем модули
    aux_init_Periph();                     
    
  
    // загоняем данные в строку
    for(uint8_t i=0; i<16; i++)
        (void)hal_SPI_SendByte(0x00);
    
    // применяем данные в сдвиговом регистре
    NSS_PIN_clr();
    HAL_Delay_us(100);
    NSS_PIN_Set();
    
    
    // далее по очереди зажикаем строки
    while(repeat--)
    {
          A_PIN_clr();  
          B_PIN_clr();
          SHOW_EN(10);
          
          A_PIN_Set();  
          B_PIN_clr();
          SHOW_EN(10);    

          A_PIN_clr();  
          B_PIN_Set();
          SHOW_EN(10);

          A_PIN_Set();  
          B_PIN_Set();
          SHOW_EN(10);
    }
    

   return;
}

