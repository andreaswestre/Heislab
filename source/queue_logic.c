//
//  queue_logic.c
//  
//
//  Created by Aksel Vaaler on 18/02/2020.
//

#include "queue_logic.h"

static order_type * order_array = order_array = malloc(4*sizeof(order_type));
static order_type * next_floor_pointer = order_array+1;
static order_type * end_floor_pointer = order_array;

