//
//  queue_logic.h
//  
//
//  Created by Aksel Vaaler on 18/02/2020.
//

#ifndef queue_logic_h
#define queue_logic_h

#include <stdio.h>
#include <stdlib.h>

typedef enum{
    UP, DOWN, OUT
}order_type;

static order_type * order_array;


order_array = malloc(4*sizeof(order_type));
static order_type * next_floor_pointer = order_array+1;
static order_type * end_floor_pointer = order_array;
void manage_order_array(order_type * next_floor_pointer,order_type )
#endif /* queue_logic_h */
