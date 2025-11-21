#include "paddle.h"
#include "Play.h"
#include "constants.h"

// Reference to the paddle
Paddle paddle;

// Draws the paddle
void DrawPaddle(const Paddle&  paddle)
{
	// Calculates the top left position of the paddle
    float topLeftX = paddle.xPos - paddleWidth / 2;
	float topLeftY = paddle.yPos - paddleHeight / 2;

	// Calculates the bottom right position of the paddle
	float bottomRightX = paddle.xPos + paddleWidth / 2;
	float bottomRightY = paddle.yPos + paddleHeight / 2;

	// Draws the paddle as a randomly coloured rectangle based on the previous calculated positions
	Play::DrawRect({topLeftX,topLeftY},{bottomRightX,bottomRightY}, Play::Colour(colorOne,colorTwo,colorThree));
}


// Updates the position of the paddle
void UpdatePaddle(Paddle& paddle)
{
	// Moves the paddle left if the left arrow or right if the right arrow is pressed
	if (Play::KeyDown(Play::KEY_LEFT))
	{
		paddle.xPos -= 1 * paddleSpeed;
	}
	if (Play::KeyDown(Play::KEY_RIGHT))
	{
		paddle.xPos += 1 * paddleSpeed;
	}

	// These statements stops the paddle from moving outside the screen borders 
	if (paddle.xPos < 40) 
	{
		paddle.xPos = 40;
	}
	if (paddle.xPos > DISPLAY_WIDTH - 45)
	{
		paddle.xPos = DISPLAY_WIDTH - 40;
	}
}