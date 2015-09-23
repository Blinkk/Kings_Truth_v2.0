#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <map>

/////////////////////////////////////////
// This is used to manage all textures
// for the game. It contains a map 
// of LPDIRECT3DTEXTURE9   
//////////////////////////////////////////

namespace Smoke
{
	class TextureManager
	{
	private:
		std::map<std::string, LPDIRECT3DTEXTURE9> _textureList;		// Map of textures

		TextureManager();

	public:
		~TextureManager();

		static TextureManager& GetInstance()
		{
			TextureManager *pInstance = NULL;

			if (!pInstance)
			{
				pInstance = new TextureManager();
			}

			return (*pInstance);
		}

		bool Initialize();
		void Shutdown();

		void AddTexture(std::string textureToStore, D3DCOLOR transparencyKey);
		LPDIRECT3DTEXTURE9 RetrieveTexture(std::string textureToRetrieve);
	};
}

#endif