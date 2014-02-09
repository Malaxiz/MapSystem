#ifndef CANIMATION_H
#define CANIMATION_H

#include <memory>
#include <vector>
#include "CSpriteSheet.h"

class CAnimation
{
public:
    CAnimation(std::shared_ptr<CSpriteSheet> SpriteSheet, std::vector<SDL_Rect> Offsets);
    ~CAnimation();

    void OnRender(int x, int y, SDL_Surface* Surf_Destination);
    void SetFrameRate(int FrameRate);

    int LastTime;
    int FrameRate; // Frame per millisecond
    int CurrentFrame;
    std::shared_ptr<CSpriteSheet> SpriteSheet;
    std::vector<SDL_Rect> Offsets;

};

#endif // CANIMATION_H
