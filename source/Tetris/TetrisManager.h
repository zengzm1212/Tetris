#pragma once

#include "MacroDefines.h"
#include <QObject>

class QKeyEvent;
class QTimer;
class QGraphicsScene;

class Brick;
class TetrisEngine;

class TetrisManager : public QObject
{
    Q_OBJECT
public:
    TetrisManager();
    ~TetrisManager();
    //��ʼ�����������ľ���
    bool InitBackgroundMatrix(int** &pMatrix); 


    // ���ܴ�������¼�
    void ReactKeyEvent(QKeyEvent* e);
    
    void Move(EnKeyAction keyAction);

    void StartGame();
    void PauseGame();
    void RestartGame();
    void StopGame();

signals:
    // ��Ӧ���������·���λ��
    void UpdateBoxPosition(Brick* pBrick, EnKeyAction keyAction);
    void ChangeBrickToBackground(Brick* pBrick);
    void UpdateBackground();

public slots:
    void MoveDownOneStep();

public:
    int** GetBackgroundMatrix() { return m_pBackgroundpMatrix; }
    void SetBackgroundMatrix(int** pMatrix) { m_pBackgroundpMatrix = pMatrix; }
    Brick* GetBrick() { return m_pBrick; }
    void SetBrick(Brick* pBrick) { m_pBrick = pBrick; }

private: // ���ߺ���
    //�����ͷŶ�̬������ڴ�
    void deleteMatrix(int** pMatrix); 

private:
    QTimer* m_pTimer;
    int** m_pBackgroundpMatrix;     // ��������
    Brick* m_pBrick;                // �����ƶ��ķ�������
};

