#pragma once
/*!
\file HomeSensor.h
*/

#include "Sensor.h"
#include "Player.h"

/*! \class HomeSensor
\brief Sensor that changes a bool held in player on contact to say when they have reached home
*/
class HomeSensor : public Sensor
{
private:
	Player * player;	//!< The player passed in constructor
	bool fade;
	int a;

	b2Fixture *fixture;		//!< The body's fixture
	b2Filter filter;		//!< Filter for body collisions

public:
	HomeSensor() {};		//!< Default constructor
	HomeSensor(b2World * world, const sf::Vector2f& position, sf::Vector2f& size, Player * play, TextureManager *texMan);		//!< Full constructor

	void onAction(b2Body * other) override;		//!< Action to do when sensor is triggered
	void offAction(b2Body * other) override;		//!< Action to do when sensor stops being triggered
	void update(float timestep) override;
	bool getFade() { return fade; }
	void setFade(bool Fade) { fade = Fade; }
};