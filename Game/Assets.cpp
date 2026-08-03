#include "Assets.h"

using namespace nu;

namespace assets
{
    Mesh playerMesh{ 
        {
            Vector2{2, 0}, 
            Vector2{-2, 2}, 
            Vector2{-1,0}, 
            Vector2{2,0}, 
            Vector2{-2,-2}, 
            Vector2{-1,0}
        }, 
        Color{0.0f, 0.0f, 100.0f} 
    };
    Mesh meshFlame{ 
        {
            Vector2{-2,0}, 
            Vector2{-3,1}, 
            Vector2{-5,0}, 
            Vector2{-3,-1}, 
            Vector2{-2,0}
        }, 
        Color{255.0f, 165.0f, 0.0f} 
    };

    Model playerModel{ std::vector<Mesh> {playerMesh, meshFlame} };

    Mesh enemyMesh{ 
        {
            Vector2{2, 0}, 
            Vector2{-2, 2}, 
            Vector2{-1,0}, 
            Vector2{2,0}, 
            Vector2{-2,-2}, 
            Vector2{-1,0}
        }, 
        Color{255.0f, 0.0f, 0.0f} 
    };
    Model enemyModel{ std::vector<Mesh> {enemyMesh} };

    Mesh bulletMesh{
  {
    Vector2{ -1, -1 },
    Vector2{ 1, 0 },
    Vector2{ -1, 1 },
    Vector2{ -1, -1 },
  },
  Color{ 1.0f, 0.0f, 0.0f }
    };
    Model bulletModel{ std::vector<Mesh> {bulletMesh} };

    Mesh healthMesh{
        {
        Vector2{0, 2},
        Vector2{0, -2},
        Vector2{0,0},
        Vector2{-2,0},
        Vector2{2, 0},
        },
        Color{0.0f, 1.0f, 0.0f}

    };
    Model healthModel{ std::vector<Mesh> {healthMesh} };



}