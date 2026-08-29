#include "pch.h"

#include "Player.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include "Renderer/Model.h"
#include "Bullet.h"
#include "SpaceGame.h"
#include "Renderer/ParticleSystem.h"
#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Player);

void Player::Update(float dt)
{
    //Movement
    float thrust = 0.0f;


    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        
        thrust = m_speed;
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;



    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -40.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +40.0f;

    auto physicsComponent = GetComponent<nu::PhysicsComponent>();
    if (physicsComponent)
    {
        nu::Vector2 forward{ 1,0 }; 
        nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::DegToRad)* thrust;

        physicsComponent->ApplyForce(force);
        physicsComponent->ApplyTorque(rotate);

        nu::Vector2 position = physicsComponent->GetPosition();

        position.x = nu::Wrap(0.0f, 1920.0f, position.x);
        position.y = nu::Wrap(0.0f, 1024.0f, position.y);
        physicsComponent->SetPosition(position);
    }

    SetRotation(m_transform.rotation + rotate * dt);

    //SetVelocity(velocity * dt);

    //Fire
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_L))
    {
        laserOn = true;
    }
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_K))
    {
        laserOn = false;
    }
    switch (laserOn) {
    case true:
        if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
        {
            auto bullet = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
            bullet->SetTransform(m_transform);
            bullet->SetScale(2.0f);
            bullet->SetTag("PlayerBullet");

            m_scene->AddActor(std::move(bullet));
            /*BulletDesc bulletDesc;
            bulletDesc.lifespan = 1.0f;
            bulletDesc.name = "Bullet";
            bulletDesc.tag = "PlayerBullet";
            bulletDesc.texture = nu::Resources().Get<nu::Texture>("Textures/PlayerProjectile.png", nu::Engine::Get().GetRenderer());
            bulletDesc.transform = m_transform;
            bulletDesc.transform.scale = 2.0f;
            bulletDesc.speed = 2000.0f;

            m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));*/
        }
        break;
    case false:
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
        {
            auto bullet = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
            bullet->SetTransform(m_transform);
            bullet->SetScale(2.0f);
            bullet->SetTag("PlayerBullet");

            m_scene->AddActor(std::move(bullet));

            /*BulletDesc bulletDesc;
            bulletDesc.lifespan = 1.0f;
            bulletDesc.name = "Bullet";
            bulletDesc.tag = "PlayerBullet";
            bulletDesc.texture = nu::Resources().Get<nu::Texture>("Textures/PlayerProjectile.png", nu::Engine::Get().GetRenderer());
            bulletDesc.transform = m_transform;
            bulletDesc.transform.scale = 2.0f;
            bulletDesc.speed = 2000.0f;

            m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));*/
        }
        break;
    }

    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_X)) 
    {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }
    else
    {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }

    Actor::Update(dt);

}
    void Player::OnCollision(Actor* other)
    {
        return; //NO DEATH OR HEALTH
        if (other->GetName() == "EnemyPrototype")
        {
            m_health -= 25;
            other->SetDestroyed();

           if (m_health <= 0)
            {
                SetDestroyed();
                ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
           }
        }
    }

    void Player::Read(const nu::json::value_t& value)
    {
        Actor::Read(value);
        JSON_READ_NAME(value, "health", m_health);
        JSON_READ_NAME(value, "speed", m_speed);
    }

