#ifndef CMAP_H
#define CMAP_H

#include <vector>
#include <SDL.h>
#include "CTile.h"

class CResourceManager;

class CMap
{
public:
    CMap(CResourceManager* ResourceManager);

    bool OnLoad(char* File);
    void OnRender(SDL_Surface* Surf_Destination, int MapX, int MapY, int CameraX, int CameraY);
    // The unoptimized
//    void OnRender(SDL_Surface* Surf_Destination, int MapX, int MapY);

    CResourceManager* ResourceManager;
    std::vector<CTile> TileList;
};

#endif // CMAP_H
