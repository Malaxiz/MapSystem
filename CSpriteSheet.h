#ifndef CSPRITESHEET_H
#define CSPRITESHEET_H

#include <SDL.h>
#include <string>

class CSpriteSheet
{
public:
    CSpriteSheet(std::string Path);
    ~CSpriteSheet();

    SDL_Surface* Surf_Sheet;

    std::string Path;
};

#endif // CSPRITESHEET_H
