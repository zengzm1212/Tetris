#pragma once

#include "Brick.h"
class BrickInvZ : public Brick
{
public:
    BrickInvZ();
    ~BrickInvZ();
protected:
    virtual void UpdateStatus();
};

