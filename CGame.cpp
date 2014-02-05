#include "CGame.h"
#include "CDefine.h"
#include <iostream>
#include <sstream>
#include "CSurface.h"

/**
 * MapSystem by Malaxiz
 * https://github.com/Malaxiz/MapSystem
 *
 * This game uses maps to increase performance.
 *
 * Alot of this code I have learnt from www.sdltutorials.com and www.lazyfoo.net.
 *
 * TODO:
 * > Add entities, player and enemies (static entities(trees)?)
 * > Add physics.
 */


CGame::CGame() :
    Running(true),
    LastTime(SDL_GetTicks()), Timer(SDL_GetTicks()),
    Updates(0), Frames(0),
    Delta(0), NS(1000.0f/60.0f)
{
}

CGame::~CGame()
{
}

int CGame::OnExecute()
{
    if(OnInit() < 0)
        return -1;

    SDL_Event Event;

    std::cout << "Entering gameloop\n";

    while(Running)
    {
        while(SDL_PollEvent(&Event))
            OnEvent(&Event);

        float Now = SDL_GetTicks();
        Delta += (Now - LastTime) / NS;
        LastTime = Now;

        while(Delta >= 0)
        {
            OnLoop();
            Updates++;
            Delta--;
        }

        OnRender();

        Frames++;

        if(Timer - SDL_GetTicks() > 1000)
        {
            Timer += 1000;
            std::stringstream Title;
            Title << "MapSystem | " << Updates << " ups, " << Frames << " frames";
            SDL_WM_SetCaption(Title.str().c_str(), nullptr);
            Updates = 0;
            Frames = 0;
        }
    }

    std::cout << "Exiting gameloop\n";

    OnCleanup();

    return 0;
}

int CGame::OnInit()
{
    if((SDL_Init(SDL_INIT_EVERYTHING)) == -1)
    {
        std::cerr << "error: SDL_Init failed: " << SDL_GetError() << ".\n";
        return -1;
    }

    if((Surf_Display = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF)) == nullptr)
    {
        std::cerr << "error: SDL_SetVideoMode failed: " << SDL_GetError() << ".\n";
        OnCleanup();
        return -2;
    }

    if(ResourceManager.LoadSpriteSheets() == false)
    {
        OnCleanup();
        return -3;
    }

    Area = std::make_shared<CArea>(&ResourceManager);

    // Temp. For testing. Use level loading mechanic instead.
    if(Area->OnLoad("./maps/1.area") == false)
    {
        std::cerr << "error: " << "\"./maps/1.area\"" << " is not present.\n";
        OnCleanup();
        return -4;
    }

    // Temp. For testing. Use vel-based movement instead.
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_DELAY / 20);

    return 0;
}

void CGame::OnCleanup()
{
    SDL_Quit();
}

void CGame::OnLoop()
{
}

void CGame::OnRender()
{
    CSurface::RenderRect(0, 0, WIDTH, HEIGHT,
                         Surf_Display,
                         0, 0, 0);

    Area->OnRender(Surf_Display, Camera.GetX(), Camera.GetY());

    ResourceManager.GetSprite("Apple")->OnRender(100, 100, Surf_Display);
    ResourceManager.GetSprite("Helm")->OnRender(116, 100, Surf_Display);

    SDL_Flip(Surf_Display);
}

void CGame::OnEvent(SDL_Event* Event)
{
    switch(Event->type)
    {
    case SDL_KEYDOWN:
        switch(Event->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            Running = false;
            break;

        case SDLK_RIGHT: Camera.OnMove(5, 0); break;
        case SDLK_LEFT: Camera.OnMove(-5, 0); break;
        case SDLK_DOWN: Camera.OnMove(0, 5); break;
        case SDLK_UP: Camera.OnMove(0, -5); break;

            default:;
        }
        break;

    case SDL_QUIT:
        Running = false;
        break;

        default:;
    }
}
