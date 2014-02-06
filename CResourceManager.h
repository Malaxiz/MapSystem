#ifndef CRESOURCEMANAGER_H
#define CRESOURCEMANAGER_H

#include <SDL_ttf.h>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "CSprite.h"
#include "CSpriteSheet.h"
#include "TextBuffer.h"

class CResourceManager
{
public:
    CResourceManager();
    ~CResourceManager();

    bool LoadSpriteSheets();
    void CreateSprite(std::string Name, int x, int y, int w, int h, std::shared_ptr<CSpriteSheet> SpriteSheet);
    void CreateTextBuffer(int x, int y, const char* Text, SDL_Surface* Surf_Destination,
                                        TTF_Font* Font, SDL_Color Color);
    void RenderTextBuffers();
    std::shared_ptr<CSprite> GetSprite(std::string Key);
    std::shared_ptr<CSprite> GetSprite(int ID);

    int CurrentID;
    std::map<std::string, std::shared_ptr<CSprite>> SpriteMap;
    std::map<int, std::shared_ptr<CSprite>> SpriteMapByID;
    std::map<std::string, std::shared_ptr<CSpriteSheet>> SpriteSheetMap;
    std::map<std::string, TTF_Font*> FontMap;
    std::vector<TextBuffer> TextBufferVector;

};

#endif // CRESOURCEMANAGER_H
