#include "Collision.h"
#include "ECS\ColliderComponent.h"

bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB)
{
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y)
    {
        return true;
    }

    return false;
}

bool Collision::AABB2(const SDL_Rect &recA, const SDL_Rect &recB)
{
    if (
        (recA.x + recA.w - 30) >= recB.x &&
        (recB.x + recB.w - 30) >= recA.x &&
        (recA.y + recA.h - 165) >= recB.y &&
        (recB.y + recB.h - 125) >= recA.y)
    {
        return true;
    }

    return false;
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB)
{
    if (colA.tag == "player" && colB.tag == "enemy")
    {
        if (AABB2(colA.collider, colB.collider))
        {
            std::cout << colA.tag << " hit" << colB.tag << std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (AABB(colA.collider, colB.collider))
        {
            std::cout << colA.tag << " hit" << colB.tag << std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }
}