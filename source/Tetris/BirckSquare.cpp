#include "BirckSquare.h"

BirckSquare::BirckSquare()
{
    UpdateStatus();
}


BirckSquare::~BirckSquare()
{
}


void BirckSquare::UpdateStatus()
{
    SetStatus(0xCC00);
}