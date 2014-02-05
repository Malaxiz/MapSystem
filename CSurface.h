#ifndef CSURFACE_H
#define CSURFACE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class CSprite;

namespace CSurface
{
    void RenderRect(int x, int y, int w, int h, SDL_Surface* Surf_Destination, int r, int g, int b);

    // Image functions
    SDL_Surface* LoadSurface(std::string Path);
    void ApplySprite(int x, int y, CSprite* Sprite, SDL_Surface* Surf_Destination);

    // Misc functions
    bool Collision(int x, int y, int w, int h, int x2, int y2, int w2, int h2);
};

#endif // CSURFACE_H
