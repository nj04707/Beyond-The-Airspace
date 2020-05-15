#pragma once

#include "Components.h"
#include "../Vector2D.h"
#include "../Game.h"

class HealthComponent : public Component
{
public:
    int health;

    HealthComponent()
    {
        health = 200;
    }

    void init() override
    {
        health = 200;
    }

    void update() override
    {
    }

    void take_damage(int damage)
    {
        health = health - damage;
    }
};