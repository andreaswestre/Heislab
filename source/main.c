#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator_logic.h"



int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    int current_goal = -1;
    int current_floor = 1;
    int *current_floor_pointer = &current_floor;
    while(1){
        
        current_goal = check_button_pressed();
        find_direction(current_goal);


        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }
        current_floor_reader(current_floor_pointer);
        /*if (hardware_read_order(3,HARDWARE_ORDER_INSIDE)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }
        if (hardware_read_order(2,HARDWARE_ORDER_INSIDE)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
        if (hardware_read_order(1,HARDWARE_ORDER_INSIDE)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
        
       
    
        if(hardware_read_floor_sensor(0)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }*/
    }
}

