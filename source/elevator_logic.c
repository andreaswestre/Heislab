//
//  elevator_logic.c
//  
//
//  Created by Aksel Vaaler on 13/02/2020.
//

#include "elevator_logic.h"


void current_floor_reader(){
    if (hardware_read_floor_sensor(0) && (*current_floor_pointer != FLOOR_1)){
        *current_floor_pointer = FLOOR_1;
        printf("Currently in floor 1");
        printf("\n");
    }
    if (hardware_read_floor_sensor(1) && (*current_floor_pointer != FLOOR_2)){
    *current_floor_pointer = FLOOR_2;
    printf("Currently in floor 2");
    printf("\n");
    } 
    
    if (hardware_read_floor_sensor(2) && (*current_floor_pointer != FLOOR_3)){
    *current_floor_pointer = FLOOR_3;
    printf("Currently in floor 3");
    printf("\n");
    }
    if (hardware_read_floor_sensor(3) && (*current_floor_pointer != FLOOR_4)){
    *current_floor_pointer = FLOOR_4;
    printf("Currently in floor 4");
    printf("\n");
    }
}

 