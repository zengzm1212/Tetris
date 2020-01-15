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
    case 0: { SetStatus(0x4620); break; }
    case 1: { SetStatus(0x0360); break; }
    case 2: { SetStatus(0x2310); break; }
    case 3: { SetStatus(0x3600); break; }
    }
}
