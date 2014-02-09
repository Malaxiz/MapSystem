#ifndef CRESOURCEMANAGER_H
#define CRESOURCEMANAGER_H

#include <SDL_ttf.h>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "CSprite.h"
#include "CSpriteSheet.h"
#include "CTextBuffer.h"

#include "CAnimation.h"

class CResourceManager
{
public:
    CResourceManager();
    ~CResourceManager();

    bool LoadSpriteSheets();
    void CreateSprite(std::string SpriteType, std::string Name, int x, int y, int w, int h, std::shared_ptr<CSpriteSheet> SpriteSheet);
    void CreateTextBuffer(int x, int y, const char* Text, SDL_Surface* Surf_Destination,
                                        TTF_Font* Font, SDL_Color Color);
    void RenderTextBuffers();
    std::shared_ptr<CSprite> GetSprite(std::string SpriteType, std::string Key);
    std::shared_ptr<CSprite> GetSprite(std::string SpriteType, int ID);

    std::map<std::string, int> CurrentID;
//    int CurrentDebugTextID;
    std::map<std::string, std::map<std::string, std::shared_ptr<CSprite>>> SpriteMap;
    std::map<std::string, std::map<int, std::shared_ptr<CSprite>>> SpriteMapByID;
    std::map<std::string, std::map<std::string, std::shared_ptr<CAnimation>>> AnimationMap;
    std::map<std::string, std::shared_ptr<CSpriteSheet>> SpriteSheetMap;
    std::map<std::string, TTF_Font*> FontMap;
    std::vector<CTextBuffer> TextBufferVector;

};

#endif // CRESOURCEMANAGER_H
