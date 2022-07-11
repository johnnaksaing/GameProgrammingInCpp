#pragma once

#include "SDL.h"
#include "Game.h"
#include "Component.h"
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
	
	// Add/remove components
	void AddComponent(std::shared_ptr<Component> component);
	void RemoveComponent(std::shared_ptr<Component> component);
protected:

	virtual void UpdateActor(float deltaTime);

private:

	//components
	std::vector<std::shared_ptr<Component>> m_Components;
	
	//game
	class Game& m_Game;
	State m_State;
	
	//transform
	float m_Scale;
	float m_Rotation;
};