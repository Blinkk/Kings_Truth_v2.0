#ifndef DUNGEONKEY_H
#define DUNGEONKEY_H
#include "IITem.h"

class DungeonKey : public IItem
{
private:

public:
	DungeonKey();
	~DungeonKey();

	void Initialize(float posX, float posY, float rotationInRadians) override;
	void Update(float deltaTime);
	void HandleEvent(IEvent*) override;
	void Render() override;
};

#endif