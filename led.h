
#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define LED_GREEN 12
#define LED_ORANGE 13
#define LED_RED 14
#define LED_BLUE 15

#define RCC_AHB1ENR *((volatile uint32_t *)0x40023830U)
#define GPIOD_MODER *((volatile uint32_t *)0x40020C00U)
#define GPIOD_ODR *((volatile uint32_t *)0x40020C14U)


// prototypes 
void led_init(void);
void led_on(uint8_t pin);
void led_off(uint8_t pin);
void led_toggle(uint8_t pin);

#endif



