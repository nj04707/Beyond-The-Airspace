#include "Bullet.h"
#include "ECS\Components.h"

void Bullet::init(Manager *m, Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{

    auto &projectile(m->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 42, 190, 0.15);
    projectile.addComponent<SpriteComponent>(id);
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    projectile.addComponent<ColliderComponent>("Bullet");
    projectile.addGroup(Game::groupBullets);
}
