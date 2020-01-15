#include "BrickLine.h"



BrickLine::BrickLine()
{
    UpdateStatus();
}


BrickLine::~BrickLine()
{
}

void BrickLine::UpdateStatus()
{
    switch (GetIndex() % 2)
    {
    case 0: { SetStatus(0x0F00); break; }
    case 1: { SetStatus(0x2222); break; }
    //case 2: { SetStatus(0x0F00); break; }
    //case 3: { SetStatus(0x2222); break; }
    }
}
