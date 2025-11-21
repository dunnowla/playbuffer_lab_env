#pragma once
// Variables for the dimensions of the display
const int DISPLAY_WIDTH = 640;
const int DISPLAY_HEIGHT = 360;
const int DISPLAY_SCALE = 2;
// Varaibles for the speed of the ball and the paddle
const float ballSpeed = 5;
const int paddleSpeed = 15;
// Varaibles for the starting positions of the bricks
const int startX = 5;
const int startY = 0;
// Variables for the dimensions of the bricks
const int brickHeight = 10;
const int brickWidth = 16;
// Variables for the dimensions of the paddle
const int paddleWidth = 80;
const int paddleHeight = 10;
// This represents the different object types
enum ObjectType
{
	TYPE_BALL,
	TYPE_BRICK
};

// Variables for the color of the paddle
extern int colorOne;
extern int colorTwo;
extern int colorThree;