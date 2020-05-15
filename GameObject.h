#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"
#include "ECS\Components.h"

class GameObject
{
private:
public:
    virtual void init(); //initlaize the specific component
};