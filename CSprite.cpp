#include "CSprite.h"
#include "CSurface.h"

CSprite::CSprite(int x, int y, int w, int h, std::shared_ptr<CSpriteSheet> SpriteSheet) :
    Offset{(Sint16)x, (Sint16)y, (Uint16)w, (Uint16)h}, SpriteSheet(SpriteSheet)
{
}

CSprite::~CSprite()
{
}

void CSprite::OnRender(int x, int y, SDL_Surface* Surf_Destination)
{
    CSurface::ApplySprite(x, y, this, Surf_Destination);
}

SDL_Surface* CSprite::GetSurface()
{
    return SpriteSheet->Surf_Sheet;
}
