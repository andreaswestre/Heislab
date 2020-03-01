//
//  Emeregency_stop_logic.c
//
//
//  Created by Aksel Vaaler on 28/02/2020.
//

#include "emergency_stop_logic.h"

void stop_movement_and_set_stop_floor(float *current_floor_pointer, int *end_floor_pointer, int current_direction, int above_or_below)
{
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    if (current_direction && (((int)(current_floor * 10) % 2) == 0))
    {
        end_floor = current_floor;

        //checks if elevator was moving before emergency stop
        switch (above_or_below)
        {       //In addition, if current floor already has been incremented +-0.5
        case 1: //it will not be further incremented before it is reset by a floor sensor.
            current_floor += 0.5;
            break;
        case 0:
            current_floor -= 0.5;
            break;
        }
    }
    else if (current_direction == 0)
    {
        hardware_command_door_open(1);
    }
}

void set_stop_light_and_remove_all_orders(order_status *order_array)
{
    hardware_command_stop_light(1);
    for (int i = 0; i < 4; i++)
    {
        remove_orders(i, order_array);
    }
}

int currently_at_floor(int current_direction)
{
    if (current_direction == 0)
    {
        return 1;
    }
    return 0;
}

void exit_emergency_stop_mode(order_status *order_array, float current_floor, int *end_floor_pointer, int *current_direction_pointer)
{

    set_end_floor(end_floor_pointer, order_array, 0);

    if (*end_floor_pointer > current_floor)
    {
        *current_direction_pointer = 1;
        set_movement(current_direction);
    }

    else if (*end_floor_pointer < current_floor)
    {
        *current_direction_pointer = -1;
        set_movement(current_direction);
    }
}

void emergency_stop_mode(order_status *order_array, float *current_floor_pointer, int *end_floor_pointer, int *current_direction_pointer, int above_or_below)
{

    stop_movement_and_set_stop_floor(current_floor_pointer, end_floor_pointer, *current_direction_pointer, above_or_below);
    int leave_stop_mode = 0;
    while (!leave_stop_mode)
    {

        set_stop_light_and_remove_all_orders(order_array);
        hardware_command_door_open(currently_at_floor(current_direction));

        while (!hardware_read_stop_signal())
        {
            hardware_command_stop_light(0);

            if (currently_at_floor(*current_direction_pointer))
            {
                open_door();
                leave_stop_mode = 1;
                break;
            }
            if (add_orders(order_array))
            {
                leave_stop_mode = 1;
                break;
            }
        }
    }
    exit_emergency_stop_mode(order_array, *current_floor_pointer, end_floor_pointer, current_direction_pointer);
}
