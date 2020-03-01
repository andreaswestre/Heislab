#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "door_logic.h"
#include "floor_sensor_logic.h"
#include "queue_logic.h"
#include "emergency_stop_logic.h"

int main()
{
    int error = hardware_init();
    if (error != 0)
    {
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    /*INIT*/
    printf("=== Årets heis ===\n");

    starting_procedure(current_floor_pointer, end_floor_pointer);
    /*INIT*/
    while (1)
    {

        if (add_orders(order_array))
        {                                                                     //Triggers when new order added.
            set_end_floor(end_floor_pointer, order_array, current_direction); //If in movement, only set end floor further along current path if needed
            if (current_direction == 0)
            { //If idle and order coming from current floor, open door
                if (stop_at_floor(current_floor, end_floor, order_array))
                { //then set movement variables
                    remove_orders(current_floor, order_array);
                    open_door();
                    set_end_floor(end_floor_pointer, order_array, current_direction);
                    set_current_direction(end_floor, current_floor, current_direction_pointer);
                    set_movement(current_direction);
                    set_above_or_below(above_or_below_pointer, current_direction);
                }
                else
                {
                    set_current_direction(end_floor, current_floor, current_direction_pointer);
                    set_movement(current_direction);
                    set_above_or_below(above_or_below_pointer, current_direction);
                }
            }
        }

        if (new_floor_registered(current_floor_pointer) && stop_at_floor(current_floor, end_floor, order_array) )
        { //triggers when elevator reaches new floor.
            //Checks if elevator should stop at the floor.
                remove_orders(current_floor, order_array);
                set_current_direction(end_floor, current_floor, current_direction_pointer);
                set_end_floor(end_floor_pointer, order_array, current_direction);
                set_current_direction(end_floor, current_floor, current_direction_pointer); //If stopped, remove orders on floor, open door, and set queue variables.
                open_door();                                                                //Then continue if unadressed orders, or stay put otherwise.
                set_movement(current_direction);
                set_above_or_below(above_or_below_pointer, current_direction);
        }

        if (hardware_read_stop_signal())
        { //enter emergency stop mode

            emergency_stop_mode(order_array, current_floor_pointer, end_floor_pointer, current_direction_pointer, above_or_below);
        }
    } //endwhile(1) (main loop)
} //endmain()
