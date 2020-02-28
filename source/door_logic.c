//
//  elevator_logic.c
//  
//
//  Created by Aksel Vaaler on 13/02/2020.
//

#include "door_logic.h"
int obstruction = 0;
int * obstruction_pointer = & obstruction;
void setTimeout(){
    int milliseconds = 3000;// a current time of milliseconds
    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC; // needed count milliseconds of return from this timeout
    int end = milliseconds_since + milliseconds;// wait while until needed time comes
    while (milliseconds_since <= end) {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
            if( add_orders(order_array)){
            remove_orders(current_floor,order_array);
            set_order_lights(order_array);
            set_end_floor(end_floor_pointer,order_array, current_direction);
            set_current_direction(end_floor,current_floor,current_direction_pointer);
            
        } 
        if(hardware_read_obstruction_signal()){
                *obstruction_pointer = 1;
                while( hardware_read_stop_signal() ){
            //break;
            hardware_command_stop_light(1);
            for (int i = 0; i<4; i++){
                remove_orders(i,order_array);
            }
        }
        hardware_command_stop_light(0);
                break;
            }
        while( hardware_read_stop_signal() ){
            //break;
            hardware_command_stop_light(1);
            for (int i = 0; i<4; i++){
                remove_orders(i,order_array);
            }
        }
        hardware_command_stop_light(0);

    }
    
}

void open_door(){
    if(hardware_read_floor_sensor(0) || hardware_read_floor_sensor(1) || hardware_read_floor_sensor(2) || hardware_read_floor_sensor(3)  ){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_door_open(1);
    setTimeout();
    while(*obstruction_pointer ){
        *obstruction_pointer = 0;
        setTimeout();
    }
    hardware_command_door_open(0);
    }
    
}


