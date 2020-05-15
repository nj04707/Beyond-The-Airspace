#pragma once

#include "Projectiles.h"

class Bullet : public Projectile
{
private:
public:
    void init(Manager *m, Vector2D pos, Vector2D vel, int range, int speed, std::string id);
};