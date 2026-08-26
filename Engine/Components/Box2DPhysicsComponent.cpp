#include "pch.h"
#include "Box2DPhysicsComponent.h"
#include "Core/Factory.h"
#include "Framework/Actor.h"
#include "Math/MathUtils.h"
#include "Engine.h"


namespace nu
{
	FACTORY_REGISTER(Box2dPhysicsComponent)

	Box2dPhysicsComponent::Box2dPhysicsComponent(const Box2dPhysicsComponent& other)
	{
		m_bodyDef = other.m_bodyDef;
		m_size = other.m_size;
		m_scale = other.m_scale;
	}

	void Box2dPhysicsComponent::Start()
	{
		m_bodyDef.actor = GetOwner();
		m_physicsBody = std::make_unique<PhysicsBody>(GetOwner()->GetTransform(), m_size, m_bodyDef, Engine::Get().GetPhysics());
	}

	void Box2dPhysicsComponent::Update(float dt)
	{
		GetOwner()->SetPosition(GetPosition());
		GetOwner()->SetRotation(GetRotation() * RadToDeg);
	}

	void Box2dPhysicsComponent::ApplyForce(const Vector2& force)
	{
		m_physicsBody->ApplyForce(force);
	}

	void Box2dPhysicsComponent::SetVelocity(const Vector2& velocity)
	{
		m_physicsBody->SetVelocity(velocity);
	}

	Vector2 Box2dPhysicsComponent::GetVelocity()
	{
		return m_physicsBody->GetVelocity();
	}

	void Box2dPhysicsComponent::ApplyTorque(float torque)
	{
		m_physicsBody->ApplyTorque(torque);
	}

	void Box2dPhysicsComponent::SetAngularVelocity(float angularVelocity)
	{
		m_physicsBody->SetAngularVelocity(angularVelocity);
	}

	float Box2dPhysicsComponent::GetAngularVelocity() const
	{
		return m_physicsBody->GetAngularVelocity();
	}

	void Box2dPhysicsComponent::SetPosition(const Vector2& position)
	{
		m_physicsBody->SetPosition(position);
	}

	Vector2 Box2dPhysicsComponent::GetPosition() const
	{
		return m_physicsBody->GetPosition();
	}

	void Box2dPhysicsComponent::SetRotation(float rotation)
	{
		m_physicsBody->SetRotation(rotation);
	}

	float Box2dPhysicsComponent::GetRotation() const
	{
		return m_physicsBody->GetRotation();
	}

	void Box2dPhysicsComponent::Read(const json::value_t& value)
	{
		PhysicsComponent::Read(value);

		JSON_READ_NAME(value, "size", m_size);
		JSON_READ_NAME(value, "scale", m_scale);

		JSON_READ_NAME(value, "gravity_scale", m_bodyDef.gravityScale);
		JSON_READ_NAME(value, "linear_damping", m_bodyDef.linearDamping);
		JSON_READ_NAME(value, "angular_damping", m_bodyDef.angularDamping);
		JSON_READ_NAME(value, "constrain_angle", m_bodyDef.constrainAngle);
		JSON_READ_NAME(value, "is_dynamic", m_bodyDef.isDynamic);
		JSON_READ_NAME(value, "friction", m_bodyDef.friction);
		JSON_READ_NAME(value, "restitution", m_bodyDef.restitution);
		JSON_READ_NAME(value, "density", m_bodyDef.density);
		JSON_READ_NAME(value, "is_sensor", m_bodyDef.isSensor);

		std::string shapeName;
		JSON_READ_NAME(value, "shape", shapeName);

		if (!shapeName.empty())
		{
			if (EqualsIgnoreCase(shapeName, "box")) m_bodyDef.shape = PhysicsBody::Shape::Box;
			else if (EqualsIgnoreCase(shapeName, "capsule")) m_bodyDef.shape = PhysicsBody::Shape::Capsule;
			else if (EqualsIgnoreCase(shapeName, "circle")) m_bodyDef.shape = PhysicsBody::Shape::Circle;
		}
	}
}