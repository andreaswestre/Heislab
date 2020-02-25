//
//  elevator_logic.c
//  
//
//  Created by Aksel Vaaler on 13/02/2020.
//

#include "Door_logic.h"


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
                add_orders(order_array);
        
    } while (milliseconds_since <= end);
    
}

void open_door(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_door_open(1);
    setTimeout();
    hardware_command_door_open(0);
    printf("Door is closed");
    
    
}


