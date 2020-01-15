#include "TetrisManager.h"
#include "MacroDefines.h"
#include <QKeyEvent>


TetrisManager::TetrisManager()
{
}


TetrisManager::~TetrisManager()
{
}

void TetrisManager::ReactKeyEvent(QKeyEvent* e)
{
    switch (e->key())
    {
    case Qt::Key_Up:
        Move(EnKeyAction::LEFT);
        break;
    case Qt::Key_Left:
        Move(EnKeyAction::RIGHT);
        break;
    case Qt::Key_Right:
        Move(EnKeyAction::UP);
        break;
    case Qt::Key_Down:
        Move(EnKeyAction::DOWN);
        break;
    default:
        break;
    }
}

void TetrisManager::Move(EnKeyAction keyAction)
{

}