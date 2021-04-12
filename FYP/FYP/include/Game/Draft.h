#pragma once

#include "Sensor.h"

class Draft : public Sensor
{
private:
	float angle;
	b2Body *player;
public:
	Draft() {};
	Draft(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, const float orientation);

	virtual void onAction(b2Body * other) override;		//!< Action to do when sensor is triggered
	virtual void offAction(b2Body * other) override;		//!< Action to do when sensor stops being triggered
	void update(float timestep) override;
};