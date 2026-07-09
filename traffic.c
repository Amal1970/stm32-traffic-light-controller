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

void change_state(state new_state){
    traffic_controller.current_state = new_state;
    traffic_controller.state_start_tick = g_tick_count;

    if(new_state == EMERGENCY || new_state == PEDESTRIAN){
        traffic_controller.blue_led_tick = g_tick_count;
    }
}

static void update_leds(state current_state){
    led_off(LED_GREEN);
    led_off(LED_ORANGE);
    led_off(LED_RED);

    switch(current_state){
        case GREEN :
            led_on(LED_GREEN);
            break;

        case YELLOW :
            led_on(LED_ORANGE);
            break;

        case RED :
        case PEDESTRIAN :
        case EMERGENCY :
            led_on(LED_RED);
            break;

        default:
            break;
    }
}

static void clear_pedestrian_request(void){
    traffic_controller.is_pedestrian = 0;
}

static void clear_emergency_request(void){
    traffic_controller.is_emergency = 0;
}

static void update_blue_led(uint32_t toggle_rate){
        if(((g_tick_count)-(traffic_controller.blue_led_tick))>=toggle_rate){
            led_toggle(LED_BLUE);
            traffic_controller.blue_led_tick = g_tick_count;
        }
}

void traffic_update(void){
    // traffic update 
    if(traffic_controller.is_emergency && traffic_controller.current_state != EMERGENCY){
        change_state(EMERGENCY);
    }

    uint32_t elapsed_time = g_tick_count - traffic_controller.state_start_tick;



    switch(traffic_controller.current_state){
        case GREEN :
            if(elapsed_time>=GREEN_TIME){
                change_state(YELLOW);
            }
            update_leds(traffic_controller.current_state);
            break;

        case YELLOW :
            if(elapsed_time>=YELLOW_TIME){
                change_state(RED);
            }
            update_leds(traffic_controller.current_state);
            break;

        case RED :
            update_leds(traffic_controller.current_state);

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
            update_leds(traffic_controller.current_state);

            // need to toggle it every 500ms
            update_blue_led(PEDESTRIAN_TOGGLE_RATE);
            

            if(elapsed_time>=PEDESTRIAN_TIME){
                clear_pedestrian_request();
                change_state(GREEN);
                led_off(LED_BLUE);
            }
            break;
        case EMERGENCY : 
            update_leds(traffic_controller.current_state);

            update_blue_led(EMERGENCY_TOGGLE_RATE);

            if(elapsed_time>=EMERGENCY_TIME){
                clear_emergency_request();
                change_state(GREEN);
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