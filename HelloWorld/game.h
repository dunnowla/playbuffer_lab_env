#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"

// Declaring the SpawnBall function
void SpawnBall();
// Declaring the StepFrame function that takes a parameter of the time since the last step 
void StepFrame(float timeSinceLastStep);
// Declaring the SetupScene function
void SetupScene();