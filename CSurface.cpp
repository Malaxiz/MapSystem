#include "CSurface.h"
#include "CSprite.h"
#include <iostream>

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

void CSurface::ApplySurface(int x, int y, SDL_Surface* Surf_Source, SDL_Surface* Surf_Destination)
{
    SDL_Rect Rect;

    Rect.x = x;
    Rect.y = y;

    SDL_BlitSurface(Surf_Source, nullptr, Surf_Destination, &Rect);
}

void CSurface::ApplySprite(int x, int y, CSprite* Sprite, SDL_Surface* Surf_Destination)
{
    SDL_Rect Rect;

    Rect.x = x;
    Rect.y = y;

    SDL_BlitSurface(Sprite->GetSurface(), &Sprite->Offset, Surf_Destination, &Rect);
}

void CSurface::RenderText(int x, int y, const char* Text, SDL_Surface* Surf_Destination,
                          TTF_Font* Font, SDL_Color Color)
{
    SDL_Surface* Surf_Text = nullptr;

    // It crashes here
    Surf_Text = TTF_RenderText_Solid(Font, Text, Color);

    ApplySurface(x, y, Surf_Text, Surf_Destination);

    SDL_FreeSurface(Surf_Text);
}

bool CSurface::Collision(int x, int y, int w, int h, int x2, int y2, int w2, int h2)
{
    int LeftA, LeftB;
    int RightA, RightB;
    int TopA, TopB;
    int BottomA, BottomB;

    LeftA = x;
    RightA = x + w;
    TopA = y;
    BottomA = y + w;

    LeftB = x2;
    RightB = x2 + w2;
    TopB = y2;
    BottomB = y2 + w2;

    // Uncomment to see how dirty rects work
//    LeftB = x2 + 32;
//    RightB = x2 + w2 - 32;
//    TopB = y2 + 32;
//    BottomB = y2 + w2 - 32;

    if(LeftA >= RightB)
        return false;
    if(RightA <= LeftB)
        return false;
    if(TopA >= BottomB)
        return false;
    if(BottomA <= TopB)
        return false;

    // Collision
    return true;
}
