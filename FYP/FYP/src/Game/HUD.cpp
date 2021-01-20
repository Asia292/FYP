#include "HUD.h"

HUD::HUD(TextureManager * texMan, sf::Font & font)
{
	eTime = 0;
	min = 0;
	sec = 0;
	passed = font;

	//// TIME TEXT ////
	time.setFont(passed);
	time.setFillColor(sf::Color::Yellow);
	time.setOutlineColor(sf::Color::Black);
	time.setOutlineThickness(1);
	time.setCharacterSize(40);
	time.setScale(sf::Vector2f(0.01f, 0.01f));
	time.setPosition(sf::Vector2f(6.40f, 0.10f));
}

void HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(time);
}

void HUD::update(float timestep)
{
	eTime += timestep;
	if (eTime > 1.f)
	{
		if (sec != 59)
			sec++;
		else
		{
			min++;
			sec = 0;
		}
		eTime = 0;
		//std::cout << min << ":" << sec << std::endl;
	}
	if (sec < 10)
		time.setString(std::to_string(min) + ":0" + std::to_string(sec));
	else
		time.setString(std::to_string(min) + ":" + std::to_string(sec));
}
