#pragma once
#include "Actor.h"
#include <memory>
class Component : public std::enable_shared_from_this<Component>
{
public:
	// Constructor
	// (the lower the update order, the earlier the component updates)
	Component(class Actor& owner, int updateOrder = 100);

	virtual void Initialize() {};
	virtual void Shutdown() {};

	// Destructor
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return m_UpdateOrder; }
protected:
	// Owning actor
	class Actor& m_Owner;
	// Update order of component
	int m_UpdateOrder;
};
