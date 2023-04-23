/*
 * tim.c
 *
 *  Created on: Apr 3, 2023
 *      Author: Ezrah Buki
 */
#include<stm32f4xx.h>

#define TIM2EN      (1U<<0)
#define TIM3EN      (1U<<1)

#define CR1_CEN     (1U<<0)
#define OC_TOGGLE   ((1U<<4) | (1U<<5))
#define  CCER_CC1E   (1U<<0)
#define   GPIOAEN    (1U<<0)
#define   AFR5_TIM    (1U<<20)
#define   AFR6_TIM    (1U<<25)
#define  CCER_CC1S    (1U<<0)



void tim2_1hz_init(void)
{
	/*Enable clock acess to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	/*Set PA5 to alternate function mode*/
	GPIOA-> MODER &=~ (1U<<10);
	GPIOA-> MODER |=  (1U<<11);
	/*Set PA5 alternate function type to TIM2_CH1(AF01) */
	GPIOA-> AFR[0] |= AFR5_TIM;
	/*Enabe clock acess to tim2*/

	/*Enable clock access to tm2*/
	RCC->AHB1ENR |= TIM2EN;
	/*Set Prescaler value*/
	TIM2->PSC = 1600-1 ;// 16 000 000/1600 =100000
	/*set auto-reload value*/
    TIM2->ARR = 10000-1; // 10000/10000 = 1
	/*Clear counter*/
    TIM2->CNT = 0;
	/*Enable counter*/
    TIM2->CR1 = TIM2EN;
}

void tim2_pa5_output_compare(void)
{
	/*Enable clock access to tm2*/
	RCC->AHB1ENR |= TIM2EN;
	/*Set Prescaler value*/
	TIM2->PSC = 1600-1 ;// 16 000 000/1600 =100000
	/*set auto-reload value*/
    TIM2->ARR = 10000-1; // 10000/10000 =1

    /*Set the output toggle compare mode*/
    TIM2->CCMR1 = OC_TOGGLE;
    /*Enable tim2 ch1 compare mode*/
    TIM2->CCER |= CCER_CC1E;


	/*Clear counter*/
    TIM2->CNT = 0;
	/*Enable counter*/
    TIM2->CR1 = TIM2EN;
}

void  tim3_input_capture(void)
{
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	/*Enable clock access to tm2*/
	GPIOA-> MODER &=~ (1U<<12);
	GPIOA-> MODER |=  (1U<<13);
	/*Set PA6 to alternate function type to TIM3_CH1(AF01)*/
	GPIOA->AFR[0] |= AFR6_TIM;

	/*Enable clock access to tm3*/
	RCC->APB1ENR |= TIM3EN ;

	/*set prescaler*/
	TIM3->PSC =16000 ; //16 000 000/16000

	/*set CH1 to capture to input mode */
	TIM3->CCMR1  = CCER_CC1S ;
	/*set CH1 to capture at  rising edge*/
	TIM3->CCER =CCER_CC1E;
	/*Enable TIM3*/
	TIM3->CR1 = CR1_CEN;
}














