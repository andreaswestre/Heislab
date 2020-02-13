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


#endif /* elevator_logic_h */
typedef enum{
    FLOOR_1,FLOOR_2,FLOOR_3,FLOOR_4
}floor_numbers;

void current_floor_reader(*floor_numbers);
