#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include "Paddle.h"

void SpawnBall()
{
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 280 }, 4, "ball2");

	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;

}

void StepFrame(float timeSinceLastStep)
{
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);

	for (int i = 0; i < (ballIds.size()); i++)
	{
		int currentId = ballIds[i];
		Play::UpdateGameObject(Play::GetGameObject(currentId));
		if (Play::GetGameObject(currentId).pos.x > DISPLAY_WIDTH || Play::GetGameObject(currentId).pos.x < 0)
		{
			Play::GetGameObject(currentId).velocity.x = -Play::GetGameObject(currentId).velocity.x;
		}
		if (Play::GetGameObject(currentId).pos.y > DISPLAY_HEIGHT || Play::GetGameObject(currentId).pos.y < 0)
		{
			Play::GetGameObject(currentId).velocity.y = -Play::GetGameObject(currentId).velocity.y;
		}
		Play::DrawObject(Play::GetGameObject(currentId));
	}

	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int i = 0; i < (brickIds.size()); i++)
	{
		int currentId = brickIds[i];
		Play::UpdateGameObject(Play::GetGameObject(currentId));
		Play::DrawObject(Play::GetGameObject(currentId));
	}

	for (int i = 0; i < ballIds.size(); i++)
	{
		int currentBall = ballIds[i];
		for (int i = 0; i < brickIds.size(); i++)
		{
			int currentBrick = brickIds[i];
			if (Play::IsColliding(Play::GetGameObject(currentBall), Play::GetGameObject(currentBrick)))
			{
				Play::DestroyGameObject(currentBrick);
				Play::GetGameObject(currentBall).velocity = -Play::GetGameObject(currentBall).velocity;
			}
		}
	}

	DrawPaddle(paddle);
	UpdatePaddle(paddle);
}

void SetupScene()
{

	for (int row = 1; row <= 8; row++)
	{
		for (int col = 1; col <= 37; col++)
		{
			int x = startX + col * (brickWidth + gap);
			int y = DISPLAY_HEIGHT - (startY + (row + 1) * (brickHeight + gap));
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick2");
		}
	}
}

void IsColliding(const Paddle& paddle, const GameObject& obj)
{
	//const float dx = obj.pos.x - Max(topLeftX, Min(obj.pos.x, bottomRightX));
	//const float dy = obj.pos.y - Max(paddleTopLeft.y, Min(obj.pos.y, paddleBottomRight.y));
	//return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}