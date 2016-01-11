#ifndef STATICOBJECT_H
#define STATICOBJECT_H
#include "IITem.h"

class StaticObject : public IItem
{
private:

public:
	StaticObject();
	~StaticObject();

	/*
		Special Init function for Static Objects.
		Allows for use of same class for any object
		that is not meant to be interacted with (ie. Decorations, etc.)
	*/
	void Initialize(float posX, float posY, float rotationInRadians,
		float scaleX, float scaleY, unsigned int frameWidth,
		unsigned int frameHeight, unsigned int numCol,
		unsigned int startFrame, unsigned int endFrame,
		unsigned int delay, int animDirection, std::string textureToUse);

	void Initialize(float posX, float posY, float rotationInRadians) override;
	void Update(float deltaTime);
	void HandleEvent(IEvent*) override;
	void Render() override;


};

#endif