#include "paddle.h"
#include "Play.h"
#include "constants.h"

Paddle paddle;


void DrawPaddle(const Paddle&  paddle)
{
	int paddleWidth = 80;
	int paddleHeight = 10;

	int topLeftX = paddle.xPos - paddleWidth / 2;
	int topLeftY = paddle.yPos - paddleHeight / 2;

	int bottomRightX = paddle.xPos + paddleWidth / 2;
	int bottomRightY = paddle.yPos + paddleHeight / 2;

	Play::DrawRect({topLeftX,topLeftY},{bottomRightX,bottomRightY}, Play::cYellow);
}

void UpdatePaddle(Paddle& paddle)
{
	if (Play::KeyDown(Play::KEY_LEFT))
	{

		paddle.xPos -= 1 * paddleSpeed;
	}
	if (Play::KeyDown(Play::KEY_RIGHT))
	{
		paddle.xPos += 1 * paddleSpeed;

	}
	if (paddle.xPos < 40) 
	{
		paddle.xPos = 40;
	}
	if (paddle.xPos > DISPLAY_WIDTH - 45)
	{
		paddle.xPos = DISPLAY_WIDTH - 40;
	}
}