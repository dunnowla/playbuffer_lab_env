#pragma once

struct Paddle
{
	float xPos = 320;
	float yPos = 35;
};

extern Paddle paddle;



void DrawPaddle(const Paddle& paddle);
void UpdatePaddle(Paddle& paddle);