#include<stdio.h>
#include<stm32f4xx.h>
#include<stdint.h>
#include<uart.h>
#include  "adc.h"
#include  "systic.h"
#include "tim.h"
#include "exti.h"

#define GPIOAEN				   (1U<<0)
#define GPIOA_5				   (1U<<5)

#define LED_PIN				   GPIOA_5

static void dma_callback(void);



int main(void)
{
    char message[31]= "Hello from stm32 transfer\n\r";
	/*1.Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	uart2_tx_init();
	dma1_stream6_init((uint32_t) message, (uint32_t)&USART2->DR,  31);

	while(1)
	{

	}

}


static void dma_callback(void)
{
    GPIOA->ODR |= LED_PIN;
}

void DMA1_Stream6_IRQHandler(void)
{
	/*check for complete transfer interrupt*/
	if(DMA1->HISR & HISR_TCIF)
	{
		/*cler flag*/
		DMA1->HIFCR |=HIFCR_CTCIF6;
		//Do something
        dma_callback();
	}
	/**/
}






