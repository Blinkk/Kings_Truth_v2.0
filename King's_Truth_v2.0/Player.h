#ifndef PLAYER_H
#define PLAYER_H
#include "IEntity.h"
#include "Vector.h"
#include "Inventory.h"
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

	/*
		This is the player inventory. It will hold
		all items for the player including weapons,
		ammo, extra hearts, etc.
	*/
	Inventory *_playerInventory;

public:
	Player();
	~Player();

	void HandleEvent(IEvent *e) override;
	void Update(float deltaTime) override;
	void Render() override;

	/////////////////////////
	// Utility Functions
	/////////////////////////
	void SetIdle() override;
	void KeepInBounds() override;
	void SetMovementFlags(bool left, bool right, bool up, bool down);
	void AddItemToInventory(IGameObject* item);

	/////////////////////////
	// Accessors / Mutators
	/////////////////////////
	Vector2 GetCurrentPos();
	RECT GetHitbox();
};

#endif