#include "BrickZ.h"


BrickZ::BrickZ()
{
    UpdateStatus();
}


BrickZ::~BrickZ()
{
}

void BrickZ::UpdateStatus()
{
    switch (GetIndex())
    {
    case 0: { SetStatus(0x00C6); break; }
    case 1: { SetStatus(0x04C8); break; }
    case 2: { SetStatus(0x00C6); break; }
    case 3: { SetStatus(0x04C8); break; }
    }
}
