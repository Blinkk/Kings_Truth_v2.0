/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef DEBUG_H
#define DEBUG_H
#include "Font.h"
#include "IGameObject.h"
#include "IRenderableObject.h"
#include "Timer.h"

namespace Smoke
{
	class Debug : public IGameObject, public IRenderableObject
	{
	private:
		Font _fontObject;
		long _coreFrameRate;
		double _gameTime;
		float _deltaTime;
		Timer _frameTimer;
		
		Debug();

	public:
		
		~Debug();

		static Debug& GetInstance()
		{
			static Debug* pInstance = NULL;

			if (!pInstance)
			{
				pInstance = new Debug();
			}

			return (*pInstance);
		}

		bool Initialize();
		void Update(float deltaTime) override;
		void HandleEvent(IEvent *e) override;
		void Render() override;
		void Shutdown();

		//////////////////////
		// Utility functions
		//////////////////////
		void CalcFrameRate();
	};
}

#endif