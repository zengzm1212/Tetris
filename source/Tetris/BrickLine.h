#pragma once
#include "Brick.h"

class BrickLine : public Brick
{
public:
    BrickLine();
    ~BrickLine();

protected:
    virtual void UpdateStatus();

};

