#include "Game.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Collision.h"
#include "ECS/ECS.cpp"
#include "Definitions.h"
#include "AssetManager.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "PowerUp.h"
#include "ScoreUp.h"
#include "screenDisplay.h"
#include "mainmenu.h"
#include "Missile.h"

SDL_Event Game::event;
SDL_Renderer *Game::renderer = nullptr;

bool game_flag = false;
std::vector<ColliderComponent *> Game::colliders;

std::string str, str1;

SDL_Color black = {40, 50, 255, 255};

auto &enemy(manager.addEntity());
auto &label(manager.addEntity());
Uint32 last_enemy_arrive = 0;
Enemy e;

Bullet bullet;
Uint32 last_bullet_fired = 0;

Missile missile;
Uint32 last_missile_fired = 0;

Uint32 last_explosion_appear = 0;

PowerUp power;
Uint32 last_power_arrive = 0;

ScoreUp score;
Uint32 last_score_arrive = 0;

Uint32 delay = 0;
Explosion explosion;

screenDisplay levelComplete;

screenDisplay gameOver;

screenDisplay gamePaused;

AssetManager *Game::assets = new AssetManager(&manager);
Game::Game()
{
}

bool Game::getGameState()
{
    return gam_over;
}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{

    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window)
        {
            std::cout << "Windows created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Created" << std::endl;
        }

        if (TTF_Init() == -1)
        {
            std::cout << "Error : SDL_TTF" << std::endl;
        }

        isRunning = true;

        assets->AddTexture("player", "assets/player_plane.png");
        assets->AddTexture("bullet", "assets/Bullet_3.png");
        assets->AddTexture("enemy", "assets/enemy_plane.png");
        assets->AddTexture("score", "assets/sp.png");
        assets->AddTexture("power", "assets/ps.png");
        assets->AddTexture("explosion", "assets/explosion.png");
        assets->AddTexture("missile", "assets/Bomb_2.png");

        assets->AddFont("arial", "assets/arial.ttf", 16);

        // explosion.animated = true;
        // explosion.nframes = 2;
        // explosion.speed = 100;

        levelComplete.Load("assets/levelComplete.jpg");
        levelComplete.setDimension(0, 0, 608, 342, 0, 0, 1280, 720);

        gamePaused.Load("assets/paused.png");
        gamePaused.setDimension(0, 0, 1600, 1600, 420, 100, 400, 360);

        gameOver.Load("assets/gameOver.jpg");
        gameOver.setDimension(0, 0, 852, 480, 0, 0, 1280, 720);

        bg.Load();
        //bg.Draw();

        player.addComponent<TransformComponent>(0.0f, 0.0f, 250, 250, 1);
        player.addComponent<SpriteComponent>("player", true);
        player.addComponent<KeyboardController>();
        player.addComponent<ColliderComponent>("player");
        player.addComponent<HealthComponent>();
        player.addComponent<ScoreComponent>();
        player.addGroup(groupPlayers);

        str = std::to_string((player.getComponent<HealthComponent>().health));
        str1 = std::to_string(player.getComponent<ScoreComponent>().getScore());

        label.addComponent<UILabel>(10, 10, "Health : " + str, "arial", black);
        player.addComponent<UILabel>(200, 10, "Score " + player.getComponent<ScoreComponent>().getScore(), "arial", black);

        player.getComponent<TransformComponent>().position.x += 1;
    }
    else
    {
        isRunning = false;
    }
}

auto &players(manager.getGroup(Game::groupPlayers));
auto &enemies(manager.getGroup(Game::groupEnemies));
auto &bullets(manager.getGroup(Game::groupBullets));
auto &powerups(manager.getGroup(Game::groupPowerUps));
auto &scoreups(manager.getGroup(Game::groupScoreUps));
auto &explosions(manager.getGroup(Game::groupExplosions));
auto &missiles(manager.getGroup(Game::groupMissiles));

void Game::update()
{
    //label.destroy();
    if (!gam_over)
    {
        str = std::to_string((player.getComponent<HealthComponent>().health));
        str1 = std::to_string(player.getComponent<ScoreComponent>().getScore());

        //std::cout << "Health: " << str << std::endl
        //<< "Score: " << str1 << std::endl;

        label.getComponent<UILabel>().SetLabelText("Health : " + str, "arial");
        player.getComponent<UILabel>().SetLabelText("Score " + str1, "arial");
        label.getComponent<UILabel>().draw();
        player.getComponent<UILabel>().draw();
        // label.getComponent<UILabel>().draw();
    }

    manager.refresh();
    manager.update();
    bg.update();

    //player restrict
    if ((player.getComponent<TransformComponent>().position.x) < 0)
    {
        player.getComponent<TransformComponent>().position.x = 0;
    }
    if ((player.getComponent<TransformComponent>().position.x) > 1280)
    {
        player.getComponent<TransformComponent>().position.x = 1180;
    }
    if ((player.getComponent<TransformComponent>().position.y) < 0)
    {
        player.getComponent<TransformComponent>().position.y = 0;
    }
    if ((player.getComponent<TransformComponent>().position.y) > 720)
    {
        player.getComponent<TransformComponent>().position.y = 720;
    }

    if ((time.get_Time() - last_missile_fired) > 6000)
    {
        last_missile_fired = time.get_Time();
        for (auto en : enemies)
        {

            missile.init(&manager, Vector2D((float)en->getComponent<TransformComponent>().position.x - 100, (float)en->getComponent<TransformComponent>().position.y + 110), Vector2D(-2, 0), 300, 1, "missile");
        }
    }

    if ((time.get_Time() - last_power_arrive) > 31000)
    {
        last_power_arrive = time.get_Time();
        power.init(&manager, "power");
    }

    if ((time.get_Time() - last_score_arrive) > 5000)
    {
        last_score_arrive = time.get_Time();
        score.init(&manager, "score");
    }

    if ((time.get_Time() - last_enemy_arrive) > 3000)
    {
        last_enemy_arrive = time.get_Time();
        e.init(&manager, "enemy");
    }

    if ((time.get_Time() - (this->level_start + pause_time) > 90000))
    {
        std::cout << "Level Pass" << std::endl;

        lev_com = true;
        //Game::isRunning = false;
    }

    if ((time.get_Time() - last_explosion_appear) > 500)
    {
        last_explosion_appear = time.get_Time();
        for (auto e : explosions)
        {
            e->destroy();
        }
    }
    //for (auto cc : colliders)
    //{
    // Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
    //}

    //std::cout << enemies.size() << std::endl;

    for (auto en : enemies)
    {
        if (en->getComponent<TransformComponent>().position.x < -200)
        {
            en->destroy();
        }
    }

    for (auto mis : missiles)
    {
        for (auto b : bullets)
        {
            if (Collision::AABB(b->getComponent<ColliderComponent>().collider, mis->getComponent<ColliderComponent>().collider))
            {
                b->destroy();
                mis->destroy();
            }
        }
    }

    for (auto mis : missiles)
    {
        for (auto p : players)
        {
            if (Collision::AABB(p->getComponent<ColliderComponent>().collider, mis->getComponent<ColliderComponent>().collider))
            {
                mis->destroy();
                p->getComponent<HealthComponent>().health -= 50;
                if (p->getComponent<HealthComponent>().health <= 0)
                {

                    this->update();
                    this->render();

                    p->destroy();
                    gam_over = true;
                }
            }
        }
    }

    for (auto mis : missiles)
    {
        if (mis->getComponent<TransformComponent>().position.x < -200)
        {
            mis->destroy();
        }
    }
    for (auto b : bullets)
    {
        for (auto en : enemies)
        {
            if (Collision::AABB(b->getComponent<ColliderComponent>().collider, en->getComponent<ColliderComponent>().collider))
            {
                en->getComponent<HealthComponent>().take_damage(50);
                std::cout << "Bullet hit enemy" << std::endl;
                b->destroy();

                if (en->getComponent<HealthComponent>().health <= 0)
                {
                    player.getComponent<ScoreComponent>().addScore(100);

                    explosion.init(en->getComponent<TransformComponent>().position.x, en->getComponent<TransformComponent>().position.y, &manager, "explosion");
                    last_explosion_appear = time.get_Time();
                    en->destroy();
                }
            }
        }
    }

    for (auto p : players)
    {
        for (auto en : enemies)
        {
            if (Collision::AABB(p->getComponent<ColliderComponent>(), en->getComponent<ColliderComponent>()))
            {
                /****************Just to test******************/
                p->getComponent<HealthComponent>().take_damage(100);
                // p->getComponent<HealthComponent>().take_damage(0);
                std::cout << "Player hit enemy" << std::endl;
                explosion.init(en->getComponent<TransformComponent>().position.x, en->getComponent<TransformComponent>().position.y, &manager, "explosion");
                last_explosion_appear = time.get_Time();
                en->destroy();

                if (p->getComponent<HealthComponent>().health <= 0)
                {

                    this->update();
                    this->render();

                    p->destroy();
                    gam_over = true;
                }
            }
        }
    }

    for (auto p : players)
    {
        for (auto pow : powerups)
        {
            if (Collision::AABB(p->getComponent<ColliderComponent>().collider, pow->getComponent<ColliderComponent>().collider))
            {
                p->getComponent<HealthComponent>().health += 100;

                pow->destroy();
            }
        }
    }

    for (auto p : players)
    {
        for (auto sco : scoreups)
        {
            if (Collision::AABB(p->getComponent<ColliderComponent>().collider, sco->getComponent<ColliderComponent>().collider))
            {
                p->getComponent<ScoreComponent>().addScore(50);

                sco->destroy();
            }
        }
    }
    // auto &label(manager.addEntity());
    // str = std::to_string(player.getComponent<HealthComponent>().health);
    // str1 = std::to_string(player.getComponent<ScoreComponent>().getScore());
    // //label.getComponent<UILabel>().setAgain(10, 10, "Health : " + str, "arial", black);
    // //player.getComponent<UILabel>().setAgain(200, 10, "Score :" + str1, "arial", black);
    // label.addComponent<UILabel>(10, 10, "Health : " + str, "arial", black);
    // player.addComponent<UILabel>(200, 10, "Score " + player.getComponent<ScoreComponent>().getScore(), "arial", black);
    // std::cout << "Health : " << player.getComponent<HealthComponent>().health << std::endl;
    // std::cout << "Score : " << player.getComponent<ScoreComponent>().getScore() << std::endl;
}

void Game::render()
{
    SDL_RenderClear(renderer);

    bg.Draw();

    for (auto &p : players)
    {
        p->draw();
    }
    for (auto &e : enemies)
    {
        e->draw();
    }

    for (auto &b : bullets)
    {
        b->draw();
    }

    for (auto &mis : missiles)
    {
        mis->draw();
    }

    for (auto &pow : powerups)
    {
        pow->draw();
    }
    for (auto &sco : scoreups)
    {
        sco->draw();
    }
    for (auto &explo : explosions)
    {
        explo->draw();
    }

    label.draw();

    if (lev_com)
    {
        levelComplete.Draw();
    }
    else if (gam_over)
    {
        gameOver.Draw();
    }

    if (gam_paused && gam_over == false)
    {
        gamePaused.Draw();
        std::cout << gam_paused << std::endl
                  << gam_over << std::endl;
    }

    label.draw();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

void Game::handleEvents()
{

    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }

    if (Game::event.type == SDL_KEYDOWN)
    {
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_SPACE:
            //assets->CreateProjectile(Vector2D(player.getComponent<TransformComponent>().position.x + 235, player.getComponent<TransformComponent>().position.y + 110), Vector2D(2, 0), 300, 1, "bullet");
            if ((time.get_Time() - last_bullet_fired) > 500)
            {
                last_bullet_fired = time.get_Time();
                bullet.init(&manager, Vector2D(player.getComponent<TransformComponent>().position.x + 235, player.getComponent<TransformComponent>().position.y + 110), Vector2D(2, 0), 300, 1, "bullet");
            }
            break;
        case SDLK_p:
            // gam_over = false;
            lev_com = false;
            gam_paused = !gam_paused;
            if (gam_paused)
            {
                this->pause_start_time = time.get_Time();
            }
            if (!gam_paused)
            {
                this->pause_time += time.get_Time() - this->pause_start_time;
            }

            break;
        // case SDLK_k:
        //     gam_paused=true;
        //     break;
        default:
            break;
        }
    }
}
