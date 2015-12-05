#ifndef PICBOX_H
#define PICBOX_H
#include "IUI_Object.h"

namespace Smoke
{
	class PicBox : public IUI_Object
	{
	private:
		float _width;
		float _height;

		/*
			Flag to show/unshow picBox (if you do not want 
			to delete the object but just hide it, use this)
		*/
		bool _active;		

	public:
		PicBox();
		~PicBox();

		////////////////////////
		// Overridden functions
		////////////////////////
		void Update(float deltaTime) override;
		void HandleEvent(IEvent* e) override;
		void Render() override;

		void Initialize(float width, float height, float offsetX, 
			float offsetY, bool active, std::string textureToUse);

		////////////////////////
		// Accessors / Mutators
		////////////////////////
		bool IsActive() { return _active; }
		void SetActive(bool value) { _active = value; }
	};
}

#endif