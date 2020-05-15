#include "PowerUp.h"

int PowerUp::getAddition()
{
    return addition;
}

void PowerUp::init(Manager *m, std::string id)
{

    this->setXY();

    auto &p(m->addEntity());
    p.addComponent<TransformComponent>(this->xpos, this->ypos, 230, 230, .25);
    p.addComponent<SpriteComponent>(id);
    p.addComponent<ColliderComponent>("PowerUp");
    p.addGroup(Game::groupPowerUps);

    p.getComponent<TransformComponent>().velocity.x = -1;
}

void PowerUp::setXY()
{
    xpos = 1280;
    ypos = rand() % 500;
}