#include "BrickInvZ.h"



BrickInvZ::BrickInvZ()
{
    UpdateStatus();
}


BrickInvZ::~BrickInvZ()
{
}

void BrickInvZ::UpdateStatus()
{
    switch (GetIndex())
    {
    case 0: { SetStatus(0x08C4); break; }
    case 1: { SetStatus(0x006C); break; }
    case 2: { SetStatus(0x08C4); break; }
    case 3: { SetStatus(0x006C); break; }
    }
}