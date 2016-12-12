/**
 * Handles the rotation of the stepper motor. This will lock and unlock
 * the door when the user has entered their pin.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */

#ifndef MOTOR_H
#define MOTOR_H


#include "../Config.h"

/**
 * Rotates the stepper motor counter clockwise.
 */
void Motor_RotateCounterClockwise(void);

/**
 * Rotates the stepper motor clockwise.
 */
void Motor_RotateClockwise(void);


#endif
