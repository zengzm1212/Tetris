#include "BrickT.h"



BrickT::BrickT()
{
    UpdateStatus();
}


BrickT::~BrickT()
{
}

void BrickT::UpdateStatus()
{
    switch (GetIndex())
    {
    case 0: { SetStatus(0x00E4); break; }
    case 1: { SetStatus(0x08C8); break; }
    case 2: { SetStatus(0x004E); break; }
    case 3: { SetStatus(0x04C4); break; }
    }
}
