

#include "hal_TIM2.h"
#include "HAL_Delay.h"

 uint8_t tim2_tmp = 2;
 uint32_t  tim2clk = 0;

 
 
 

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 
 

/*
    Вызывается на частоте дискритизации
 
 */
/*   
void TIM2_IRQHandler(void)
{
 
  
  
  
  return;
}
*/



extern "C" void TIM2_CC_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
    
    
//    uiCycCnt = hal_delay_getValueOfCycCnt();
//    hal_delay_ClearCycCnt();

  }
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
  }
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
  }
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);
  }
  
  return;
}



   /*
void TIM2_BRK_IRQHandler (void)
{
   return;
}
*/

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



/*
    Инициализация таймера и ШИМ
   
*/
extern "C" void hal_TIM2_Init(void)
{
  
     GPIO_InitTypeDef  GPIO_InitStructure;
     TIM_TimeBaseInitTypeDef TIM_TimeBase_InitStructure;
     TIM_OCInitTypeDef TIM_OC_InitStructure;
     TIM_BDTRInitTypeDef TIM_BDTRInitStructure;


   
     //Initialize clocks for TIM2
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
     
     //Initialize clocks for GPIOA, AFIO
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
     
     
     /*
     //Configure pin TIM2 CH1 = PA0 as alternative function push-pull
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
     GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
           */   
     GPIO_Init(GPIOA, &GPIO_InitStructure);   
     
     
     //Configure TIM2 time base
     TIM_DeInit(TIM2);
     TIM_TimeBaseStructInit( &TIM_TimeBase_InitStructure );
     TIM_TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
     TIM_TimeBase_InitStructure.TIM_Period = 65000;   
     TIM_TimeBase_InitStructure.TIM_Prescaler = 0;

     TIM_TimeBaseInit(TIM2, &TIM_TimeBase_InitStructure);
     
     
     
     
      TIM_OCStructInit( &TIM_OC_InitStructure );
      TIM_OC_InitStructure.TIM_Pulse        = 130;
      TIM_OC_InitStructure.TIM_OCMode       = TIM_OCMode_PWM1;
      TIM_OC_InitStructure.TIM_OutputState  = TIM_OutputState_Enable;
      TIM_OC_InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;

      //TIM_OC1Init(TIM2, &TIM_OC_InitStructure);
     
  
      
      // Automatic Output enable, Break, dead time and lock configuration   
      TIM_BDTRStructInit(&TIM_BDTRInitStructure);
      TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;   
      //TIM_BDTRConfig(TIM2, &TIM_BDTRInitStructure); 
      
      
 
     TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);    /* Enable the TIM Update Interrupt */
     
     
     /* 1 bit for pre-emption priority, 3 bits for subpriority */
     NVIC_SetPriorityGrouping(1); 

       /* Enable the TIM2 Interrupt */
     NVIC_SetPriority(TIM2_IRQn, 0x01); /* 0x00 = 0x01 << 3 | (0x00 & 0x7*/
     
     NVIC_EnableIRQ(TIM2_IRQn);          /* Enable TIM2 interrupt */
  
     
 
     
     
     TIM_Cmd(TIM2, ENABLE);  /* TIM counter enable */          
     
     return;
  
}

/*
    остановка таймера 
*/
extern "C" void hal_TIM2_DeInit(void)
{
   TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); 
   NVIC_DisableIRQ(TIM2_IRQn);
   TIM_Cmd(TIM2, DISABLE);  /* TIM counter disable */
  
   TIM_DeInit(TIM2);
  
       //DeInitialize clocks for TIM2
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
  
  return;  
}



/*
    Установка скважности ШИМ
*/
extern "C" void hal_TIM2_Set_OCC1(uint16_t value)
{
  
  TIM2->CCR1 = 0;
  
  return;  
}

