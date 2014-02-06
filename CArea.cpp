#include "CArea.h"
#include "CResourceManager.h"
#include "CDefine.h"
#include "CSurface.h"
#include <sstream>

#include <iostream>

CArea::CArea(CResourceManager* ResourceManager) :
    AreaSize(0), ResourceManager(ResourceManager)
{
}

CArea::~CArea()
{
    MapList.clear();
}

bool CArea::OnLoad(char* File)
{
    MapList.clear();

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == nullptr)
        return false;

    fscanf(FileHandle, "%d\n", &AreaSize);

    for(int X = 0; X < AreaSize; X++)
    {
        for(int Y = 0; Y < AreaSize; Y++)
        {
            char MapFile[255];

            fscanf(FileHandle, "%s", MapFile);

            CMap TempMap(ResourceManager);

            if(TempMap.OnLoad(MapFile) == false)
            {
                fclose(FileHandle);

                return false;
            }

            MapList.push_back(TempMap);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

void CArea::OnRender(SDL_Surface* Surf_Destination, int CameraX, int CameraY)
{
    int MapWidth = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int FirstID = CameraX / MapWidth;
        FirstID = FirstID + ((CameraY / MapHeight) * AreaSize);

    // Temp
    std::stringstream Text;
    Text << "MapID's loaded: ";

    for(int i = 0; i < 4; i++)
    {
        int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

        Text << ID << ", ";

        if(ID < 0 || ID >= MapList.size())
            continue;

        // Check if map is inside camera, otherwise, don't bother rendering. 20% - 40% fps boost!
        if(!CSurface::Collision((ID % AreaSize) * MapWidth, (ID / AreaSize) * MapHeight,
                                MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE,
                                CameraX, CameraY, WIDTH, HEIGHT))
            continue;

        int X = ((ID % AreaSize) * MapWidth) - CameraX;
        int Y = ((ID / AreaSize) * MapHeight) - CameraY;

        MapList[ID].OnRender(Surf_Destination, X, Y, CameraX, CameraY);
    }

    // Temp
    ResourceManager->CreateTextBuffer(0, 0, Text.str().c_str(), Surf_Destination,
                         ResourceManager->FontMap["TestFont"], {0xFF, 0xFF, 0xFF});
}

// The unoptimized
//void CArea::OnRender(SDL_Surface* Surf_Destination, int CameraX, int CameraY)
//{
//    int MapWidth = MAP_WIDTH * TILE_SIZE;
//    int MapHeight = MAP_HEIGHT * TILE_SIZE;
//
//    int FirstID = CameraX / MapWidth;
//        FirstID = FirstID + ((CameraY / MapHeight) * AreaSize);
//
//    for(int i = 0; i < 4; i++)
//    {
//        int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);
//
//        if(ID < 0 || ID >= MapList.size())
//            continue;
//
//        int X = ((ID % AreaSize) * MapWidth) - CameraX;
//        int Y = ((ID / AreaSize) * MapHeight) - CameraY;
//
//        MapList[ID].OnRender(Surf_Destination, X, Y);
//    }
//}
