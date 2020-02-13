//
//  floor_sensor_logic.h
//  
//
//  Created by Aksel Vaaler on 13/02/2020.
//

#ifndef floor_sensor_logic_h
#define floor_sensor_logic_h

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
static int current_floor_global;
int * current_floor_pointer;
void check_current_floor(int * current_floor_pointer);

#endif /* floor_sensor_logic_h */

