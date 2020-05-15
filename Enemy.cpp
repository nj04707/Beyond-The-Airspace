#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::init(Manager *m, std::string id)
{
    this->setXY();

    auto &e(m->addEntity());
    e.addComponent<TransformComponent>(this->xpos, this->ypos, 200, 252, 1);
    e.addComponent<SpriteComponent>("enemy");
    e.addComponent<ColliderComponent>("enemy");
    e.addComponent<HealthComponent>();
    e.addGroup(Game::groupEnemies);

    e.getComponent<TransformComponent>().velocity.x = -1;
}

void Enemy::setXY()
{

    xpos = 1280;
    ypos = rand() % 500;
}

void Enemy::take_damage(int damage)
{
    this->health = this->health - damage;
}

int Enemy::get_health()
{
    return health;
}