#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator_logic.h"
#include "floor_sensor_logic.h"

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    while(1){
        if (hardware_read_floor_sensor(0)){
            break;
        }
    }
   hardware_command_movement(HARDWARE_MOVEMENT_STOP);


    while(1){

        add_orders(order_array);
        check_current_floor(current_floor_pointer);

        if(end_floor > current_floor){
                        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
    if(end_floor < current_floor){
                        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
        if(end_floor == current_floor){
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }
     
        if(stop_or_continue(current_floor,end_floor,order_array)){
            remove_orders(current_floor,order_array);
            open_door();
        }

         set_end_floor(end_floor_pointer,order_array,current_floor);

        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            for(int i =0; i<4; i++){
            printf("%d", order_array[i].UP);
            }
            printf("\n%d", end_floor);
            break;
        }
       
    }
}
