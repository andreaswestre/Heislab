/**
 *@file
 *@brief Manages the open door signal and wait times.
 */

#ifndef elevator_logic_h
#define elevator_logic_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hardware.h"
#include "queue_logic.h"
/**
 *@brief Starts a timer loop of 3 seconds.
 */
void setTimeout();

/**
 *@brief Sets open door signal.
 */
void open_door();



#endif /* elevator_logic_h */
