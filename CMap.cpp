#include "CMap.h"
#include "CSurface.h"
#include "CSprite.h"
#include "CResourceManager.h"

CMap::CMap(CResourceManager* ResourceManager) :
    ResourceManager(ResourceManager)
{
}

bool CMap::OnLoad(char* File)
{
    TileList.clear();

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == nullptr)
        return false;

    for(int Y = 0; Y < MAP_HEIGHT; Y++)
    {
        for(int X = 0; X < MAP_WIDTH; X++)
        {
            CTile TempTile;

            fscanf(FileHandle, "%d:%d ", &TempTile.TileID, &TempTile.TypeID);

            TileList.push_back(TempTile);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

void CMap::OnRender(SDL_Surface* Surf_Destination, int MapX, int MapY, int CameraX, int CameraY)
{
    int ID = 0;

    for(int Y = 0; Y < MAP_HEIGHT; Y++)
    {
        for(int X = 0; X < MAP_WIDTH; X++)
        {
            if(TileList[ID].TypeID == TILE_TYPE_NONE)
            {
                ID++;
                continue;
            }

            int tX = MapX + (X * TILE_SIZE);
            int tY = MapY + (Y * TILE_SIZE);

            // Check if tile is inside camera, otherwise, don't bother rendering. 50% fps boost!
            if(CSurface::Collision(tX + CameraX, tY + CameraY, TILE_SIZE, TILE_SIZE, CameraX, CameraY, WIDTH, HEIGHT))
                ResourceManager->GetSprite(TileList[ID].TileID)->OnRender(tX, tY, Surf_Destination);

            ID++;
        }
    }
}

// The unoptimized
//void CMap::OnRender(SDL_Surface* Surf_Destination, int MapX, int MapY)
//{
//    int ID = 0;
//
//    for(int Y = 0; Y < MAP_HEIGHT; Y++)
//    {
//        for(int X = 0; X < MAP_WIDTH; X++)
//        {
//            if(TileList[ID].TypeID == TILE_TYPE_NONE)
//            {
//                ID++;
//                continue;
//            }
//
//            int tX = MapX + (X * TILE_SIZE);
//            int tY = MapY + (Y * TILE_SIZE);
//
//            ResourceManager->GetSprite(TileList[ID].TileID)->OnRender(tX, tY, Surf_Destination);
//
//            ID++;
//        }
//    }
//}
