#pragma once

#include "Projectiles.h"

class Missile : public Projectile
{
private:
    int damage = 50;

public:
    void init(Manager *m, Vector2D pos, Vector2D vel, int range, int speed, std::string id); //initalize components
};