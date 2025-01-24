#ifndef TIMER_H
#define TIMER_H

#include "Common.h"

// Structure to represent a Timer, with a current time and a maximum duration.
typedef struct Timer
{
	float current;
	float max;
} Timer;

//*@brief Initializes a Timer structure.
//*
//* This function sets the timer's current time to zero and assigns
//* the maximum duration to the provided value.
//*
//*@param _timer Pointer to the Timer to initialize.
//*@param _maxValue Maximum duration of the timer.
void InitTimer(Timer* _timer, float _maxValue);

//* @brief Updates the Timer based on the elapsed time.
//*
//* Adds the elapsed time(delta time) to the current time of the timer.
//* This function does not reset the timer once it reaches the maximum value.
//*
//* @param _dt Delta time(time elapsed since the last update).
//* @param _timer Pointer to the Timer to update.
void UpdateTimer(float _dt, Timer* _timer);


//@brief Checks if the Timer has finished.
//
//Determines whether the timer's current time has reached or exceeded its maximum duration.
//
//@param _timer Pointer to the Timer to check.
//@return sfBool True if the timer has finished, false otherwise.
//
//sfBool IsTimerFinished(Timer * _timer);
sfBool IsTimerFinished(Timer* _timer);

#endif
