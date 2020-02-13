//
//  elevator_logic.h
//  
//
//  Created by Aksel Vaaler on 13/02/2020.
//

#ifndef elevator_logic_h
#define elevator_logic_h

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"



int queue[10];
int  queue_pos;

int check_button_pressed();

void current_floor_reader(int* current_floor_pointer);

void add_to_queue( int floor );

void find_direction( int current_floor );

#endif /* elevator_logic_h */
