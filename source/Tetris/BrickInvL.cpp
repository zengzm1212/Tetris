#include "BrickInvL.h"



BrickInvL::BrickInvL()
{
    UpdateStatus();
}


BrickInvL::~BrickInvL()
{
}

void BrickInvL::UpdateStatus()
{
    switch (GetIndex())
    {
    case 0: { SetStatus(0x1130); break; }
    case 1: { SetStatus(0x7100); break; }
    case 2: { SetStatus(0x6440); break; }
    case 3: { SetStatus(0x0470); break; }
    }
}


