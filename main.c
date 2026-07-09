#include <stdint.h>
#include "main.h"
#include "led.h"
#include "traffic.h"

volatile uint32_t g_tick_count = 0;

int main(){
    // code here is only for testing 
    led_init();

    traffic_init();

    pedestrian_request();

    systick_init(TICK_HZ);

    while(1);
}

void systick_init(uint32_t ticks){

    // store count value to counter register
    uint32_t count_value = (SYS_CLK_HZ/ticks)-1;
    SYST_RVR =count_value & 0x00FFFFFFU;

    SYST_CVR = 0;
    // enable exception
    SYST_CSR |=(1<<1);
    // set clock source
    SYST_CSR |=(1<<2);
    // enable counter
    SYST_CSR |=(1<<0);
}

void SysTick_Handler(void){
    g_tick_count++;
    traffic_update();
}