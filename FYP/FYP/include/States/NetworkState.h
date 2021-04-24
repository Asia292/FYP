#pragma once
/*!
\file NetworktState.h
*/

#define NOMINMAX
#include <Windows.h>
#include "LevelSelectState.h"
#include "noConnection.h"
#include "Client.h"

/*! \class LevelSelectState
\brief The state which holds the level select screen
*/
class NetworkState : public State
{
private:
	bool quit;		//!< If the state should quit
	bool isHost;
	Client client;
	sf::Clock clock;
	std::stack<State *> netStates;
	State *currState;

	noConnection *none;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

public:
	NetworkState() {};
	NetworkState(float Height, float Width, std::stack<State *>* States, bool host);		//!< Constructior
	virtual ~NetworkState() override;		//!< Overrides base deconstructor
	virtual void update(float timestep) override;		//!< Overrides base update
	void HandlePackets(const PacketID & id, sf::Packet & packet, Client * client);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Overrides base draw
	virtual void processKeyPress(sf::Keyboard::Key code) override;		//!< Overrides base key press
	virtual void processNetworkKeyPress(int code, Server* l_server, int id) override {};		//!< Overrides base network key press
	virtual void processKeyRelease(sf::Keyboard::Key code) override;		//!< Overrides base key release
	virtual void processNetworkKeyRelease(int code, Server* l_server, int id) override {};		//!< Overrides base network key release
	virtual bool getQuit() override { return quit; }	//!< Overrides base quit - returns quit bool

	virtual void noServer();

	//Function per packet type???
	virtual void levelSelectUpdate(int lvl, int back) override {};
	virtual void stateTransition(bool push) override {};
	virtual void playerUpdate(int player, int texture, int frame, bool flip, bool dead, sf::Vector2f pos) override {};
	virtual void levelUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position) override {};
	virtual void timeUpdate(int minute, int second) override {};
};