//
//  queue_logic.c
//
//
//  Created by Aksel Vaaler on 18/02/2020.
//

#include "queue_logic.h"
#include <stdio.h>
order_status order_array[4];

int end_floor = 0;
int *end_floor_pointer = &end_floor;

int current_direction = 0;
int *current_direction_pointer = &current_direction;

int above_or_below = 0;
int *above_or_below_pointer = &above_or_below;

void starting_procedure(float *current_floor_pointer, int *end_floor_pointer)
{
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN); //When program starts, elevator moves down to 1. floor.
    while (1)
    {

        for (int i = 0; i < 3; i++)
        {
            if (hardware_read_floor_sensor(i))
            {
                *current_floor_pointer = i;
                *end_floor_pointer = i;
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_floor_indicator_on(i);
                return;
            }
        }
    }
}

void set_end_floor(int *end_floor_pointer, order_status *order_array_pointer, int current_direction)
{
    for (int i = 0; i < 4; i++)
    {
        if ((order_array_pointer[i].UP == 1) ||
            (order_array_pointer[i].DOWN == 1) ||
            (order_array_pointer[i].INSIDE == 1))
        {
            if ((i > *end_floor_pointer) && (current_direction >= 0))
            {
                *end_floor_pointer = i;
            }
            else if ((i < *end_floor_pointer) && (current_direction <= 0))
            {
                *end_floor_pointer = i;
            }
        }
    }
}

void set_current_direction(int end_floor, float current_floor, int *current_direction_pointer)
{
    if (end_floor > current_floor)
    {
        *current_direction_pointer = 1;
    }
    else if (end_floor < current_floor)
    {
        *current_direction_pointer = -1;
    }
    else if (end_floor == current_floor)
    {
        *current_direction_pointer = 0;
    }
}

int set_movement(int current_direction)
{
    if (current_direction == 1)
    {

        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        return 1;
    }
    else if (current_direction == -1)
    {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        return 1;
    }
    else if (current_direction == 0)
    {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        return 0;
    }
    return 0;
}

void set_above_or_below(int *above_or_below_pointer, int current_direction)
{
    switch (current_direction)
    {
    case 1:
        *above_or_below_pointer = 1;
        break;

    case -1:
        *above_or_below_pointer = 0;
        break;
    }
}

int add_orders(order_status *order_array_pointer)
{
    int new_order = 0;
    for (int i = 0; i < 4; i++)
    {
        if ((hardware_read_order(i, HARDWARE_ORDER_UP)) && order_array_pointer[i].UP == 0)
        {
            order_array_pointer[i].UP = 1;
            new_order = 1;
        }
        if (hardware_read_order(i, HARDWARE_ORDER_DOWN) && order_array_pointer[i].DOWN == 0)
        {
            order_array_pointer[i].DOWN = 1;
            new_order = 1;
        }
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE) && order_array_pointer[i].INSIDE == 0)
        {
            order_array_pointer[i].INSIDE = 1;
            new_order = 1;
        }
    }
    set_order_lights(order_array);
    return new_order;
}

int stop_at_floor(float current_floor, int end_floor, order_status *order_array_pointer)
{ //Returns 1 if the elevator should stop
    if ((order_array_pointer[(int)current_floor].UP == 1) && (end_floor >= current_floor))
    {
        return 1;
    }
    else if ((order_array_pointer[(int)current_floor].DOWN == 1) && (end_floor <= current_floor))
    {
        return 1;
    }
    else if (order_array_pointer[(int)current_floor].INSIDE == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void remove_orders(float current_floor, order_status *order_array_pointer)
{
    order_array_pointer[(int)current_floor].UP = 0;
    order_array_pointer[(int)current_floor].DOWN = 0;
    order_array_pointer[(int)current_floor].INSIDE = 0;
    set_order_lights(order_array);
}

void set_order_lights(order_status *order_array_pointer)
{
    for (int i = 0; i < 4; i++)
    {
        hardware_command_order_light(i, HARDWARE_ORDER_UP, order_array_pointer[i].UP);
        hardware_command_order_light(i, HARDWARE_ORDER_DOWN, order_array_pointer[i].DOWN);
        hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, order_array_pointer[i].INSIDE);
    }
}
