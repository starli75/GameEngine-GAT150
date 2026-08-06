#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "Font.h"
#include "Text.h"
#include "SpaceGame.h"


#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <map>
#include <memory>
#include <random>

using namespace nu; //lets you take off the nu::


class Object
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }
};

uint32_t seed = 1234;
uint32_t RNG()
{
    seed = (seed * 1103515245) + 12345;
    return seed;
}

//void dosomething(std::vector<Vector2>& v) { //Refer to the already made vector instead of making another copy
//    v[0].x = 40.0;
//}

int main()
{ 
    ////rand()
    //for (size_t i = 0; i < 10; i++) std::cout << RNG() << " ";
    //std::cout << std::endl;

    //seed = 1234;

    //for (size_t i = 0; i < 10; i++) std::cout << RNG() << " ";
    //std::cout << std::endl;


    //SeedRandom((unsigned int)time(NULL));
    //for (size_t i = 0; i < 10; i++) std::cout << rand() << " ";
    //std::cout << std::endl;


    ////<random>

    ////Makes the random seed
    //std::random_device randomDevice;
    //std::cout << randomDevice.min() << std::endl;
    //std::cout << randomDevice.max() << std::endl;
    //std::cout << randomDevice.entropy() << std::endl;

    ////Makes the actual random numbers
    //std::mt19937 generator(randomDevice());

    //std::uniform_int_distribution<> dist(0, 20);
    //for (size_t i = 0; i < 10; i++) std::cout << dist(generator) << " ";
    //std::cout << std::endl;

    //std::uniform_real_distribution<float> distReal(-10.0f, 20.0f);
    //for (size_t i = 0; i < 10; i++) std::cout << distReal(generator) << " ";
    //std::cout << std::endl;

    

    SetWorkingDirectory("Assets");


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
    //std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load(/*TODO: texture filename, get renderer from engine*/"Textures/PlayerShip.png", Engine::Get().GetRenderer());

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

        if (Engine::Get().GetInput().GetButtonDown(Input::MouseButton::Left)) {
            if (points.empty())
            {
                points.push_back(Engine::Get().GetInput().GetMousePosition());
            }
            else
            {
                Vector2 v = points.back() - Engine::Get().GetInput().GetMousePosition();

                if (v.Length() > 10.0f) {
                    points.push_back(Engine::Get().GetInput().GetMousePosition());
                }
            }
        }

        //Undo
        if (Engine::Get().GetInput().GetButtonPressed(Input::MouseButton::Right))
        {
            points.pop_back();
        }


        //RENDER
        Engine::Get().GetRenderer().SetColorFloat(0, 0, 0);
        Engine::Get().GetRenderer().Clear();

        // TODO:: get engine renderer.DrawTexture(...get() texture pointer..., 30, 30);
        Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("Textures/PlayerShip.png", Engine::Get().GetRenderer()), 30, 30, 45.0f);

        //Draw Line
        for (int i = 0; i < (int)points.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColorFloat(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

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


