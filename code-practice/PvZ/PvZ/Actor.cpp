#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game& game)
	: m_State(State::E_Active), m_Game(game)
	//m_location
	,m_Scale(1.f),m_Rotation(0.f)
{
}

Actor::~Actor() 
{
	m_Game;

	m_Components.clear();
}

void Actor::Update(float deltaTime) 
{
	UpdateActor(deltaTime);
	UpdateComponents(deltaTime);
}
void Actor::UpdateComponents(float deltaTime)
{
	for (auto& component : m_Components)
	{
		component->Update(deltaTime);
	}
}
void Actor::AddComponent(std::shared_ptr<Component> component) 
{
	//m_Components.push_back(component);
	auto iter = m_Components.begin();
	for (;iter != m_Components.end(); iter++) 
	{
		if ((*iter)->GetUpdateOrder() > component->GetUpdateOrder())
			break;
	}
	m_Components.insert(iter,component);

}
void Actor::RemoveComponent(std::shared_ptr<Component> component)
{
	auto iter = std::find(m_Components.begin(),m_Components.end(),component);

	if (iter != m_Components.end()) 
	{
		m_Components.erase(iter);
	}
}

void Actor::UpdateActor(float deltaTime)
{
	if (m_State == State::E_Paused)
		return;
}

