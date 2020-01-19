#include "BrickL.h"

BrickL::BrickL()
{
    UpdateStatus();
}


BrickL::~BrickL()
{
}

void BrickL::UpdateStatus()
{
    switch (GetIndex())
    {
    case 0: { SetStatus(0x088C); break; }
    case 1: { SetStatus(0x002E); break; }
    case 2: { SetStatus(0x0C44); break; }
    case 3: { SetStatus(0x00E8); break; }
    }
}

