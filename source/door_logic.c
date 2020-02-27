//
//  elevator_logic.c
//  
//
//  Created by Aksel Vaaler on 13/02/2020.
//

#include "door_logic.h"


void setTimeout()
{
    int milliseconds = 3000;
    // If milliseconds is less or equal to 0
    // will be simple return from function without throw error
    if (milliseconds <= 0) {
        fprintf(stderr, "Count milliseconds for timeout is less or equal to 0\n");
        return;
    }
    
    // a current time of milliseconds
    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    
    // needed count milliseconds of return from this timeout
    int end = milliseconds_since + milliseconds;
    
    // wait while until needed time comes
    do {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
        if(add_orders(order_array)){
            set_end_floor(end_floor_pointer,order_array, current_direction);
            set_current_direction(end_floor,current_floor,current_direction_pointer);
        }
                
        
    } while (milliseconds_since <= end);
    while(hardware_read_obstruction_signal()){
        setTimeout();
    }
}

void open_door(){
    if(hardware_read_floor_sensor(0) || hardware_read_floor_sensor(1) || hardware_read_floor_sensor(2) || hardware_read_floor_sensor(3)  ){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_door_open(1);
    setTimeout();
    hardware_command_door_open(0);
    }
    
}


