#include "noConnection.h"

noConnection::noConnection()
{
	texManager->setTexture("levelSelect", this);
	setBg();

	font.loadFromFile(".\\assets\\neuropol.ttf");

	noServer.setFont(font);
	noServer.setFillColor(sf::Color(255, 222, 0));
	noServer.setOutlineColor(sf::Color::Black);
	noServer.setOutlineThickness(3);
	noServer.setCharacterSize(50);
	noServer.setString("There is no server \n    to connect to!");
	noServer.setPosition(sf::Vector2f(200.f, 200.f));

	ok.setFont(font);
	ok.setFillColor(sf::Color(100, 32, 188));
	ok.setOutlineColor(sf::Color::Black);
	ok.setOutlineThickness(3);
	ok.setCharacterSize(50);
	ok.setString("OKAY");
	ok.setPosition(sf::Vector2f(420.f, 480.f));
}

void noConnection::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(currSprite, states);
	target.draw(noServer);
	target.draw(ok);
}

void noConnection::update(float timestep)
{
	Texture::update(timestep);
	currSprite.setScale(sf::Vector2f(1.0f, 1.0f));
}
