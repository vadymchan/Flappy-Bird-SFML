//#include<SFML/Graphics.hpp> // нам это не нужно мы в заголовочном файле это уже объявили
#include "AssetManager.hpp"
 
namespace Vadym
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex; // использование словаря
		}
	}

	sf::Texture& AssetManager::GetTexture(std::string name) // что это такое???(возвращает текстуру по имени из библиотеки)
	{
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			_fonts[name] = font;
		}
	}

	sf::Font& AssetManager::GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}
}
