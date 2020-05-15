#include "ScoreUp.h"

int ScoreUp::getAddition()
{
    return addition;
}

void ScoreUp::init(Manager *m, std::string id)
{

    this->setXY();

    auto &s(m->addEntity());
    s.addComponent<TransformComponent>(this->xpos, this->ypos, 230, 230, .25);
    s.addComponent<SpriteComponent>(id);
    s.addComponent<ColliderComponent>("ScoreUp");
    s.addGroup(Game::groupScoreUps);

    s.getComponent<TransformComponent>().velocity.x = -1;
}

void ScoreUp::setXY()
{
    xpos = 1280;
    ypos = rand() % 500;
}