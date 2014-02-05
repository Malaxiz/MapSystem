#ifndef CRESOURCEMANAGER_H
#define CRESOURCEMANAGER_H

#include <memory>
#include <map>
#include <string>
#include "CSprite.h"
#include "CSpriteSheet.h"

class CResourceManager
{
public:
    CResourceManager();
    ~CResourceManager();

    bool LoadSpriteSheets();
    void CreateSprite(std::string Name, int x, int y, int w, int h, std::shared_ptr<CSpriteSheet> SpriteSheet);
    std::shared_ptr<CSprite> GetSprite(std::string Key);
    std::shared_ptr<CSprite> GetSprite(int ID);

    int CurrentID;
    std::map<std::string, std::shared_ptr<CSprite>> SpriteMap;
    std::map<int, std::shared_ptr<CSprite>> SpriteMapByID;
    std::map<std::string, std::shared_ptr<CSpriteSheet>> SpriteSheetMap;

};

#endif // CRESOURCEMANAGER_H
