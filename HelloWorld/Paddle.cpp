#include "paddle.h"
#include "Play.h"

Paddle paddle;

void DrawPaddle(Paddle& const paddle)
{
	Play::DrawRect({1,2},{2,2}, Play::cMagenta);
}