#include "CResourceManager.h"
#include "CSurface.h"
#include <iostream>
#include "CDefine.h"

CResourceManager::CResourceManager()
{
    // Default spriteSheets
    SpriteSheetMap["Default"] = std::make_shared<CSpriteSheet>("./resources/gfx/default.png");
    SpriteSheetMap["Tileset"] = std::make_shared<CSpriteSheet>("./resources/gfx/tileset.png");

    //==

    CreateSprite("DefaultSprite", "Null", 15 * 16, 15 * 16, 16, 16, SpriteSheetMap.at("Default"));

    //==

    // Default ItemSprites

    CreateSprite("ItemSprite", "Helm", 0 * 16, 0 * 16, 16, 16, SpriteSheetMap.at("Default"));
    CreateSprite("ItemSprite", "Apple", 10 * 16, 0 * 16, 16, 16, SpriteSheetMap.at("Default"));

    // Default TileSprites

    CreateSprite("TileSprite", "Dirt", 2 * 16, 0 * 16, 16, 16, SpriteSheetMap.at("Tileset"));
    CreateSprite("TileSprite", "Cobblestone", 0 * 16, 1 * 16, 16, 16, SpriteSheetMap.at("Tileset"));
    CreateSprite("TileSprite", "Tree", 5 * 16, 3 * 16, 16, 16, SpriteSheetMap.at("Tileset"));

}

CResourceManager::~CResourceManager()
{
    // Is this how I should do it?
    for(auto it = FontMap.begin();
        it != FontMap.end();
        it++)
    {
        TTF_CloseFont(it->second);
    }

    FontMap.clear();
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
        if((it->second->Surf_Sheet = CSurface::LoadSurface(it->second->Path)) == nullptr)
        {
            std::cerr << "error: \"" << it->second->Path << "\" is not present.\n";
            return false;
        }
    }

    // Default fonts

    FontMap["TestFont"] = TTF_OpenFont("./resources/fonts/Minecraftia.ttf", DEFAULT_TEXT_SIZE);

    for(auto it = FontMap.begin();
        it != FontMap.end();
        it++)
    {
        if(it->second == nullptr)
        {
            std::cerr << "error: Could not find game font (./resources/fonts/)\n";
        }
    }

    return true;
}

// I don't think doing this will allow me to remove sprites.
void CResourceManager::CreateSprite(std::string SpriteType, std::string Name, int x, int y, int w, int h,
                                    std::shared_ptr<CSpriteSheet> SpriteSheet)
{
    SpriteMap[SpriteType][Name] = std::make_shared<CSprite>(x, y, w, h, SpriteSheet);
    SpriteMapByID[SpriteType][CurrentID[SpriteType]] = SpriteMap[SpriteType][Name];

    CurrentID[SpriteType]++;
}

void CResourceManager::CreateTextBuffer(int x, int y, const char* Text, SDL_Surface* Surf_Destination,
                                        TTF_Font* Font, SDL_Color Color)
{
    std::string TempText(Text);

    TextBuffer Buffer(x, y, TempText, Surf_Destination, Font, Color);

    TextBufferVector.push_back(Buffer);
}

void CResourceManager::RenderTextBuffers()
{
    // Maybe I should do some kind of system that automatically..
    // .. puts the text in the order they were added to the vector.
    // But then I can't add text for dialog. This is a good way for now.
    // (Maybe add a DEBUG flag...)

    for(auto it = TextBufferVector.begin();
        it != TextBufferVector.end();
        it++)
    {
        auto Text = (*it);

        CSurface::RenderText(Text.x, Text.y, Text.Text.c_str(), Text.Surf_Destination,
                             Text.Font, Text.Color);
    }

    TextBufferVector.clear();
}

std::shared_ptr<CSprite> CResourceManager::GetSprite(std::string SpriteType, std::string Key)
{
    if(SpriteMap.find(SpriteType) == SpriteMap.end())
        return SpriteMap.at("DefaultSprite").at("Null");
    else
        if(SpriteMap.at(SpriteType).find(Key) == SpriteMap.at(SpriteType).end())
            return SpriteMap.at("DefaultSprite").at("Null");
        else
            return SpriteMap.at(SpriteType).at(Key);
}

std::shared_ptr<CSprite> CResourceManager::GetSprite(std::string SpriteType, int ID)
{
    if(SpriteMapByID.find(SpriteType) == SpriteMapByID.end())
        return SpriteMap.at("DefaultSprite").at("Null");
    else
        if(SpriteMapByID.at(SpriteType).find(ID) == SpriteMapByID.at(SpriteType).end())
            return SpriteMap.at("DefaultSprite").at("Null");
        else
            return SpriteMapByID.at(SpriteType).at(ID);
}
