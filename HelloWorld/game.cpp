#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include "Paddle.h"

using namespace Play;
int colorOne = 200;
int colorTwo = 50;
int colorThree = 100;

// This function Creates the Ball Gameobject and sets it velocity to the ballspeed variable
void SpawnBall()
{
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 280 }, 4, "ball2");

	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;

}
// This returns the larger float
float Max(float topLeft, float min)
{
	return (topLeft > min) ? topLeft : min;
}
// This returns the smaller float
float Min(float ballPos, float bottomRight)
{
	return (ballPos < bottomRight) ? ballPos : bottomRight;
}
// This function calculates what part of the brick that is the closest to the ball when colliding
float brickMin(float left, float right, float bottom, float top)
{
	float smallestX = (left < right) ? left : right;
	float smallestY = (top < bottom) ? top : bottom;

	return (smallestX < smallestY) ? smallestX : smallestY;
}
// This calculates if the ball is touching the paddle
bool isColliding(const Paddle& paddle, const GameObject& obj)
{
	// These get the top left coordinates of the paddle
	float topLeftX = paddle.xPos - paddleWidth / 2;
	float topLeftY = paddle.yPos - paddleHeight / 2;
	// These get the bottom right coordinates of the paddle
	float bottomRightX = paddle.xPos + paddleWidth / 2;
	float bottomRightY = paddle.yPos + paddleHeight / 2;

	// These find the closest point on the rectangle to the balls center 
	// by clamping the balls position to the paddle using the min and max functions
	const float dx = obj.pos.x - Max(topLeftX, Min(obj.pos.x, bottomRightX));
	const float dy = obj.pos.y - Max(topLeftY, Min(obj.pos.y, bottomRightY));
	// This returns true if the distance between the balls center and the closest point on the paddle 
	// is smaller than the balls radius
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}
// This updates everything inside the function every frame
void StepFrame(float timeSinceLastStep)
{
	// This gets all the ids for the balls
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	// This loops through all the ball objects, updates them, 
	// changes their velocity if they hit one of the screens borders,
	// destroys it if it hits the bottom of the screen,
	// draws the ball
	for (int i = 0; i < (ballIds.size()); i++)
	{
		int currentId = ballIds[i];
		Play::UpdateGameObject(Play::GetGameObject(currentId));
		if (Play::GetGameObject(currentId).pos.x > DISPLAY_WIDTH || Play::GetGameObject(currentId).pos.x < 0)
		{
			Play::GetGameObject(currentId).velocity.x = -Play::GetGameObject(currentId).velocity.x;
		}
		if (Play::GetGameObject(currentId).pos.y > DISPLAY_HEIGHT)
		{
			Play::GetGameObject(currentId).velocity.y = -Play::GetGameObject(currentId).velocity.y;
		}
		if (Play::GetGameObject(currentId).pos.y < 0)
		{
			Play::DestroyGameObject(currentId);
		}
		Play::DrawObject(Play::GetGameObject(currentId));
	}
	// This gets all the ids for the bricks
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	// This loops through all the brick objects, updates them and then draws them on the screen
	for (int i = 0; i < (brickIds.size()); i++)
	{
		int currentId = brickIds[i];
		Play::UpdateGameObject(Play::GetGameObject(currentId));
		Play::DrawObject(Play::GetGameObject(currentId));
	}
	// This loops through all the ball objects,
	for (int i = 0; i < ballIds.size(); i++)
	{
		int currentBall = ballIds[i];
		// This loops through all the brick objects
		for (int j = 0; j < brickIds.size(); j++)
		{
			int currentBrick = brickIds[j];
			// This checks if a ball is colliding with a  brick
			if (Play::IsColliding(Play::GetGameObject(currentBall), Play::GetGameObject(currentBrick)))
			{
				// This calculates where the edges of the brick are
				float brickLeft = Play::GetGameObject(currentBrick).pos.x - brickWidth / 2;
				float brickRight = Play::GetGameObject(currentBrick).pos.x + brickWidth / 2;
				float brickTop = Play::GetGameObject(currentBrick).pos.y - brickHeight / 2;
				float brickBottom = Play::GetGameObject(currentBrick).pos.y + brickHeight / 2;
				// This calculates the distance from the balls center to all of the edges of the brick
				float distLeft = fabs(Play::GetGameObject(currentBall).pos.x - brickLeft);
				float distRight = fabs(Play::GetGameObject(currentBall).pos.x - brickRight);
				float distTop = fabs(Play::GetGameObject(currentBall).pos.y - brickTop);
				float distBottom = fabs(Play::GetGameObject(currentBall).pos.y - brickBottom);
				// This destroys the brick
				Play::DestroyGameObject(currentBrick);
				// This calculates which edge that is closer to the balls center
				float minDistance = brickMin(distLeft, distRight, distTop, distBottom);
				// This changes the balls velocity based on where it hit the brick
				if (minDistance == distLeft || minDistance ==distRight)
				{
					// If it hit the left or right side it changes the balls x velocity
					Play::GetGameObject(currentBall).velocity.x = -Play::GetGameObject(currentBall).velocity.x;
				}
				else
				{
					// If it hit the top or bottom it changes the balls y velocity
					Play::GetGameObject(currentBall).velocity.y = -Play::GetGameObject(currentBall).velocity.y;
				}
			}
		}
	}
	// This changes the balls y velocity if it collides with the paddle
	// And changes the color of the paddel
	for (int i = 0; i < ballIds.size(); i++)
	{
		int currentBall = ballIds[i];
		GameObject& ball = Play::GetGameObject(currentBall);
		if(isColliding(paddle, ball))
		{
			ball.velocity.y = -ball.velocity.y;
			colorOne = 255;
			colorTwo = RandomRollRange(0, 150);
			colorThree = RandomRollRange(0, 100);
		}
	}

	// Calls the DrawPaddle and UpdatePaddle functions
	DrawPaddle(paddle);
	UpdatePaddle(paddle);
}
// This creates all the bricks for the game
void SetupScene()
{
	for (int row = 1; row <= 8; row++)
	{
		for (int col = 1; col <= 37; col++)
		{
			// These calculate where on the screen the bricks will be placed depending on it's row and column
			int x = startX + col * (brickWidth);
			int y = DISPLAY_HEIGHT - (startY + (row + 1) * (brickHeight));
			// This creates the brick objects so that we can draw them later
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick2");
		}
	}
}
