#ifndef PLAYER_H
#define PLAYER_H
#include "IEntity.h"
using namespace Smoke;

class Player : public IEntity
{
private:

public:
	Player();
	~Player();

	void HandleEvent(IEvent *e) override;
	void Update(float deltaTime) override;
	void Render() override;

	void SetIdle() override;
	void KeepInBounds() override;
};

#endif