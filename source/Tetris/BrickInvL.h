#pragma once

#include "Brick.h"
class BrickInvL : public Brick
{
public:
    BrickInvL();
    ~BrickInvL();
protected:
    virtual void UpdateStatus();
};

