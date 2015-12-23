#ifndef SWORD_H
#define SWORD_H
#include "IWeapon.h"
#include "Collider.h"

class Sword : public IWeapon
{
private:
	Collider hitBox;

public:
	Sword();
	~Sword();

	///////////////////////////////////////
	// Use to initialize sword
	//
	// TODO: Add more parameters as needed
	///////////////////////////////////////
	void Initialize(float posX, float posY, float rotationInRadians);

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