#pragma once

#include "Component.h"
#include "Actor.h"

Component::Component(Actor& owner, int updateOrder)
	:
	std::enable_shared_from_this<Component>()
	, m_Owner(owner)
	, m_UpdateOrder(updateOrder)
{
	// Add to actor's vector of components
	m_Owner.AddComponent(std::make_shared<Component>(this));
}

Component::~Component()
{
	m_Owner.RemoveComponent(std::make_shared<Component>(this));
}

void Component::Update(float deltaTime)
{
}
