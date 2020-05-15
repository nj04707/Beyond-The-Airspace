#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:
    int animIndex = 0;
    std::map<const char *, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    SpriteComponent(std::string id)
    {
        setTex(id);
    }

    SpriteComponent(std::string id, bool isAnimated)
    {
        setTex(id);
        animated = true;

        Animation idle = Animation(0, 1, 100);
        Animation Up = Animation(4, 1, 50);
        Animation Down = Animation(3, 1, 50);
        Animation Explode = Animation(1, 4, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Up", Up);
        animations.emplace("Down", Down);
        animations.emplace("Explode", Explode);

        Play("Idle");
    }

    ~SpriteComponent()
    {
    }

    void setTex(std::string id)
    {

        texture = Game::assets->GetTexture(id);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() override
    {
        if (animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        srcRect.y = animIndex * transform->height;

        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override
    {

        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    void Play(const char *animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};
