#include "pch.h"
#include "Engine.h"
#include "SpaceGame/Player.h"
#include "SpaceGame/Enemy.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "SpriteGame/SpriteGame.h"
#include "SpaceGame/Bullet.h"
#include <memory>

using namespace nu; //lets you take off the nu::

int main()
{ 
    SetWorkingDirectory("Assets");

    //INITALIZATION
    Engine::Get().Initialize();
    Engine::Get().GetAudio().Initialize();

    //SpaceGame game;
    auto game = std::make_unique<SpriteGame>();
    game->Initialize();

    FMOD::System* audio;
    FMOD::System_Create(&audio);

    Engine::Get().GetAudio().PlaySound("AsteroidTitle");


    //Photoshop
    std::vector<Vector2> points;

    //MAIN LOOP;
    bool quit = false;
    while (!quit) {
        //UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            Engine::Get().GetAudio().Update();
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        
        //Engine::Get()
        Engine::Get().Update();


        float dt = Engine::Get().GetTime().GetDeltaTime();

        game->Update(dt);


        //RENDER
        Engine::Get().GetRenderer().SetColorFloat(0, 0, 0);
        Engine::Get().GetRenderer().Clear();

        //Draw text
       
        game->Draw(Engine::Get().GetRenderer());
        
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
    }
    game.reset();
    //SHUTDOWN
    Engine::Get().Shutdown();
    Engine::Get().GetAudio().Shutdown();

    return 0;
}


