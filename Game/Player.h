#pragma once
#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc
{
    float speed;

};

class Player : public nu::Actor
{
public:
    static Player& Get() { static Player player; return player; }

    Player() = default;
    Player(const PlayerDesc& playerDesc) :
        Actor{ playerDesc },
        m_speed{ playerDesc.speed }
    {}

    void Update(float dt) override;  

    void OnCollision(Actor* other);

    int GetHealth() const { return m_health; }

private:
    int m_ammo = 0;
    float m_speed = 2000.0f;
    int m_health = 200;


    bool laserOn = false;
};