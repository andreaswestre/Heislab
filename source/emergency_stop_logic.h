/**
 *@file
 *@brief procedure for emergency stop.
 */

#ifndef emeregency_stop_logic_h
#define emeregency_stop_logic_h

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "door_logic.h"
#include "floor_sensor_logic.h"
#include "queue_logic.h"
/**
 *@brief stops elevator movement and sets stop floor to current floor if needed.
 *@param current_floor_pointer points to current floor.
 *@param end_floor_pointer points to end floor.
 *@param current_direction the current direction of movement.
 *@param above_or_below the position relative to current floor.
 */
void stop_movement_and_set_stop_floor(float * current_floor_pointer, int * end_floor_pointer, int current_direction, int above_or_below);

/**
 *@brief activates stop light and removes all orders.
 *@param order_array the order array.
 */
void set_stop_light_and_remove_all_orders(order_status * order_array);

/**
 *@brief checks if currently standing still at floor.
 *@param current_direction the current direction of movement.
 *@return returns 1 if at standstill at floor, 0 otherwise.
 */
int currently_at_floor(int current_direction);

/**
 *@brief special procedure for when leaving emergency stop mode while between floors. sets correct direction and movement.
 *@param order_array the order array.
 *@param current_floor the current floor.
 *@param end_floor_pointer points to end floor.
 *@param current_direction_pointer points to current direction.
 */
void exit_emergency_stop_mode(order_status *order_array, float current_floor, int *end_floor_pointer, int *current_direction_pointer);

/**
 *@brief Called when emergency stop button is pressed. stops movement, sets stop light and removes all orders. if elevator standing still at floor, leaves emergency stop mode when stop button is released. if between floors, waits for first new order, then sets correct direction and movement before leaving stop mode.
 *@param order_array the order array.
 *@param current_floor_pointer points to current floor.
 *@param end_floor_pointer points to end floor.
 *@param current_direction_pointer points to current direction.
 *@param above_or_below the position relative to current floor.
 */
void emergency_stop_mode(order_status *order_array, float * current_floor_pointer, int * end_floor_pointer, int * current_direction_pointer, int above_or_below);


#endif /* emeregency_stop_logic_h */
