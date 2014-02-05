#include "CSurface.h"
#include "CSprite.h"

void CSurface::RenderRect(int x, int y, int w, int h,
                     SDL_Surface* Surf_Destination,
                     int r, int g, int b)
{
    SDL_Rect Rect = SDL_Rect{(Sint16)x, (Sint16)y, (Uint16)w, (Uint16)h};

    SDL_FillRect(Surf_Destination,
                 &Rect,
                 SDL_MapRGB(Surf_Destination->format, r, g, b));
}

SDL_Surface* CSurface::LoadSurface(std::string Path)
{
    SDL_Surface* LoadedSurface = nullptr;
    SDL_Surface* OptimizedSurface = nullptr;

    LoadedSurface = IMG_Load(Path.c_str());

    if(LoadedSurface != nullptr)
    {
        OptimizedSurface = SDL_DisplayFormatAlpha(LoadedSurface);

        SDL_FreeSurface(LoadedSurface);
    }

    return OptimizedSurface;
}

void CSurface::ApplySprite(int x, int y, CSprite* Sprite, SDL_Surface* Surf_Destination)
{
    SDL_Rect Rect;

    Rect.x = x;
    Rect.y = y;

    SDL_BlitSurface(Sprite->GetSurface(), &Sprite->Offset, Surf_Destination, &Rect);
}

bool CSurface::Collision(int x, int y, int w, int h, int x2, int y2, int w2, int h2)
{
//    x += 16;
//    y += 16;

    // Left is larger Right2
    if(x > x2 + w2)
        return false;
    // Right is less than Left2
    if(x + w < x2)
        return false;
    // Top is larger than Bottom2
    if(y > y2 + h2)
        return false;
    // Bottom is less than Top2
    if(y + h < y2)
        return false;

    // Collision
    return true;
}
