/*
 * exti.c
 *
 *  Created on: Apr 3, 2023
 *      Author: Ezrah Buki
 */

#include<exti.h>

#define  GPIOCEN   (1U<<2)
#define  SYSCFGEN  (1U<<14)

void pc13_exti_init(void)
{
	/*disable global interrupt*/
	__disable_irq();
	/*Enable clock access to GPIOC*/
	RCC->AHB1ENR |= GPIOCEN;
	/*Enable clock acess to SYSCNFG*/
	RCC->APB2ENR |= SYSCFGEN;

	/*set PC13 as input */
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	/*select PORTC for EXTI13*/
	SYSCFG->EXTICR[3] |= (1U<<5);

	/*Unmask EXTI13*/
	EXTI->IMR |= (1U<<13);

	/*select falling edge trigger*/
	EXTI->FTSR |= (1U<<13);

	/*Enable EXTI13 line in NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	/*Enable global interrupts*/
	__enable_irq();









}
