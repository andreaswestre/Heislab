#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "door_logic.h"
#include "floor_sensor_logic.h"
#include "queue_logic.h"

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
 
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

hardware_command_movement(HARDWARE_MOVEMENT_DOWN);    //When program starts, elevator moves down to 1. floor.
    while(1){
        if (hardware_read_floor_sensor(0)){
            break;
        }
    }
   hardware_command_movement(HARDWARE_MOVEMENT_STOP);


    while(1){

        if(add_orders(order_array)){                                                //Triggers when new order added.
            set_end_floor(end_floor_pointer,order_array, current_direction);        //If in movement, only set end floor further along current path if needed
            if(current_direction==0){                                               //If idle and order coming from current floor, open door
                if(stop_at_floor(current_floor,end_floor,order_array)){             //then set movement variables
                remove_orders(current_floor,order_array);
                open_door();
                set_end_floor(end_floor_pointer,order_array, current_direction);
                set_current_direction(end_floor,current_floor,current_direction_pointer);
                set_movement(current_direction);
                set_above_or_below(above_or_below_pointer, current_direction);
            }
                else{
                    set_current_direction(end_floor,current_floor,current_direction_pointer);
                    printf("%d", current_direction);
                    set_movement(current_direction);
                    set_above_or_below(above_or_below_pointer, current_direction);
                }
            }
        }
        
        

        

     if((new_floor_registered(current_floor_pointer))){                  //triggers when elevator reaches new floor.
        if(stop_at_floor(current_floor,end_floor,order_array)){        //Checks if elevator should stop at the floor.
            remove_orders(current_floor,order_array);
            set_current_direction(end_floor,current_floor,current_direction_pointer);
            set_end_floor(end_floor_pointer,order_array, current_direction);
            set_current_direction(end_floor,current_floor,current_direction_pointer);//If stopped, remove orders on floor, open door, and set queue variables.
            //printf("\n%d", end_floor);
            //printf("\n%d", current_direction);
            open_door();                                               //Then continue if unadressed orders, or stay put otherwise.
            set_movement(current_direction);
            set_above_or_below(above_or_below_pointer, current_direction);
        }
         
     }
     

    if(hardware_read_stop_signal()){                       //enter emergency stop mode
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        hardware_command_stop_light(1);
        int leave_stop_mode = 0;                           //leaves stop mode loop when set to 1.
                     //set to current floor or current floor+-0.5 if above or below.
        
        if(current_direction && ( ((int)(current_floor*10)%2) == 0)){ 
            end_floor = current_floor;

                                        //checks if elevator was moving before emergency stop
            switch (above_or_below) {                                                   //In addition, if current floor already has been incremented +-0.5
                case 1:                                                                 //it will not be further incremented before it is reset by a floor sensor.
                    current_floor+=0.5;
                    break;
                case 0:
                    current_floor-= 0.5;
                    break;
                }
                //printf("\n%f Current floor: ", current_floor);
            }
        else if(current_direction == 0){
            hardware_command_door_open(1);
        }
        while(1){
            for (int i = 0; i<4; i++){
                remove_orders(i,order_array);
            }
            while(!hardware_read_stop_signal()){
        hardware_command_stop_light(0);
                if(current_direction == 0){           // if stationory on floor can safely leave stop mode
                    leave_stop_mode = 1;
                    open_door();
                    break;
                }//endif(stop_position==current_floor)
                if(add_orders(order_array)){                //if between floors, must set direction depending on first new order before leaving stop mode.
                    set_end_floor(end_floor_pointer,order_array, 0);
                    if(end_floor>current_floor){
                        current_direction = 1;
                        set_movement(current_direction);
                        leave_stop_mode = 1;
                        break;
                    }//endif(end_floor>current_floor)
                    else if(end_floor<current_floor){
                        current_direction = -1;
                        set_movement(current_direction);
                        leave_stop_mode = 1;
                        break;
                    }//end else if(end_floor<current_floor)
                   
                }//endif(add_orders(order_array))
                if(leave_stop_mode){
                    break;
                }//endif(leave_stop_mode) (inner loop)
            }//endwhile(!hardware_read_stop_signal())
            if(leave_stop_mode){
                break;
            }//endif(leave_stop_mode) (outer loop)
        }//endwhile(1) (stop mode loop)
    }//endif(hardware_read_stop_signal())
}//endwhile(1) (main loop)
}//endmain()
