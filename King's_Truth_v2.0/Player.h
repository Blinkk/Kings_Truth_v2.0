#ifndef PLAYER_H
#define PLAYER_H
#include "IEntity.h"
#include "Vector.h"
using namespace Smoke;

enum PLAYER_ANIM_STATES
{
	IDLE = 0,
	WALKING_LEFT,
	WALKING_RIGHT,
	WALKING_UP,
	WALKING_DOWN
};

enum KEY_PRESS
{
	UP = 0,	DOWN, LEFT, RIGHT
};

class Player : public IEntity
{
private:
	Vector2 _moveStartPos;
	Vector2 _currentPos;
	unsigned int _animState;
	unsigned int _lastKeyPress;
	bool _goLeft;
	bool _goRight;
	bool _goUp;
	bool _goDown;
	bool _canGoLeft;
	bool _canGoRight;
	bool _canGoUp;
	bool _canGoDown;
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

	// Mutators
	void SetMovementFlags(bool left, bool right, bool up, bool down);
};

#endif