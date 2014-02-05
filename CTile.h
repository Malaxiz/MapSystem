#ifndef CTILE_H
#define CTILE_H

#include "CDefine.h"

enum
{
    TILE_TYPE_NONE = 0,

    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK
};

class CTile
{
public:
    CTile();

    int TileID;
    int TypeID;
};

#endif // CTILE_H
