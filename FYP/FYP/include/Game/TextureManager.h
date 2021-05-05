#pragma once
/*!
\file TexManager.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Texture.h"

/*! \class TextureManager
\brief Sets up all texture data - spritesheets, key frames, and animation times
*/
class TextureManager
{
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> spritesheets;	//!< Holds the spritesheets
	std::map<std::string, std::vector<sf::IntRect>> frames;		//!< Holds the animation frames
	std::map<std::string, float> animTime;		//!< Holds the animation time
	std::string currState;		//!< The current state that the animation is in

	static unsigned short int instanceCount;		//!< The number of instances that exist
	static TextureManager *onlyInstance;		//!< Pointer to only instance that can exist

public:
	TextureManager();	//!< Default constructor
	~TextureManager();	//!< Deconstructor

	std::shared_ptr<sf::Texture> loadSprite(std::string location);		//!< Loads in the spritesheet from file
	std::shared_ptr<sf::Texture> getTexture(std::string keyName);		//!< Returns the spritesheet linked to entered string

	void setTexture(std::string keyName, Texture * target);		//!< Links the stated spritesheet to the target object
	void setFrames(std::string keyName, std::vector<sf::IntRect> keyFrames);	//!< Sets the key frames in the map
	void getFrames(std::string keyName, Texture * target);		//!< Links the stated key frames to the target object
	std::string getState();		//!< Returns the current state the animation is in

	static TextureManager * getInstance();		//!< Returns the instance if there is one or makes one if there isn't
	static void delInstance();		//!< Deletes the instance

};
