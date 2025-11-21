#pragma once

const int DISPLAY_WIDTH = 640;
const int DISPLAY_HEIGHT = 360;
const int DISPLAY_SCALE = 2;

const float ballSpeed = 15;
const int paddleSpeed = 15;

const int startX = 5;
const int startY = 0;
const int gap = 0;
const int brickHeight = 10;
const int brickWidth = 16;


enum ObjectType
{
	TYPE_BALL,
	TYPE_BRICK
};