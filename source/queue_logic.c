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

void set_end_floor(int *end_floor_pointer, order_status *order_pointer, int current_floor){
    for(int i = 0; i<4; i++){

        if((order_pointer[i].UP==1) ||
           (order_pointer[i].DOWN==1) ||
           (order_pointer[i].OUT==1)){
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

void add_orders(order_status *add_order_pointer){
    for (int i = 0; i<4; i++) {
        if(hardware_read_order(i,HARDWARE_ORDER_UP)){
            add_order_pointer[i].UP = 1;
           // printf("Order UP: %d", i);
        }
        if(hardware_read_order(i,HARDWARE_ORDER_DOWN)){
            add_order_pointer[i].DOWN = 1;
            //printf("Order DOWN: %d", i);

        }
        if(hardware_read_order(i,HARDWARE_ORDER_INSIDE)){
            add_order_pointer[i].OUT = 1;
            //printf("Order OUT: %d", i);

        }
    }


}


int stop_or_continue(int current_floor,int end_floor, order_status *order_pointer){//Returns 1 if the elevator should stop
    if((order_pointer[current_floor].UP==1) && (end_floor>=current_floor)){
        return 1;
    }
    else if((order_pointer[current_floor].DOWN==1) && (end_floor<=current_floor)){
        return 1;
    }
    else if(order_pointer[current_floor].OUT==1){
        return 1;
    }
    else{
        return 0;
    }
}

void remove_orders(int current_floor, order_status *order_pointer){
    order_pointer[current_floor].UP = 0;
    order_pointer[current_floor].DOWN = 0;
    order_pointer[current_floor].OUT = 0;
}
