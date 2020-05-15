#pragma once

#include "GameObject.h"

class PowerUp : public GameObject
{

private:
    int addition;
    int xpos;
    int ypos;

public:
    int getAddition();      //increase health

    void init(Manager *m, std::string id);      //initialze components

    void setXY();           //set the coordinates of powerup on screen
};