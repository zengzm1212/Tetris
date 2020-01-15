#pragma once
#include "Brick.h"
class BrickZ : public Brick
{
public:
    BrickZ();
    ~BrickZ();
protected:
    virtual void UpdateStatus();
};

