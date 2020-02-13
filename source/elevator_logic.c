//
//  elevator_logic.c
//  
//
//  Created by Aksel Vaaler on 13/02/2020.
//

#include "elevator_logic.h"

int queue_pos = 0;


void add_to_queue( int floor ){ //Next "goal"
    queue[queue_pos] = floor;
    (queue_pos)++;
    if((queue_pos == 9)){
        queue_pos = 0;
    }
    printf("added to que");
}

int check_button_pressed(){
    if (hardware_read_order(2,HARDWARE_ORDER_UP) ){
        //add_to_queue(2);
//            printf("Button pressed\n");
        return 2;
    }
    return 2;
}


void find_direction(int current_floor){
    if (current_floor != -1){
        if(queue[queue_pos > current_floor]){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }else if(queue[queue_pos < current_floor]){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);

            }
    }
    
}


void current_floor_reader(int* current_floor_pointer){
    if (hardware_read_floor_sensor(0) && (*current_floor_pointer != 0)){
        *current_floor_pointer = 0;
        printf("Currently in floor 1");
        printf("\n");
    }
    if (hardware_read_floor_sensor(1) && (*current_floor_pointer != 1)){
    *current_floor_pointer = 1;
    printf("Currently in floor 2");
    printf("\n");
    } 
    
    if (hardware_read_floor_sensor(2) && (*current_floor_pointer != 2)){
    *current_floor_pointer = 2;
    printf("Currently in floor 3");
    printf("\n");
    }
    if (hardware_read_floor_sensor(3) && (*current_floor_pointer != 3)){
    *current_floor_pointer = 3;
    printf("Currently in floor 4");
    printf("\n");
    }
}

 