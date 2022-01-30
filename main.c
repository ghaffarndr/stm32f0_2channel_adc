// This program reads the analog voltage on PB4 and ...

#include "stm32f0xx.h"                  // Device header

static  uint32_t val1;
static  uint32_t val2;

static void delay(int dly)
{
  while( dly--);
}
 
static void initADC()
{ 
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;     					 // Turn on GPIOA
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;              // Turn on ADC   
  GPIOB->MODER |= (1<<10)|(1<<11)|(1<<12)|(1<<13); // Select analog mode for PB5/6   
  ADC1->CR |= (1u<<31);                            // Begin ADCCalibration   
  while ((ADC1->CR & (1u<<31)));                   // Wait for calibration complete:   
  ADC->CCR |= (1<<22);	                           // Enable the reference voltage  
  ADC1->CR |= (1<<0);                              // Enable the ADC 
}

int main()
{
	
  initADC();
  while(1) 
		{
		ADC1->CHSELR =0x00;
    ADC1->CHSELR |= (1<<5);
	  ADC1->CR |=  (1<<2);           // Trigger a conversion
	  while ( (ADC1->CR & (1<<2)) ); // Wait for End of Conversion      	
	  val1 = ADC1->DR;		         	 //Store the ADC conversion result
		ADC1->CR |=  (1<<4);           // stop conversion
    delay(100000);
			
		ADC1->CHSELR =0x00;	
  	ADC1->CHSELR |= (1<<6);
	  ADC1->CR |=  (1<<2);           // Trigger a conversion
	  while ( (ADC1->CR & (1<<2)) ); // Wait for End of Conversion 	
	  val2 = ADC1->DR;               //Store the ADC conversion result
		ADC1->CR |=  (1<<4);           // stop conversion 
		delay(100000);
  } 
}
