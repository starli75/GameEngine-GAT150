#include "pch.h"

#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "Model.h"
#include "Bullet.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "ParticleSystem.h"

void Player::Update(float dt)
{

    //Movement
    float thrust = 0.0f;


    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        
        thrust = m_speed;
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;



    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1,0 }; 
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad)* thrust;
    SetVelocity(velocity * dt);

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
            BulletDesc bulletDesc;
            bulletDesc.lifespan = 1.0f;
            bulletDesc.name = "Bullet";
            bulletDesc.tag = "PlayerBullet";
            bulletDesc.texture = nu::Resources().Get<nu::Texture>("Textures/PlayerProjectile.png", nu::Engine::Get().GetRenderer());
            bulletDesc.transform = m_transform;
            bulletDesc.transform.scale = 2.0f;
            bulletDesc.speed = 2000.0f;

            m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));
        }
        break;
    case false:
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
        {
            BulletDesc bulletDesc;
            bulletDesc.lifespan = 1.0f;
            bulletDesc.name = "Bullet";
            bulletDesc.tag = "PlayerBullet";
            bulletDesc.texture = nu::Resources().Get<nu::Texture>("Textures/PlayerProjectile.png", nu::Engine::Get().GetRenderer());
            bulletDesc.transform = m_transform;
            bulletDesc.transform.scale = 2.0f;
            bulletDesc.speed = 2000.0f;

            m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));
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
        if (other->GetName() == "Enemy")
        {
            m_health -= 25;

           /* if (m_health == 0)
            {*/
                SetDestroyed();
                ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
           /* }*/
        }
    }

