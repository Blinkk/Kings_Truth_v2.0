#include "Engine_Core.h"

namespace Smoke
{
	TextureManager::TextureManager()
	{
		// Make sure map is empty
		if (!_textureList.empty())
			_textureList.clear();
	}


	TextureManager::~TextureManager() {}


	bool TextureManager::Initialize()
	{
		///////////////////////////////
		// Get texture filenames and 
		// transparency keys from
		// a single file, then add
		// them to the _textureList
		///////////////////////////////
		std::ifstream textureFile("textureList.txt");

		// Store entire line to buffer
		std::string fileInput = "";

		// Filename of texture
		std::string fileName = "";

		// Color keys
		std::string alphaR = "";
		std::string alphaG = "";
		std::string alphaB = "";

		// Loop through entire file
		while (getline(textureFile, fileInput))
		{
			std::istringstream buffer(fileInput);
			buffer >> fileName >> alphaR >> alphaG >> alphaB;

			// Add "bin/" extension to filename
			fileName = "bin/" + fileName;

			// If transparency key is NULL, add texture w/ NULL key
			if (alphaR == "NULL" && alphaG == "NULL" && alphaB == "NULL")
				AddTexture(fileName, NULL);
			// Otherwise, get color key conversions and AddTexture w/ that key
			else
				AddTexture(fileName, D3DCOLOR_XRGB(atoi(alphaR.c_str()), atoi(alphaG.c_str()), atoi(alphaB.c_str())));

			// End loop at end of file
			if (textureFile.eof())
				break;
		}

		textureFile.close();
		return true;
	}


	void TextureManager::AddTexture(std::string textureToStore, D3DCOLOR transparencyKey)
	{
		HRESULT result;
		LPDIRECT3DTEXTURE9 pTexture = NULL;
		D3DXIMAGE_INFO _info;

		// Get width and height from bitmap file
		// and store in our _info object
		result = D3DXGetImageInfoFromFile(textureToStore.c_str(), &_info);
		if (result != D3D_OK)
		{
			debug << "\tUnable to get image info" << std::endl;
			pTexture = NULL;
			return;
		}

		// Create the new texture with bitmap file
		D3DXCreateTextureFromFileEx(
			g_Engine->GetDevice(),	// Direct3D device object
			textureToStore.c_str(),	// Bitmap filename
			_info.Width,            // Bitmap image width
			_info.Height,           // Bitmap image height
			1,						// Mip-map levels (1 for no chain)
			D3DPOOL_DEFAULT,		// Type of surface (standard)
			D3DFMT_UNKNOWN,			// Surface format (default)
			D3DPOOL_DEFAULT,		// Memory class for the texture
			D3DX_DEFAULT,			// Image filter
			D3DX_DEFAULT,			// Mip filter
			transparencyKey,		// Color key for transparency
			&_info,                 // Bitmap file info (from loaded file)
			NULL,					// Color palette
			&pTexture);				// Destination texture

		// Check that texture was created successfully
		if (result != D3D_OK)
		{
			debug << "\tFailed to create texture from file, name: " + textureToStore << std::endl;
			pTexture = NULL;
			return;
		}

		_textureList[textureToStore] = pTexture;
	}


	LPDIRECT3DTEXTURE9 TextureManager::RetrieveTexture(std::string textureToRetrieve)
	{
		// Create a texture pointer
		LPDIRECT3DTEXTURE9 texture = NULL;

		// Add "bin/" extension
		textureToRetrieve = "bin/" + textureToRetrieve;

		// Get the texture from the map
		if (_textureList[textureToRetrieve])
			texture = static_cast<LPDIRECT3DTEXTURE9>(_textureList[textureToRetrieve]);
		else
			debug << "\tFailed to retrieve texture, name: " + textureToRetrieve << std::endl;

		return texture;
	}


	void TextureManager::Shutdown()
	{
		debug << "\tTextureManager shutting down..." << std::endl;

		std::map<std::string, LPDIRECT3DTEXTURE9>::iterator tlIt;
		LPDIRECT3DTEXTURE9 temp = NULL;
		for (tlIt = _textureList.begin(); tlIt != _textureList.end(); ++tlIt)
		{
			// Get a temp pointer to the texture from map
			temp = static_cast<LPDIRECT3DTEXTURE9>(tlIt->second);

			if (temp == NULL)
				debug << "\t\tFailed to release a texture, name: " + tlIt->first << std::endl;
			else
				// Release texture
				temp->Release();
		}

		// Erase elements in map (should be NULL)
		_textureList.erase(_textureList.begin(), _textureList.end());

		if (_textureList.empty())
			debug << "\tTexture manager shutdown successfully" << std::endl;
		else
			debug << "\tError shutting down texture manager" << std::endl;
	}
}