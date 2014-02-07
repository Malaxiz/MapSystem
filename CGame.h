#ifndef CGAME_H
#define CGAME_H

#include <SDL.h>
#include <memory>
#include <string>
#include "CResourceManager.h"
#include "CArea.h"
#include "CCamera.h"

class CGame
{
public:
    std::string GameVersion;

    CGame();
    virtual ~CGame();

    int OnExecute();

private:
    int OnInit();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();

    bool Running;
    SDL_Surface* Surf_Display;

    CResourceManager ResourceManager;
    std::shared_ptr<CArea> Area;
    CCamera Camera;

    int LastTime;
    int Timer;
    int Updates;
    int Frames;
    float Delta;
    float NS;

};

#endif // CGAME_H
