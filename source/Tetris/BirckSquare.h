#pragma once
//����
#include "Brick.h"
class BirckSquare : public Brick
{
public:
    BirckSquare();
    ~BirckSquare();

protected:
    virtual void UpdateStatus();
};

