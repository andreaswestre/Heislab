//
//  queue_logic.c
//  
//
//  Created by Aksel Vaaler on 18/02/2020.
//

#include "queue_logic.h"


order_status order_array[4];

int end_floor = 0;
int * end_floor_pointer = &end_floor;

void set_end_floor(int *end_floor_pointer, order_status *order_array_pointer, int current_floor){
    for(int i = 0; i<4; i++){

        if((order_array_pointer[i].UP==1) ||
           (order_array_pointer[i].DOWN==1) ||
           (order_array_pointer[i].INSIDE==1)){
            if((i>*end_floor_pointer) &&
               (*end_floor_pointer>=current_floor)){
                *end_floor_pointer = i;
            }
            else if((i<*end_floor_pointer) &&
               (*end_floor_pointer<=current_floor)){
                *end_floor_pointer = i;
            }
        }
    }
}

void add_orders(order_status *order_array_pointer){
    for (int i = 0; i<4; i++) {
        if(hardware_read_order(i,HARDWARE_ORDER_UP)){
            order_array_pointer[i].UP = 1;
           // printf("Order UP: %d", i);
        }
        if(hardware_read_order(i,HARDWARE_ORDER_DOWN)){
            order_array_pointer[i].DOWN = 1;
            //printf("Order DOWN: %d", i);

        }
        if(hardware_read_order(i,HARDWARE_ORDER_INSIDE)){
            order_array_pointer[i].INSIDE = 1;
            //printf("Order INSIDE: %d", i);

        }
    }
    //set_order_lights(order_array);
}


int stop_or_continue(int current_floor,int end_floor, order_status *order_array_pointer){//Returns 1 if the elevator should stop
    if((order_array_pointer[current_floor].UP==1) && (end_floor>=current_floor)){
        return 1;
    }
    else if((order_array_pointer[current_floor].DOWN==1) && (end_floor<=current_floor)){
        return 1;
    }
    else if(order_array_pointer[current_floor].INSIDE==1){
        return 1;
    }
    else{
        return 0;
    }
}

void remove_orders(int current_floor, order_status *order_array_pointer){
    order_array_pointer[current_floor].UP = 0;
    order_array_pointer[current_floor].DOWN = 0;
    order_array_pointer[current_floor].INSIDE = 0;
}

/*void set_order_lights(order_status order_array){
    for(int i = 0; i<4; i++){
        hardware_command_order_light[i,HARDWARE_ORDER_UP,order_array[i].UP];
        hardware_command_order_light[i,HARDWARE_ORDER_DOWN,order_array[i].DOWN];
        hardware_command_order_light[i,HARDWARE_ORDER_INSIDE,order_array[i].INSIDE];
    }
}*/
