#pragma once

#include "SDL.h"
#include "Game.h"
#include <vector>

class Actor 
{
public:
	enum class State {E_Active,E_Paused,E_Dead};

	Actor(class Game& game);
	virtual ~Actor();
	
	//called in Game
	void Update(float deltaTime);

	//refreshing all m_Components
	void UpdateComponents(float deltaTime);


	//getter & setters
	class Game& getGame() const { return m_Game; }
	State getState() const { return m_State; }

protected:

	virtual void UpdateActor(float deltaTime);

private:

	State m_State;

	//transform

	//components
	std::vector<class Component*> m_Components;
	
	//game
	class Game& m_Game;
};