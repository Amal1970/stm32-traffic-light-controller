#include "traffic.h"
#include "led.h"

Traffic_controller_t traffic_controller;

void traffic_init(void){
    traffic_controller.current_state = GREEN;
    traffic_controller.state_start_tick = g_tick_count;
    traffic_controller.blue_led_tick = g_tick_count;
    traffic_controller.is_pedestrian = 0;
    traffic_controller.is_emergency = 0;
}

void traffic_update(void){
    // traffic update 
    uint32_t elapsed_time = g_tick_count - traffic_controller.state_start_tick;

    switch(traffic_controller.current_state){
        case GREEN :
            if(elapsed_time>=GREEN_TIME){
                // change state 
                traffic_controller.current_state = YELLOW;
                // update state start tick
                traffic_controller.state_start_tick = g_tick_count;
            }
            led_on(LED_GREEN);
            led_off(LED_ORANGE);
            led_off(LED_RED);
            break;

        case YELLOW :
            if(elapsed_time>=YELLOW_TIME){
                // change state 
                traffic_controller.current_state = RED;
                // update state start tick
                traffic_controller.state_start_tick = g_tick_count;
            }
            led_off(LED_GREEN);
            led_on(LED_ORANGE);
            led_off(LED_RED);
            break;

        case RED :
            led_off(LED_GREEN);
            led_off(LED_ORANGE);
            led_on(LED_RED);

            if(elapsed_time>=RED_TIME){
                if(traffic_controller.is_pedestrian){
                    traffic_controller.current_state = PEDESTRIAN;
                }
                else{
                    traffic_controller.current_state = GREEN;
                }
                traffic_controller.state_start_tick = g_tick_count;
            }
            break;
        case PEDESTRIAN :
            led_off(LED_GREEN);
            led_off(LED_ORANGE);
            led_on(LED_RED);

            // need to toggle it every 500ms
            if(((g_tick_count)-(traffic_controller.blue_led_tick))>=PEDESTRIAN_TOGGLE_RATE){
                led_toggle(LED_BLUE);
                traffic_controller.blue_led_tick = g_tick_count;
            }
            

            if(elapsed_time>=PEDESTRIAN_TIME){
                traffic_controller.is_pedestrian = 0;
                traffic_controller.current_state = GREEN;
                traffic_controller.state_start_tick = g_tick_count;
                led_off(LED_BLUE);
            }
            break;

        default :
            break;
        
    }
}


void pedestrian_request(void){
    traffic_controller.is_pedestrian = 1;
    // do the things 
}

void emergency_request(void){
    traffic_controller.is_emergency = 1;
}