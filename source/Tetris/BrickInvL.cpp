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
    case 0: { SetStatus(0x044C); break; }
    case 1: { SetStatus(0x00E2); break; }
    case 2: { SetStatus(0x0C88); break; }
    case 3: { SetStatus(0x008E); break; }
    }
}


