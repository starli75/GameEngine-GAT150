#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "Font.h"
#include "Text.h"
#include "SpaceGame.h"
#include "Bullet.h"


#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <map>
#include <memory>
#include <random>
#include <fstream>

using namespace nu; //lets you take off the nu::

int main()
{ 
    SetWorkingDirectory("Assets");
    //Factory::Instance().Register<Object>("Object");
   /* Factory::Instance().Register<Actor>("Actor");
    Factory::Instance().Register<Player>("Player");
    Factory::Instance().Register<Enemy>("Enemy");
    Factory::Instance().Register<Bullet>("Bullet");*/
    /*
    auto actor = Factory::Instance().Create<Actor>("Actor");
    auto object = Factory::Instance().Create("Object");

    std::cout << actor->IsActive() << std::endl;
    std::cout << object->IsActive() << std::endl;

    auto player = Factory::Instance().Create<Player>("Player");

    json::document_t document;
    if (json::Load("data/scene.json", document))
    {
        player->Read(document);
        std::cout << player->GetName() << std::endl;
        std::cout << player->GetTag() << std::endl;

        std::cout << player->GetTransform().rotation << std::endl;
        std::cout << player->GetSpeed() << std::endl;
    }


    return 0;*/


    
    // load the json data from a file
    //std::string buffer;
    //if (ReadTextFile("data/data.json", buffer))
    //{
    //    // show the contents of the json file (debug)
    //    std::cout << buffer << std::endl;

    //    // create json document from the json file contents
    //    rapidjson::Document document;
    //    if (json::Load("data/data.json", document))
    //    {
    //        // read/show the data from the json file
    //        std::string name;
    //        int age;
    //        float speed;
    //        bool isAwake;
    //        Vector2 position;
    //        Vector3 color;

    //        // read the json data
    //        JSON_READ(document, name);
    //        JSON_READ(document, age);
    //        JSON_READ(document, speed);
    //        JSON_READ(document, isAwake);
    //        JSON_READ(document, position);
    //        JSON_READ(document, color);

    //        // show the data
    //        std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    //        std::cout << position.x << " " << position.y << std::endl;
    //        std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
    //    }
    //}

    //return 0;
    

    

    //INITALIZATION
    Engine::Get().Initialize();
    Engine::Get().GetAudio().Initialize();

    SpaceGame game;
    game.Initialize();

    FMOD::System* audio;
    FMOD::System_Create(&audio);

    Engine::Get().GetAudio().PlaySound("AsteroidTitle");


    //Photoshop
    std::vector<Vector2> points;

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("Textures/PlayerShip.png", Engine::Get().GetRenderer());

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

        game.Update(dt);


        //RENDER
        Engine::Get().GetRenderer().SetColorFloat(0, 0, 0);
        Engine::Get().GetRenderer().Clear();

        // TODO:: get engine renderer.DrawTexture(...get() texture pointer..., 30, 30);
        Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("Textures/PlayerShip.png", Engine::Get().GetRenderer()), 30, 30, 45.0f);

        //Draw text
       
        game.Draw(Engine::Get().GetRenderer());
        
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
    }
    //SHUTDOWN
    Engine::Get().Shutdown();
    Engine::Get().GetAudio().Shutdown();

    return 0;
}


