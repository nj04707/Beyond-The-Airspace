#include "Explosion.h"

Explosion::Explosion()
{
}

void Explosion::init(float xpos, float ypos, Manager *m, std::string id)
{

    auto &e(m->addEntity());
    e.addComponent<TransformComponent>(xpos, ypos, 258, 258, 1);
    e.addComponent<SpriteComponent>("explosion");
    e.addComponent<ColliderComponent>("explosion");
    e.addGroup(Game::groupExplosions);

    std::cout << "initiated" << std::endl;

    //e.getComponent<TransformComponent>().velocity.x = -1;
}