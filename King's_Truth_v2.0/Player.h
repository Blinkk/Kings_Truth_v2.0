#ifndef PLAYER_H
#define PLAYER_H
#include "IEntity.h"
#include "Vector.h"
using namespace Smoke;

class Player : public IEntity
{
private:
	Vector2 _moveStartPos;
	Vector2 _currentPos;
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
};

#endif