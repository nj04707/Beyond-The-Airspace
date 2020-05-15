#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
private:
    int damage = 50;

public:
    virtual void init(Manager *m, Vector2D pos, Vector2D vel, int range, int speed, std::string id) = 0;

    virtual int getDamage(); //returns the damage value of the bullet when it strikes the plane
};