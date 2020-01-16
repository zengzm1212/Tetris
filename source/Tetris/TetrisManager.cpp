#include "TetrisManager.h"
#include "MacroDefines.h"
#include "BrickUtils.h"
#include "TetrisEngine.h"

#include <QKeyEvent>
#include <QTimer>


TetrisManager::TetrisManager()
{ 
    // init background
    InitBackgroundMatrix(m_pBackgroundpMatrix);
    // �������Brick
    m_pBrick = BrickUtils::CreateBrick();
    // init timer
    m_pTimer = new QTimer;
    m_pTimer->setInterval(TIME_INTERVAL);
    m_pTimer->setSingleShot(false);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(MoveDownOneStep()));
    // init engine
    m_pTreisEngine = new TetrisEngine;
}


TetrisManager::~TetrisManager()
{
    deleteMatrix(m_pBackgroundpMatrix); //�ͷŶ�̬������ڴ�

    if (m_pBrick)
        delete m_pBrick;
    if (m_pTimer)
        delete m_pTimer;
    if (m_pTreisEngine)
        delete m_pTreisEngine;
}


bool TetrisManager::InitBackgroundMatrix(int** &pMatrix)
{
    // ��̬������ڴ���Ҫ�������������ͷ�
    pMatrix = new int*[WINDOW_HEIGHT];
    for (size_t i = 0; i < WINDOW_HEIGHT; ++i)
        pMatrix[i] = new int[WINDOW_WIDTH];

    // ��ʼ����������״̬
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

    m_pTimer->start();
}

void TetrisManager::StartGame()
{
    m_pTimer->start();
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
    if (!m_pTreisEngine->NextStepIsReasonable(m_pBackgroundpMatrix, m_pBrick, DOWN))
    { // �����ж��л�ִ��һ�β��������������򳷻ظò���
        m_pTreisEngine->ReverseTransform(m_pBrick, DOWN);
    }
    emit UpdateBoxPosition(DOWN);
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
