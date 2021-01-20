#pragma once
/*!
\file State.h
*/

#include <SFML/Graphics.hpp>
#include <iostream>

/*! \class Level
\brief Base class for all states
*/
class State : public sf::Drawable
{
public:
	virtual ~State() = default;
	virtual void update(float timestep) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

};