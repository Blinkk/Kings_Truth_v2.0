#ifndef SWORD_H
#define SWORD_H
#include "IWeapon.h"

class Sword : public IWeapon
{
private:

public:
	Sword();
	~Sword();

	///////////////////////////////////////
	// Use to initialize sword
	//
	// TODO: Add more parameters as needed
	///////////////////////////////////////
	void Initialize(float damage, float range);

	////////////////////////
	// Overriden Functions
	////////////////////////
	void HandleEvent(IEvent*) override;
	void Update(float deltaTime) override;
	void Render() override;
};

#endif