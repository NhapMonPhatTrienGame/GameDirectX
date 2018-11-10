#include "BrickGold.h"

BrickGold::BrickGold(D3DXVECTOR3 position)
{
    Init(position);
}

const char * BrickGold::FileName()
{
    return "Resources/goldbrick.png";
}

int BrickGold::TotalFrame()
{
    return 4;
}

int BrickGold::Row()
{
    return 1;
}

int BrickGold::Column()
{
    return 4;
}

float BrickGold::TimePerFrame()
{
    return 0.3f;
}
