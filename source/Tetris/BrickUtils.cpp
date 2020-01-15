#include "BrickUtils.h"
#include "BirckSquare.h"
#include "BrickInvL.h"
#include "BrickInvZ.h"
#include "BrickL.h"
#include "BrickLine.h"
#include "BrickT.h"
#include "BrickZ.h"
#include <cstdlib>

Brick* BrickUtils::CreateBrick()
{
    Brick* pBrock;
    int rad = rand() % 7;
    switch (rad) {
    case 0: {	pBrock = new BirckSquare();	break; }
    case 1: {	pBrock = new BrickZ();	break;  }
    case 2: {	pBrock = new BrickL();	break;  }
    case 3: {	pBrock = new BrickInvZ();	break;  }
    case 4: {	pBrock = new BrickInvL();	break;  }
    case 5: {	pBrock = new BrickT();	break;  }
    case 6: {	pBrock = new BrickLine();	break;  }
    }
    return pBrock;
}
