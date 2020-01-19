#include "Brick.h"
#include <cstdlib>

Brick::Brick() 
{
    m_index = rand() % 4;
    m_status = 0;
    m_row = 1;
    m_column = 3;
    m_isFrozen = false;
}

Brick::~Brick()
{
}

void Brick::Rotate()
{
    SetIndex((GetIndex() + 1) % 4);
    UpdateStatus();
}

Brick& Brick::operator=(Brick & euqal) 
{
    m_index = euqal.GetIndex();
    m_status = euqal.GetStatus();
    m_row = euqal.GetBrickRow();
    m_column = euqal.GetBrickColumn();
    return *this;
}