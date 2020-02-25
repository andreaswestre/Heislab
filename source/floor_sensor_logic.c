//
//  floor_sensor_logic.c
//  
//
//  Created by Aksel Vaaler on 13/02/2020.
//

#include "floor_sensor_logic.h"


int current_floor = 0;

int * current_floor_pointer = &current_floor;

int check_current_floor(int * current_floor_pointer){
if(hardware_read_floor_sensor(0) && (*current_floor_pointer!=0)){
    *current_floor_pointer = 0;
    hardware_command_floor_indicator_on(0);
    return 1;
}
if(hardware_read_floor_sensor(1) && (*current_floor_pointer!=1)){
    *current_floor_pointer = 1;
    hardware_command_floor_indicator_on(1);
    return 1;
}
if(hardware_read_floor_sensor(2) && (*current_floor_pointer!=2)){
    *current_floor_pointer = 2;
    hardware_command_floor_indicator_on(2);
    return 1;
}
if(hardware_read_floor_sensor(3) && (*current_floor_pointer!=3)){
    *current_floor_pointer = 3;
    hardware_command_floor_indicator_on(3);
    return 1;
}
return 0;
}
