 
#include "DMD2.h" 

#include "hal_SPI.h"
#include "hal_IO.h"
#include "hal_TIM2.h"

// Port registers are same size as a pointer (16-bit on AVR, 32-bit on ARM)
typedef intptr_t port_reg_t;
 

class SPI
{ 
  public: 
    void begin();                               // INIT SPI
    void setBitOrder(uint8_t mode);             // set first bit - first or last 
    void setClockDivider(uint16_t value);       // set clock
    void transfer(uint8_t data);                // transfer data
};
 
void SPI::begin()
{
    
  hal_SPI_Init();
  
  return;  
}
 
void SPI::transfer(uint8_t data)
{ 
  data = 0x0F;     // test
  hal_SPI_SendByte(data);                
  return;  
}

// Установка разрядности ЫЗШ
void SPI::setBitOrder(uint8_t mode)
{        
   return;
}

void SPI::setClockDivider(uint16_t value)
{       
   return;
}     

SPIDMD::SPIDMD(byte panelsWide, byte panelsHigh)
  : BaseDMD(panelsWide, panelsHigh, 9, 6, 7, 8)
{
}

/* Create a DMD display using a custom pinout for all the non-SPI pins (SPI pins set by hardware) */
SPIDMD::SPIDMD(byte panelsWide, byte panelsHigh, byte pin_noe, byte pin_a, byte pin_b, byte pin_sck)
  : BaseDMD(panelsWide, panelsHigh, pin_noe, pin_a, pin_b, pin_sck)
{              
        
  beginNoTimer();
}


// STANISLAV
//write HIGH/LOW to selected pin
void digitalWrite(uint8_t pin, uint8_t state) {    
  if  (state > 1) state = 1;
  switch (pin) { 
    case 1 : pin = 0x01 ;
    break;
    case 2 : pin = 0x02 ;  
    break;
    case 3 : pin = 0x04 ;  
    break;
    
    case 5 : pin = 0x10 ; 
    break;    
  }
  hal_digitalWrite(GPIOA,  pin, state); 

  return;
}

//read HIGH/LOW from selected pin
uint8_t digitalRead(uint8_t pin) 
{
  return hal_digitalRead(GPIOA, pin);
}



//write analog value to selected pin 0-255
void analogWrite(uint8_t pin, uint16_t val)  // тут не известно назначение
{
  hal_TIM2_Set_OCC1(val); // установка скважности ШИМ
  
  return;
  
  
}



//set INPUT/OUTPUT to selected pin
void pinMode(uint8_t pin, uint8_t mode) 
{
    switch (pin) { 
    case 1 : pin = 0x01 ;
    break;
    case 2 : pin = 0x02 ;  
    break;
    case 3 : pin = 0x04 ;  
    break;                    
    case 5 : pin = 0x20 ; 
    break;    
  }
  hal_IO_InitPin(RCC_APB2Periph_GPIOA, GPIOA, pin,  mode );       
  return;
}









void BaseDMD::scanDisplay() {
  if(pin_other_cs >= 0 && digitalRead(pin_other_cs) != HIGH)
    return;
  // Rows are send out in 4 blocks of 4 (interleaved), across all panels

  int rowsize = unified_width_bytes();

  for (int i = 0; i < 10; i++)
    bitmap[i] = 0x0F;
  
  volatile uint8_t *rows[4] = { // Scanning out 4 interleaved rows
    bitmap + (scan_row + 0) * rowsize,
    bitmap + (scan_row + 4) * rowsize,
    bitmap + (scan_row + 8) * rowsize,
    bitmap + (scan_row + 12) * rowsize,
  }; 
  digitalWrite(pin_noe, LOW);
  digitalWrite(pin_sck, HIGH);   
  
  writeSPIData(rows, rowsize);
  
  digitalWrite(pin_sck, LOW);  
  
 
  // Digital outputs A, B are a 2-bit selector output, set from the scan_row variable (loops over 0-3),
  // that determines which set of interleaved rows we are outputting during this pass.
  // BA 0 (00) = 1,5,9,13
  // BA 1 (01) = 2,6,10,14
  // BA 2 (10) = 3,7,11,15
  // BA 3 (11) = 4,8,12,16
  uint8_t writeA = scan_row & 0x01;  
  uint8_t writeB = scan_row & 0x02;
  digitalWrite(pin_a, writeA);
  digitalWrite(pin_b, writeB);
  scan_row = (scan_row + 1) % 4;

  // Output enable pin is either fixed on, or PWMed for a variable brightness display
  if(brightness == 255)
    digitalWrite(pin_noe, HIGH);
  else
    analogWrite(pin_noe, brightness);
   
}
 
BaseDMD::BaseDMD(byte panelsWide, byte panelsHigh, byte pin_noe, byte pin_a, byte pin_b, byte pin_sck)
  :
  DMDFrame(panelsWide*PANEL_WIDTH, panelsHigh*PANEL_HEIGHT),
  scan_row(0),
  pin_noe(pin_noe),
  pin_a(pin_a),
  pin_b(pin_b),
  pin_sck(pin_sck),
  default_pins(pin_noe == 9 && pin_a == 6 && pin_b == 7 && pin_sck == 8),
  pin_other_cs(-1),
  brightness(255)
{
   begin();
}      

SPI spi; 
void SPIDMD::beginNoTimer()
{
  // Configure SPI before initialising the base DMD  
  spi.setBitOrder(MSBFIRST); 
  spi.begin();
#ifdef __AVR__
  spi.setClockDivider(SPI_CLOCK_DIV4); // 4MHz clock. 8MHz (DIV2 not DIV4) is possible if you have short cables. Longer cables may need DIV8/DIV16.
#else
  spi.setClockDivider(20); // 4.2MHz on Due. Same comment as above applies (lower numbers = less divider = faster speeds.)
#endif
  BaseDMD::beginNoTimer();
}

void SPIDMD::writeSPIData(volatile uint8_t *rows[4], const int rowsize)
{
  /* We send out interleaved data for 4 rows at a time */
  for(int i = 0; i < rowsize; i++) {
   spi.transfer(*(rows[3]++));
    spi.transfer(*(rows[2]++));
    spi.transfer(*(rows[1]++));   
    spi.transfer(*(rows[0]++));  
    /*spi.transfer(0x0F);     
    spi.transfer(0x0F);
    spi.transfer(0x0F);
    spi.transfer(0x0F);      */
  }
}

void BaseDMD::beginNoTimer()
{                            
  pinMode(pin_noe, OUTPUT);
  digitalWrite(pin_noe, LOW);
                              
  pinMode(pin_a, OUTPUT);
  digitalWrite(pin_a, LOW);
                             
  pinMode(pin_b, OUTPUT);
  digitalWrite(pin_b, LOW);
                              
  pinMode(pin_sck, OUTPUT);
  digitalWrite(pin_sck, LOW);

  clearScreen();
  scanDisplay();
}
