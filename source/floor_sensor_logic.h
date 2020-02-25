/**
 *@file
 *@brief Reads floor sensors and sets current floor variable.
 */

#ifndef floor_sensor_logic_h
#define floor_sensor_logic_h

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

/**
 *@brief The current floor.
 */
int current_floor;


/**
 *Pointer to the current floor.
 */
int * current_floor_pointer;//= &current_floor;

/**
 *@checks the current floor and sets the current floor variable.
 *@param current_floor_pointer pointer to current floor.
 */
int check_current_floor(int * current_floor_pointer);

#endif /* floor_sensor_logic_h */

