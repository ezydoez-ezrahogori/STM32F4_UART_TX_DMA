/*
 * adc.h
 *
 *  Created on: Mar 31, 2023
 *      Author: user
 */
#include <stdint.h>
#ifndef ADC_H_
#define ADC_H_
void pa1_adc_init(void);
void start_conversion(void);
uint32_t read_adc(void);

uint32_t adc_read(void);


#endif /* ADC_H_ */
