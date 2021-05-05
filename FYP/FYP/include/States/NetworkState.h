#pragma once
/*!
\file NetworktState.h
*/

#define NOMINMAX
#include <Windows.h>
#include "LevelSelectState.h"
#include "noConnection.h"
#include "Client.h"

/*! \class NetworkState
\brief Derives from base state class - sets up and handles the networking
*/
class NetworkState : public State
{
private:
	bool quit;							//!< If the state should quit
	bool isHost;						//!< If host has been selected
	Client client;						//!< The client
	sf::Clock clock;					//!< Clock used to update client
	std::stack<State *> netStates;		//!< Stack of states held by the network state
	State *currState;					//!< The current state on the network state

	noConnection *none;					//!< Pointer to the no connection class, used when there is no server to connect to

	STARTUPINFO si;						//!< Start up information for the server
	PROCESS_INFORMATION pi;				//!< Process information for the server

public:
	NetworkState() {};		//!< Default constructor
	NetworkState(float Height, float Width, std::stack<State *>* States, bool host);		//!< Full constructior
	virtual ~NetworkState() override;		//!< Overrides base deconstructor
	virtual void update(float timestep) override;		//!< Overrides base update
	void HandlePackets(const PacketID & id, sf::Packet & packet, Client * client);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;		//!< Overrides base draw
	virtual void processKeyPress(sf::Keyboard::Key code) override;		//!< Overrides base key press
	virtual void processNetworkKeyPress(int code, Server* l_server, int id) override {};		//!< Overrides base network key press
	virtual void processKeyRelease(sf::Keyboard::Key code) override;		//!< Overrides base key release
	virtual void processNetworkKeyRelease(int code, Server* l_server, int id) override {};		//!< Overrides base network key release
	virtual bool getQuit() override { return quit; }	//!< Overrides base quit - returns quit bool

	void noServer();		//!< Creates no connection screen

	//Function per packet type
	virtual void levelSelectUpdate(int lvl, int back) override {};		//!< Updates the level select values - used only for networking - not needed in this state
	virtual void stateTransition(bool push) override {};		//!< Signifies if a state should be pushed or popped - used only for networking - not needed in this state
	virtual void playerUpdate(int player, int texture, int frame, bool flip, bool dead, sf::Vector2f pos) override {};		//!< Updates the player - used only for networking - not needed in this state
	virtual void levelUpdate(int object, int index, bool texture, int frame, float angle, sf::Vector2f position) override {};		//!< Updates all other objects in a level except the player - used only for networking - not needed in this state
	virtual void timeUpdate(int minute, int second) override {};		//!< Updates the time for the level - used only for networking - not needed in this state
};