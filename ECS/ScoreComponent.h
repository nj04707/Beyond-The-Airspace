#pragma once

#include "Components.h"
#include "../Vector2D.h"
#include "../Game.h"

class ScoreComponent : public Component
{

private:
    int score;

public:
    ScoreComponent()
    {
        score = 0;
    }

    int getScore()
    {
        return score;
    }

    void addScore(int value)
    {
        score += value;
    }

    void init() override
    {
        score = 0;
    }
};