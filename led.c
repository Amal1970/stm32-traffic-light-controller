#include "led.h"

void led_init(void){
    // enable clock
    RCC_AHB1ENR |=(1<<3);

    // output mode 
    GPIOD_MODER &= ~((3<<24)|(3<<26)|(3<<28)|(3<<30));
    GPIOD_MODER |= (1<<24)|(1<<26)|(1<<28)|(1<<30);
}

void led_on(uint8_t pin){
    GPIOD_ODR |=(1<<(pin));
}

void led_off(uint8_t pin){
    GPIOD_ODR &= ~(1<<pin);
}

void led_toggle(uint8_t pin){
    GPIOD_ODR ^=(1<<pin);
}