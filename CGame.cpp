#include "CGame.h"
#include <SDL_ttf.h>
#include <sstream>
#include <iostream>
#include "CDefine.h"
#include "CSurface.h"

#include "CAnimation.h"

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
    GameVersion("MapSystem v.1.1"),
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

    std::stringstream FpsDebug;

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
            FpsDebug.str("");
            FpsDebug << "Ups: " << Updates << ", Fps: " << Frames;

            Timer += 1000;
            Updates = 0;
            Frames = 0;
        }

        // Text buffer call
        ResourceManager.CreateTextBuffer(4, 32, FpsDebug.str().c_str(), Surf_Display,
                                 ResourceManager.FontMap["TestFont"], {0xFF, 0xFF, 0xFF});
    }

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

    if(TTF_Init() == -1)
    {
        std::cerr << "error: TTF_Init failed: " << SDL_GetError() << ".\n";
    }

    if((Surf_Display = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF)) == nullptr)
    {
        std::cerr << "error: SDL_SetVideoMode failed: " << SDL_GetError() << ".\n";
        OnCleanup();
        return -2;
    }

    SDL_WM_SetCaption("MapSystem by Malaxiz", nullptr);

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

    TTF_Quit();
}

void CGame::OnLoop()
{
    // Just a test
//    void test(int i, std::initializer_list<SDL_Rect> Offsets);
//
//    test(1, {
//            {0, 0, 16, 16},
//            {16, 16, 16, 16},
//            {24, 24, 16, 16},
//            {32, 32, 16, 16}
//         });
}

void CGame::OnRender()
{
    CSurface::RenderRect(0, 0, WIDTH, HEIGHT,
                         Surf_Display,
                         0, 0, 0);

    Area->OnRender(Surf_Display, Camera.GetX(), Camera.GetY());

    // Puts together a text that displays the camera's coordinates
    std::stringstream Text;
    Text << "CameraX: " << Camera.GetX() << ", CameraY: " << Camera.GetY();
    // Text buffer call
    ResourceManager.CreateTextBuffer(4, 16, Text.str().c_str(), Surf_Display,
                         ResourceManager.FontMap["TestFont"], {0xFF,0xFF,0xFF});

    // Renders the version name to the text buffer
    int vWidth, vHeight;
    TTF_SizeText(ResourceManager.FontMap["TestFont"], GameVersion.c_str(), &vWidth, &vHeight);
    // Text buffer call
    ResourceManager.CreateTextBuffer(WIDTH - vWidth - 4, 0, GameVersion.c_str(), Surf_Display,
                                     ResourceManager.FontMap["TestFont"], {0xFF,0xFF,0xFF});

    // Temp
    ResourceManager.GetSprite("ItemSprite", "Apple")->OnRender(120, 100, Surf_Display);
    ResourceManager.GetSprite("ItemSprite", "Helm")->OnRender(480, 100, Surf_Display);

    ResourceManager.AnimationMap["TestAnimation"]["Wheat"]->OnRender(150, 150, Surf_Display);
    ResourceManager.AnimationMap["TestAnimation"]["Wool"]->OnRender(150, 200, Surf_Display);
    ResourceManager.AnimationMap["TestAnimation"]["All"]->OnRender(150, 250, Surf_Display);

    ResourceManager.RenderTextBuffers();

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
