#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "door_logic.h"
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

        if(add_orders(order_array)){
            set_end_floor(end_floor_pointer,order_array,current_floor, current_direction);
            if(current_direction==0){
                if(stop_or_continue(current_floor,end_floor,order_array)){
                remove_orders(current_floor,order_array);
                open_door();
            }
                else{
                    set_current_direction(end_floor,current_floor,current_direction_pointer);
                    set_movement(current_direction);
                }
            }
        }
        
        
        

     if(check_current_floor(current_floor_pointer)){
        if(stop_or_continue(current_floor,end_floor,order_array)){
            remove_orders(current_floor,order_array);
            set_end_floor(end_floor_pointer,order_array,current_floor, current_direction);
            open_door();
        }
         
     }
     

    if(hardware_read_stop_signal()){
        while(hardware_read_stop_signal()){

            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            for (int i = 0; i<4; i++){
                remove_orders(i,order_array);
            }
            
    }
    while(1){
        add_orders(order_array);
        
    }
        }
}
}
