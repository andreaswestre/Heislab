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

   int current_floor = 0;
   int * current_floor_pointer = &current_floor;
   int end_floor = 0;
   int * end_floor_pointer = &end_floor;

    //open_door();
    while(1){
        /*while(hardware_read_obstruction_signal()){
            add_orders(order_array);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);

        }*/
        add_orders(order_array);
        check_current_floor(current_floor_pointer);
        //printf("%d",current_floor);

        if(end_floor > current_floor){
                        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
    if(end_floor < current_floor){
                        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
        if(end_floor == current_floor){
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }
        /*switch (end_floor - current_floor)
        {
        case 0:
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        
        case 1 || 2 || 3:
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            break;

               
        default:
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN); 
            break;
        }*/
        
        if(stop_or_continue(current_floor,end_floor,order_array)){
            printf("Curren floor %d \n",current_floor );
            printf("ENDFLOOR %d \n",end_floor );
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
