#pragma once
#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc
{
    float speed;
    int health;

};

class Player : public nu::Actor
{
public:
    static Player& Get() { static Player player; return player; }

    Player() = default;
    Player(const PlayerDesc& playerDesc) :
        Actor{ playerDesc },
        m_health{ playerDesc.health },
        m_speed{ playerDesc.speed }
    {}

    void Update(float dt) override;  

    void OnCollision(Actor* other);

    virtual void Read(const nu::json::value_t& value) override;

    int GetHealth() { return m_health; } //read access violation here; says "this was nullptr"

    float GetSpeed() const { return m_speed; }


private:
    int m_ammo = 0;
    float m_speed = 2000.0f;
    int m_health = 1;


    bool laserOn = false;
};