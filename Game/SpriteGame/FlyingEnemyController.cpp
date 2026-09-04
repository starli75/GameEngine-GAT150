#include "FlyingEnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Damager.h"


FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void FlyingEnemyController::Update(float dt)
{
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();

	auto player = m_scene->GetActorByName("PlayerPrototype");
	switch (m_state)
	{
	case CharacterBase::State::Move:
		if (player)
		{
			nu::Vector2 position = GetTransform().position;
			nu::Vector2 playerPosition = player->GetTransform().position;
			nu::Vector2 direction = playerPosition - position;

			m_rendererComponent->SetFlipH(direction.x < 0.0f);

			if (direction.Length() < 100.0f)
			{
				m_state = State::Attack;
				m_rendererComponent->Play("Attack");

				auto damager = nu::Factory::Instance().Create<Damager>("DamagerPrototype");
				damager->SetPosition(GetTransform().position);
				damager->SetScale(2.0f);
				damager->SetTag("EnemyDamager");
				m_scene->AddActor(std::move(damager));
			}

			m_physicsComponent->ApplyForce(direction.Normalized() * 500.0f);
		}
		break;
	case CharacterBase::State::Attack:
	case CharacterBase::State::Hit:
		if (m_rendererComponent->IsAnimationDone())
		{
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
		break;
	case CharacterBase::State::Death:
		break;
	default:
		break;
	}


	CharacterBase::Update(dt);
}

void FlyingEnemyController::OnCollision(nu::Actor* other)
{
	if (nu::EqualsIgnoreCase(other->GetTag(), "PlayerDamager"))
	{
		//hit player
		m_state = State::Hit;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) m_health -= damager->GetDamage();
		if (m_health <= 0)
		{
			SetDestroyed();
		}
		//SetDestroyed();

		//remove damager
		other->SetDestroyed();
	}
}

void FlyingEnemyController::Read(const nu::json::value_t& value)
{
	CharacterBase::Read(value);
}


