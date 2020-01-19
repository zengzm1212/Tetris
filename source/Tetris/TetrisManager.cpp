#include "TetrisManager.h"
#include "MacroDefines.h"
#include "BrickUtils.h"
#include "TetrisEngine.h"

#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>


TetrisManager::TetrisManager()
{ 
    // init background
    InitBackgroundMatrix(m_pBackgroundpMatrix);
    // 随机生成Brick
    m_pBrick = BrickUtils::CreateBrick();
    // init timer
    m_pTimer = new QTimer;
    m_pTimer->setInterval(TIME_INTERVAL);
    m_pTimer->setSingleShot(false);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(MoveDownOneStep()));
}


TetrisManager::~TetrisManager()
{
    deleteMatrix(m_pBackgroundpMatrix); //释放动态分配的内存

    if (m_pBrick)
        delete m_pBrick;
    if (m_pTimer)
        delete m_pTimer;
}


bool TetrisManager::InitBackgroundMatrix(int** &pMatrix)
{
    // 动态分配的内存需要在析构函数中释放
    pMatrix = new int*[WINDOW_HEIGHT];
    for (size_t i = 0; i < WINDOW_HEIGHT; ++i)
        pMatrix[i] = new int[WINDOW_WIDTH];

    // 初始化背景矩阵状态
    for (size_t i = 0; i < WINDOW_HEIGHT; ++i)
        for (size_t j = 0; j < WINDOW_WIDTH; ++j)
            pMatrix[i][j] = 0;

    return true;
}

void TetrisManager::ReactKeyEvent(QKeyEvent* e)
{
    switch (e->key())
    {
    case Qt::Key_Up:
        Move(EnKeyAction::UP);
        break;
    case Qt::Key_Left:
        Move(EnKeyAction::LEFT);
        break;
    case Qt::Key_Right:
        Move(EnKeyAction::RIGHT);
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
    TetrisEngine::KeyTransform(m_pBrick, keyAction);
    //if (keyAction == EnKeyAction::UP)
    //{
    //    emit UpdateBoxUpPosition(m_pBrick);
    //}
    //else
    {
        emit UpdateBoxPosition(keyAction, m_pBrick);
    }
}

void TetrisManager::StartGame()
{
    //m_pTimer->start();
}
void TetrisManager::PauseGame()
{

}
void TetrisManager::RestartGame()
{

}
void TetrisManager::StopGame()
{

}
void TetrisManager::MoveDownOneStep()
{
    if (!TetrisEngine::NextStepIsReasonable(m_pBackgroundpMatrix, m_pBrick, DOWN))
    { // 条件判断中会执行一次操作，若不合理则撤回该操作
        TetrisEngine::ReverseTransform(m_pBrick, DOWN);
        //emit UpdateBoxPosition(DOWN);
    }  
}

void TetrisManager::deleteMatrix(int** pMatrix)
{
    for (size_t j = 0; j < WINDOW_HEIGHT; ++j)
    {
        delete pMatrix[j];
        pMatrix[j] = nullptr;
    }
    delete pMatrix;
    pMatrix = nullptr;
}
