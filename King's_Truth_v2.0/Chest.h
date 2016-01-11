#ifndef CHEST_H
#define CHEST_H
#include "IITem.h"

class Chest : public IItem
{
private:

public:
	Chest();
	~Chest();

	void Initialize(float posX, float posY, float rotationInRadians) override;
	void Update(float deltaTime);
	void HandleEvent(IEvent*) override;
	void Render() override;
};

#endif