#pragma once

#include "Brick.h"
//L��
class BrickL : public Brick
{
public:
    BrickL();
    ~BrickL();
protected:
    virtual void UpdateStatus();
};

