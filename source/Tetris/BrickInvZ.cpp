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
    case 0: { SetStatus(0x1320); break; }
    case 1: { SetStatus(0x6300); break; }
    case 2: { SetStatus(0x2640); break; }
    case 3: { SetStatus(0x0630); break; }
    }
}