#include "TetrisManager.h"
#include "MacroDefines.h"
#include "BrickUtils.h"
#include "TetrisEngine.h"
#include "Brick.h"

#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>

namespace
{
    void FindBackMatrix(int res[WINDOW_HEIGHT][WINDOW_WIDTH], int** pMatrix)
    {
        for (size_t i = 0; i < WINDOW_HEIGHT; ++i)
        {
            for (size_t j = 0; j < WINDOW_WIDTH; j++)
            {
                res[i][j] = pMatrix[i][j];
            }
        }
    }
}

TetrisManager::TetrisManager()
{ 
    // init background
    InitBackgroundMatrix(m_pBackgroundpMatrix);
    //int res[WINDOW_HEIGHT][WINDOW_WIDTH];
    //FindBackMatrix(res, m_pBackgroundpMatrix);

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
    if (keyAction == EnKeyAction::DOWN)
    {
        if (!TetrisEngine::NextStepIsReasonable(m_pBackgroundpMatrix, m_pBrick, DOWN))
        {
            bool currentBrick[4][4];
            for (size_t i = 0; i < 4; ++i)
            {
                for (size_t j = 0; j < 4; ++j)
                {
                    currentBrick[i][j] = ((m_pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
                    if (currentBrick[i][j])
                    {
                        m_pBackgroundpMatrix[m_pBrick->GetBrickRow() - 3 + i][m_pBrick->GetBrickColumn() + j] = 1;
                    }
                }
            }
            emit UpdateBackground();
            delete m_pBrick;
            m_pBrick = BrickUtils::CreateBrick();
        }
    }

    if (TetrisEngine::NextStepIsReasonable(m_pBackgroundpMatrix, m_pBrick, keyAction))
    {
        TetrisEngine::KeyTransform(m_pBrick, keyAction);
        emit UpdateBoxPosition(m_pBrick, keyAction);
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
    if (TetrisEngine::NextStepIsReasonable(m_pBackgroundpMatrix, m_pBrick, DOWN))
    { // 条件判断中会执行一次操作，若不合理则撤回该操作
        TetrisEngine::KeyTransform(m_pBrick, DOWN);
        emit UpdateBoxPosition(m_pBrick, DOWN);
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
