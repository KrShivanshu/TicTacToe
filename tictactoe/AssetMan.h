#pragma once
#include "State.h"
#include <map>
#include <memory>
//#include <string>
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;

namespace Engine {
	class AssetMan
	{
	private:
		map<string, unique_ptr<Texture> > _textureMap;
		map<string, unique_ptr<Font> > _fontMap;
	public:
		AssetMan();
		~AssetMan();;

		void AddTextures(const string id, const string filepath);
		void AddFont(const string id, const string filepath);

		Texture & GetTexture(string id);
		Font & GetFont(string id);

	};
}

