#ifndef CSPRITE_H
#define CSPRITE_H

#include <SDL.h>
#include <memory>
#include "CSpriteSheet.h"

class CSprite
{
public:
    CSprite(int x, int y, int w, int h, std::shared_ptr<CSpriteSheet> SpriteSheet);
    ~CSprite();

    void OnRender(int x, int y, SDL_Surface* Surf_Destination);
    SDL_Surface* GetSurface();

    SDL_Rect Offset;
    std::shared_ptr<CSpriteSheet> SpriteSheet;
};

#endif // CSPRITE_H
