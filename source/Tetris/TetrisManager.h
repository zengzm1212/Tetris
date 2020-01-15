#pragma once

#include "MacroDefines.h"
#include <QObject>

class QKeyEvent;

class TetrisManager : public QObject
{
    Q_OBJECT
public:
    TetrisManager();
    ~TetrisManager();
    // 接受处理键盘事件
    void TetrisManager::ReactKeyEvent(QKeyEvent* e);
    void Move(EnKeyAction keyAction);

};

