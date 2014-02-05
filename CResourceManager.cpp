#include "CResourceManager.h"
#include "CSurface.h"
#include <iostream>

CResourceManager::CResourceManager() : CurrentID(0)
{
    // Default spriteSheets
    SpriteSheetMap["Default"] = std::make_shared<CSpriteSheet>("./resources/gfx/default.png");
    SpriteSheetMap["Tileset"] = std::make_shared<CSpriteSheet>("./resources/gfx/tileset.png");

    //==

//    SpriteMap["Null"] = std::make_shared<CSprite>(15 * 16, 15 * 16, 16, 16, SpriteSheetMap.at("Default"));
    CreateSprite("Null", 15 * 16, 15 * 16, 16, 16, SpriteSheetMap.at("Default"));

    //==

    // Default sprites, maybe separate sprites and tiles...

    CreateSprite("Cobblestone", 0 * 16, 1 * 16, 16, 16, SpriteSheetMap.at("Tileset"));
    CreateSprite("Dirt", 2 * 16, 0 * 16, 16, 16, SpriteSheetMap.at("Tileset"));
    CreateSprite("Tree", 5 * 16, 3 * 16, 16, 16, SpriteSheetMap.at("Tileset"));
    CreateSprite("Helm", 0 * 16, 0 * 16, 16, 16, SpriteSheetMap.at("Default"));
    CreateSprite("Apple", 10 * 16, 0 * 16, 16, 16, SpriteSheetMap.at("Default"));

}

CResourceManager::~CResourceManager()
{
    SpriteMap.clear();
    SpriteMapByID.clear();
    SpriteSheetMap.clear();
}

bool CResourceManager::LoadSpriteSheets()
{
    for(auto it = SpriteSheetMap.begin();
        it != SpriteSheetMap.end();
        it++)
    {
//        it->second->Surf_Sheet = CSurface::LoadSurface(it->second->Path);

        if((it->second->Surf_Sheet = CSurface::LoadSurface(it->second->Path)) == nullptr)
        {
            std::cerr << "error: \"" << it->second->Path << "\" is not present.\n";
            return false;
        }
    }

    return true;
}

// I don't think doing this will allow me to remove sprites.
void CResourceManager::CreateSprite(std::string Name, int x, int y, int w, int h,
                                    std::shared_ptr<CSpriteSheet> SpriteSheet)
{
    SpriteMap[Name] = std::make_shared<CSprite>(x, y, w, h, SpriteSheet);
    SpriteMapByID[CurrentID] = SpriteMap[Name];

    CurrentID++;
}

std::shared_ptr<CSprite> CResourceManager::GetSprite(std::string Key)
{
    if(SpriteMap.find(Key) == SpriteMap.end())
        return SpriteMap.at("Null");
    else
        return SpriteMap.at(Key);
}

std::shared_ptr<CSprite> CResourceManager::GetSprite(int ID)
{
    if(SpriteMapByID.find(ID) == SpriteMapByID.end())
        return SpriteMapByID.at(0); // 0 is "Null"
    else
        return SpriteMapByID.at(ID);
}

//std::shared_ptr<CSprite> CResourceManager::GetSprite(int ID)
//{
//    // Gets sprite by ID
//    // Doesn't work, maps are sorted by alphabetical order...
//
//    auto it = SpriteMap.begin();
//
//    int i = 0;
//    while(i != ID)
//    {
//        it++;
//        i++;
//    }
//
//    return it->second;
//}
