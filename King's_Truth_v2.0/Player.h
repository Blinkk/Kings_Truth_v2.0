#ifndef PLAYER_H
#define PLAYER_H
#include "IEntity.h"
#include "Vector.h"
using namespace Smoke;

enum Player_Animation_States
{
	IDLE = 0,
	WALKING_LEFT,
	WALKING_RIGHT,
	WALKING_UP,
	WALKING_DOWN
};

class Player : public IEntity
{
private:
	Vector2 _moveStartPos;
	Vector2 _currentPos;
	unsigned int _animState;
	bool _goLeft;
	bool _goRight;
	bool _goUp;
	bool _goDown;
	float _speed;

public:
	Player();
	~Player();

	void HandleEvent(IEvent *e) override;
	void Update(float deltaTime) override;
	void Render() override;

	void SetIdle() override;
	void KeepInBounds() override;

	// Accessors
	Vector2 GetCurrentPos() { return _currentPos; }
	RECT GetHitbox() { return Renderer.GetBoundingBox(); }
};

#endif