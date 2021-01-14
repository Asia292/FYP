#include "Texture.h"

Texture::Texture()
{
	animated = false;
	background = false;
	flip = false;
	Loop = true;
	currFrame = 0;
	elTime = 0.f;
}

void Texture::nextFrame()
{
	if (Loop)
		currFrame = (currFrame + 1) % frames.size();
	else
	{
		if (currFrame < (frames.size() - 1))
		{
			currFrame++; 
			//std::cout << "Frame: " << currFrame << " Size: " << frames[currFrame].left << ", " << frames[currFrame].top << std::endl;

		}
	}
}

void Texture::setAnim()
{
	animated = !animated;
	//std::cout << "SWITCHING	" << animated << std::endl;
}


void Texture::setBg()
{
	background = true;
}

void Texture::setLoop(bool loop)
{
	Loop = loop;
}

void Texture::flipSprite()
{
	flip = !flip;
	//std::cout << flip << std::endl;
}

void Texture::setFlip(bool Flip)
{
	flip = Flip;
}

void Texture::setSpriteSheet(std::shared_ptr<sf::Texture> tex)
{
	spriteSheet = tex;
	//std::cout << "SET: " << spriteSheet << std::endl;
}

void Texture::setKeyFrames(std::vector<sf::IntRect> frams, float time)
{
	frames = frams;
	aTime = time;
}

void Texture::update(float timestep)
{
	//std::cout << animated << std::endl;
	if (animated)
	{
		elTime += timestep;
		//std::cout << elTime << std::endl;
		if (elTime > aTime / frames.size())
		{
			//std::cout << "HERE" << std::endl;
			nextFrame();
			elTime = 0.f;
		}
		//std::cout << aTime / frames.size() << std::endl;
		currSprite.setTexture(*spriteSheet, true);
		currSprite.setTextureRect(frames[currFrame]);
		//currSprite.setScale(sf::Vector2f(0.00275 - (int)flip * 0.0055, 0.00275f));	// 1 - (int)flip * 2
		currSprite.setOrigin(frames[currFrame].width / 2, frames[currFrame].height / 2);
	}
	else if (!animated && !background)
	{
		currSprite.setTexture(*spriteSheet, true);
		currSprite.setTextureRect(frames[currFrame]);
		currSprite.setOrigin(frames[currFrame].width / 2, frames[currFrame].height / 2);
	}
	else if (background)
	{
		currSprite.setTexture(*spriteSheet, true);
		currSprite.setPosition(0.f, 0.f);
		//std::cout << "SPRITESHEET: " << spriteSheet << std::endl;
		currSprite.setScale(sf::Vector2f(0.01f, 0.01f));	//0.00575f, 0.00775f
	}
}

void Texture::setPos(sf::Vector2f(pos))
{
	currSprite.setPosition(pos);
}

void Texture::setSize(sf::Vector2f(size))
{
	currSprite.setScale(size);
}

void Texture::setFrame(int frame)
{
	currFrame = frame;
}

void Texture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(currSprite, states);
}