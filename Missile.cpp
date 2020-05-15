#include "Missile.h"
#include "ECS\Components.h"

void Missile::init(Manager *m, Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
    auto &projectile(m->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 183, 500, .15);
    projectile.addComponent<SpriteComponent>("missile");
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("missile");
    projectile.addGroup(Game::groupMissiles);
    std::cout << "missile fired" << std::endl;
}
