#pragma once

struct Paddle
{
	// Variables for the paddles starting position
	float xPos = 320;
	float yPos = 35;
};
// A public variable for the paddle
extern Paddle paddle;
// Declaring the DrawPaddle function with a constant paddle reference as parameter
void DrawPaddle(const Paddle& paddle);
// Declaring the UpdatePaddle function with a paddle reference as parameter
void UpdatePaddle(Paddle& paddle);