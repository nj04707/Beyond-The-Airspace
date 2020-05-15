#pragma once

#include "GameObject.h"

class ScoreUp : public GameObject
{

private:
    int addition;
    int xpos;
    int ypos;

public:
    int getAddition();              //increase plane health

    void init(Manager *m, std::string id);  //initialze components

    void setXY();                   //update the location of power ups on screen
};