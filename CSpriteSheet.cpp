#include "CSpriteSheet.h"

CSpriteSheet::CSpriteSheet(std::string Path) :
    Surf_Sheet(nullptr), Path(Path)
{
}

CSpriteSheet::~CSpriteSheet()
{
    SDL_FreeSurface(Surf_Sheet);
}
