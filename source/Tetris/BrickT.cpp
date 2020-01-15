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
    case 0: { SetStatus(0x7200); break; }
    case 1: { SetStatus(0x4640); break; }
    case 2: { SetStatus(0x0270); break; }
    case 3: { SetStatus(0x1310); break; }
    }
}
