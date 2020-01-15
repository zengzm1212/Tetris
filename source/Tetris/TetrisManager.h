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
    // ���ܴ�������¼�
    void TetrisManager::ReactKeyEvent(QKeyEvent* e);
    void Move(EnKeyAction keyAction);

};

