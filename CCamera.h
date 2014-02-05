#ifndef CCAMERA_H
#define CCAMERA_H

enum
{
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class CCamera
{
public:
    CCamera();
    ~CCamera();

    int X;
    int Y;

    int* TargetX;
    int* TargetY;

    int TargetMode;

    void OnMove(int MoveX, int MoveY);

    int GetX();
    int GetY();

    void SetPos(int X, int Y);
    void SetTarget(int* X, int* Y);
};

#endif // CCAMERA_H
