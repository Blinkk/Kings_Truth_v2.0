#ifndef SWORD_H
#define SWORD_H
#include "IWeapon.h"

class Sword : public IWeapon
{
private:
	Collider hitBox;

public:
	Sword();
	~Sword();

	void Initialize(float posX, float posY, float rotationInRadians) override;

	////////////////////////
	// Overriden Functions
	////////////////////////
	void HandleEvent(IEvent*) override;
	void Update(float deltaTime) override;
	void Render() override;

	/////////////////////////
	// Accessors / Mutators
	/////////////////////////
	void SetIsInInventory(bool value);
	bool IsInInventory();
};

#endif