#pragma once

#include "Brick.h"
class BrickT : public Brick
{
public:
    BrickT();
    ~BrickT();
protected:
    virtual void UpdateStatus();
};

