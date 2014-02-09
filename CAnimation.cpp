#include "CAnimation.h"
#include "CSurface.h"
#include "CSprite.h"
#include <iostream>

CAnimation::CAnimation(std::shared_ptr<CSpriteSheet> SpriteSheet, std::vector<SDL_Rect> Offsets) :
    LastTime(SDL_GetTicks()), FrameRate(100), CurrentFrame(0), SpriteSheet(SpriteSheet)
{
    for(int i = 0; (Uint16)i < Offsets.size(); i++)
    {
        this->Offsets.push_back(Offsets[i]);
    }
}

CAnimation::~CAnimation()
{
    Offsets.clear();
}

void CAnimation::OnRender(int x, int y, SDL_Surface* Surf_Destination)
{
    // Should I do this before or after I've rendered the sprite?
    if(SDL_GetTicks() - LastTime > (Uint16)FrameRate)
    {
        LastTime += FrameRate;
        if((Uint16)CurrentFrame >= Offsets.size() - 1)
            CurrentFrame = 0;
        else
            CurrentFrame++;
    }

    CSprite TempSprite(Offsets[CurrentFrame].x, Offsets[CurrentFrame].y, Offsets[CurrentFrame].w, Offsets[CurrentFrame].h, SpriteSheet);

    CSurface::ApplySprite(x, y, &TempSprite, Surf_Destination);
}
