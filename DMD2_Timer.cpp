 
#include "DMD2.h"
 
#include "hal_TIM2.h"

/*
  Uncomment the following line if you don't want DMD library to touch
  any timer functionality (ie if you want to use TimerOne library or
  similar, or other libraries that use timers.

  With timers enabled, on AVR-based Arduinos this code will register a
  Timer1 overflow handler (without disrupting any built-in library
  functions.) On ARM-based Arduino Due it will use use Timer7.

*/
 
// Forward declarations for tracking currently running DMDs
static void register_running_dmd(BaseDMD *dmd);
static bool unregister_running_dmd(BaseDMD *dmd);
static void inline scan_running_dmds();
 
void BaseDMD::begin() {           
  register_running_dmd(this);
}

void BaseDMD::end() {
}

 
 extern "C" void TIM2_IRQHandler()
{     
    GPIO_SetBits(GPIOB, GPIO_Pin_1);  
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);      /* Clear the Update pending bit */     
    scan_running_dmds(); 
    GPIO_ResetBits(GPIOB, GPIO_Pin_1); 
  return;
}
 
static volatile BaseDMD **running_dmds = 0;
static volatile int running_dmd_len = 0;

// Add a running_dmd to the list (caller must have disabled interrupts)
static void register_running_dmd(BaseDMD *dmd)
{
  int empty = -1;
  for(int i = 0; i < running_dmd_len; i++) {
    if(running_dmds[i] == dmd)
      return; // Already running and registered
    if(!running_dmds[i])
      empty = i; // Found an unused slot in the array
  }

  if(empty == -1) { // Grow array to fit new entry
    running_dmd_len++;
    BaseDMD **resized = (BaseDMD **)realloc(running_dmds, sizeof(BaseDMD *)*running_dmd_len);
    if(!resized) {
      // Allocation failed, bail out

      running_dmd_len--;
      return;
    }
    empty = running_dmd_len-1;
    running_dmds = (volatile BaseDMD **)resized;
  }
  running_dmds[empty] = dmd;
}

// Null out a running_dmd from the list (caller must have disabled interrupts)
static bool unregister_running_dmd(BaseDMD *dmd)
{
  bool still_running = false;
  for(int i = 0; i < running_dmd_len; i++) {
    if(running_dmds[i] == dmd)
      running_dmds[i] = NULL;
    else if (running_dmds[i])
      still_running = true;
  }
  return still_running;
}


// This method is called from timer ISR to scan all the DMD instances present in the running sketch
static void inline scan_running_dmds()
{
  for(int i = 0; i < running_dmd_len; i++) {
    BaseDMD *next = (BaseDMD*)running_dmds[i];
    if(next) {
      next->scanDisplay();
    }
  }
}
 
