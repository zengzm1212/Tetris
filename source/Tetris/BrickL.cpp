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
    case 0: { SetStatus(0x4460); break; }
    case 1: { SetStatus(0x0170); break; }
    case 2: { SetStatus(0x3110); break; }
    case 3: { SetStatus(0x7400); break; }
    }
}

