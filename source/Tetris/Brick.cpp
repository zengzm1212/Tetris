#include "Brick.h"
#include <cstdlib>

Brick::Brick() 
{
    m_index = rand() % 4;
    m_status = 0;
    m_row = 1;
    m_column = 3;
}

Brick::~Brick()
{
}

void Brick::Rotate()
{
    SetIndex(GetIndex() + 1);
    UpdateStatus();
}

Brick& Brick::operator=(Brick & euqal) 
{
    m_index = euqal.GetIndex();
    m_status = euqal.GetStatus();
    return *this;
}