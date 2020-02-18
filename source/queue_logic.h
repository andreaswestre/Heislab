//
//  queue_logic.h
//  
//
//  Created by Aksel Vaaler on 18/02/2020.
//

#ifndef queue_logic_h
#define queue_logic_h



typedef enum{
    UP, DOWN, OUT
}order_type;

order_type order_array[4];

order_type * next_floor_pointer;
order_type * end_floor_pointer;
void manage_order_array(order_type * next_floor_pointer,order_type);
#endif /* queue_logic_h */
