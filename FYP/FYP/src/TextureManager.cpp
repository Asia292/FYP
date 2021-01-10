#include "TextureManager.h"

TextureManager::TextureManager()
{
	//// SET SPRITES ////
	spritesheets["lvl1"] = loadSprite(".\\assets\\Lvl1.png");
}


std::shared_ptr<sf::Texture> TextureManager::loadSprite(std::string location)
{
	std::shared_ptr<sf::Texture> tex(new sf::Texture);
	if (!tex->loadFromFile(location))
		std::cout << "Cant load " << location << std::endl;

	return tex;
}

std::shared_ptr<sf::Texture> TextureManager::getTexture(std::string keyName)
{
	return spritesheets[keyName];
}

void TextureManager::setTexture(std::string keyName, Texture * target)
{
	//std::cout << "PASSED: " << spritesheets[keyName] << std::endl;
	target->setSpriteSheet(spritesheets[keyName]);
}

void TextureManager::setFrames(std::string keyName, std::vector<sf::IntRect> keyFrames)
{
	frames[keyName] = keyFrames;
}

void TextureManager::getFrames(std::string keyName, Texture * target)
{
	currState = keyName;
	target->setKeyFrames(frames[keyName], animTime[keyName]);
}

std::string TextureManager::getState()
{
	//std::cout << currState << std::endl;
	return currState;
}

TextureManager * TextureManager::onlyInstance = nullptr;
unsigned short int TextureManager::instanceCount = 0;
TextureManager * TextureManager::getInstance()
{
	if (instanceCount != 0)
		return onlyInstance;
	else
	{
		onlyInstance = new TextureManager;
		instanceCount = 1;
		return onlyInstance;
	}
}

void TextureManager::delInstance()
{
	//delete onlyInstance;
	onlyInstance = nullptr;
	instanceCount = 0;
}

TextureManager::~TextureManager()
{
	delInstance();
}