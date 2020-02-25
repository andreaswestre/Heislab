/**
 *@file
 *@brief Logic setup for elevator queue system
 */
#ifndef queue_logic_h
#define queue_logic_h

/**
 *@brief Types of order for each floor. Used in @c order_array.
 */
typedef struct{
    unsigned int UP;
    unsigned int DOWN;
    unsigned int OUT;
}order_status;

/**
 *@brief Array of 4 @c order_status, one element for each floor. Keeps track of all current orders.
 */
order_status order_array[4];

/**
 *@brief The farthest floor with a current order in the direction of movement.
 */
int end_floor;

/**
 *@brief Pointer to end floor.
 */
int * end_floor_pointer;

/**
 *@brief adds orders to @c order_array.
 *@param add_order_pointer pointer to @c order_status.
 */
void add_orders(order_status *add_order_pointer);

/**
 *@brief Updates @c end_floor.
 *@param end_floor_pointer pointer to the current end floor.
 *@param order_pointer pointer to the order array.
 *@param current_floor The current floor.
 */
void set_end_floor(int *end_floor_pointer, order_status *order_pointer,  int current_floor);

/**
 *@brief Stops the elevator on floors with current orders.
 *@param current_floor The current floor.
 *@param end_floor The current end floor.
 *@param order_pointer pointer to the order array.
 */
int stop_or_continue(int current_floor, int end_floor, order_status *order_pointer);

/**
 *@brief Removes orders on current floor if elevator has stopped.
 *@param current_floor The current floor
 *@param order_pointer pointer to the order array.
 */
void remove_orders(int current_floor, order_status *order_pointer);

void set_order_lights(order_status order_array);
#endif /* queue_logic_h */

