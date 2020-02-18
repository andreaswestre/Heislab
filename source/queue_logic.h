//
//  queue_logic.h
//  
//
//  Created by Aksel Vaaler on 18/02/2020.
//

#ifndef queue_logic_h
#define queue_logic_h



typedef struct{
    int UP;
    int DOWN;
    int OUT;
}order_status;


order_status order_array[4];

int end_floor;

void add_orders(order_status *add_order_pointer);

void set_end_floor(int *end_floor_pointer, order_status *order_pointer,  int current_floor);

int stop_or_continue(int current_floor, int end_floor, order_status *order_pointer);

void remove_orders(int current_floor, order_status *order_pointer);
#endif /* queue_logic_h */
