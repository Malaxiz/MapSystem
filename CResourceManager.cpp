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

    // Default DefaultSprites

    CreateSprite("DefaultSprite", "Null", 15 * 16, 15 * 16, 16, 16, SpriteSheetMap.at("Default"));

    // Default ItemSprites

    CreateSprite("ItemSprite", "Helm", 0 * 16, 0 * 16, 16, 16, SpriteSheetMap.at("Default"));
    CreateSprite("ItemSprite", "Apple", 10 * 16, 0 * 16, 16, 16, SpriteSheetMap.at("Default"));

    // Default TileSprites

    CreateSprite("TileSprite", "Dirt", 2 * 16, 0 * 16, 16, 16, SpriteSheetMap.at("Tileset"));
    CreateSprite("TileSprite", "Cobblestone", 0 * 16, 1 * 16, 16, 16, SpriteSheetMap.at("Tileset"));
    CreateSprite("TileSprite", "Tree", 5 * 16, 3 * 16, 16, 16, SpriteSheetMap.at("Tileset"));

    // In the future the animation offsets will be loaded from files
    std::vector<SDL_Rect> Offsets;

    // Wheat looping
    for(int x = 8; x <= 14; x++)
        Offsets.push_back({x * 16, 5 * 16, 16, 16});

    AnimationMap["TestAnimation"]["Wheat"] = std::make_shared<CAnimation>(SpriteSheetMap.at("Tileset"), Offsets);

    Offsets.clear();

    // Wool looping
    for(int x = 0; x <= 15; x++)
        Offsets.push_back({x * 16, 4 * 16, 16, 16});

    AnimationMap["TestAnimation"]["Wool"] = std::make_shared<CAnimation>(SpriteSheetMap.at("Tileset"), Offsets);

    Offsets.clear();

    // All tiles
    for(int y = 0; y < 16; y++)
        for(int x = 0; x < 16; x++)
            Offsets.push_back({16 * x, 16 * y, 16, 16});

    AnimationMap["TestAnimation"]["All"] = std::make_shared<CAnimation>(SpriteSheetMap.at("Tileset"), Offsets);

    Offsets.clear();

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

    CTextBuffer Buffer(x, y, TempText, Surf_Destination, Font, Color);

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
