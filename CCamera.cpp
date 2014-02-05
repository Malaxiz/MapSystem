#include "CCamera.h"
#include "CDefine.h"

CCamera::CCamera() :
    X(0), Y(0),
    TargetX(nullptr), TargetY(nullptr),
    TargetMode(TARGET_MODE_NORMAL)
{
}

CCamera::~CCamera()
{
}

void CCamera::OnMove(int MoveX, int MoveY)
{
    X += MoveX;
    Y += MoveY;
}

int CCamera::GetX()
{
    if(TargetX != nullptr)
        if(TargetMode == TARGET_MODE_CENTER)
            return *TargetX - WIDTH / 2;
        else
            return * TargetX;
    else
        return X;
}

int CCamera::GetY()
{
    if(TargetY != nullptr)
        if(TargetMode == TARGET_MODE_CENTER)
            return *TargetY - HEIGHT / 2;
        else
            return * TargetY;
    else
        return Y;
}

void CCamera::SetPos(int X, int Y)
{
    this->X = X;
    this->Y = Y;
}

void CCamera::SetTarget(int* X, int* Y)
{
    TargetX = X;
    TargetY = Y;
}
