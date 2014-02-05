#ifndef CAREA_H
#define CAREA_H

#include "CMap.h"

class CResourceManager;

class CArea
{
public:
    CArea(CResourceManager* ResourceManager);
    ~CArea();

    bool OnLoad(char* File);
    void OnRender(SDL_Surface* Surf_Destination, int CameraX, int CameraY);

    int AreaSize;
    CResourceManager* ResourceManager;
    std::vector<CMap> MapList;
};

#endif // CAREA_H
