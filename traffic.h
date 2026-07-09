#ifndef TRAFFIC_H_
#define TRAFFIC_H_

#include <stdint.h>

#define GREEN_TIME 5000
#define YELLOW_TIME 2000
#define RED_TIME 5000

#define PEDESTRIAN_TIME 5000
#define EMERGENCY_TIME 10000

#define PEDESTRIAN_TOGGLE_RATE 500
#define EMERGENCY_TOGGLE_RATE 100

typedef enum{
    GREEN,
    YELLOW,
    RED,
    PEDESTRIAN,
    EMERGENCY
}state;


typedef struct{
    state current_state;
    uint32_t state_start_tick;
    uint32_t blue_led_tick;
    uint8_t is_pedestrian;
    uint8_t is_emergency;
}Traffic_controller_t;


extern volatile uint32_t g_tick_count;

// prototypes
void traffic_init(void);
void traffic_update(void);
void pedestrian_request(void);
void emergency_request(void);

void change_state(state new_state);

#endif