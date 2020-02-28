//
//  Emeregency_stop_logic.h
//  
//
//  Created by Aksel Vaaler on 28/02/2020.
//

#ifndef emeregency_stop_logic_h
#define emeregency_stop_logic_h

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "door_logic.h"
#include "floor_sensor_logic.h"
#include "queue_logic.h"

void stop_movement_and_set_stop_floor(float * current_floor_pointer, int * end_floor_pointer, int current_direction, int above_or_below);

void set_stop_light_and_remove_all_orders(order_status * order_array);

int currently_at_floor(int current_direction);

void exit_emergency_stop_mode(order_status *order_array, float current_floor, int *end_floor_pointer, int *current_direction_pointer);

void emergency_stop_mode(order_status *order_array, float * current_floor_pointer, int * end_floor_pointer, int * current_direction_pointer, int above_or_below);


#endif /* emeregency_stop_logic_h */
