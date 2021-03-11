#pragma once
/*!
\file Texture.h
*/

//#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

/*! \class Texture
\brief Manipulates textures
*/
class Texture : public sf::Drawable
{
protected:
	sf::Sprite currSprite;		//!< The current spritesheet
	std::vector<sf::IntRect> frames;	//!< Vector of key frames
	bool animated;		//!< If the texture is animated or not
	bool background;	//!< If the texture is the background
	bool flip;			//!< If the texture needs to be flipped
	std::shared_ptr<sf::Texture> spriteSheet;	//!< Spritesheet being used
	int currFrame;		//!< The current key frame
	float elTime;	//!< Elapsed time
	float aTime;	//!< Animation time
	bool Loop;		//!< If the key frames should loop

public:
	Texture();		//!< Default constructor
	void nextFrame();	//!< Advances the frames and resets to beginning if looped 
	void setAnim();		//!< Sets the animated bool to its opposite
	void setBg();		//!< Sets background bool to true
	void setLoop(bool loop);	//!< Specifies the loop bool
	void flipSprite();		//!< Sets the flipped bool to its opposite
	void setFlip(bool Flip);	//!< Specifies the flip bool
	void setSpriteSheet(std::shared_ptr<sf::Texture> tex);		//!< Assigns the spritesheet variable
	void setKeyFrames(std::vector<sf::IntRect> frams, float time);		//!< Assigns the frames and aTime variables
	void update(float timestep);		//!< Updates the animation based on bools
	void setPos(sf::Vector2f(pos));		//!< Sets the position of the sprite
	void setSize(sf::Vector2f(size));	//!< Sets the size of the sprite
	void setFrame(int frame);					//!< Reset frame to 0
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;		//!< Draws the current sprite
	int getFrame() { return currFrame; }
	bool getFlip() { return flip; }
};
