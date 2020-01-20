#include "TetrisMainWindow.h"
#include "Box.h"
#include "Brick.h"
#include "TetrisManager.h"
#include "TetrisEngine.h"
#include <QGraphicsLineItem>
#include <QKeyEvent>

namespace
{
    bool ParseBrick(bool parsedMatrix[4][4], Brick* pBrick)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                parsedMatrix[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            }
        }
        return true;
    }
}


TetrisMainWindow::TetrisMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    ui = new Ui::TetrisMainWindowClass();
	ui->setupUi(this);

    for (size_t i = 0; i < WINDOW_HEIGHT; ++i)
    {
        for (size_t j = 0; j < WINDOW_WIDTH; ++j)
        {
            m_pBackgroundBoxs[i*WINDOW_WIDTH + j] = nullptr;
        }
    }

    for (size_t i = 0; i < 4; ++i)
    {
        m_p4Boxs[i] = nullptr;
    }

    m_pTetrisManager = new TetrisManager;

    initGraphicsViewWidget();

    //m_p4Boxs[0] = new Box(0, 0);
    //m_p4Boxs[1] = new Box(1, 0);
    //m_p4Boxs[2] = new Box(2, 0);
    //m_p4Boxs[3] = new Box(3, 0);
    //m_scene->addItem(m_p4Boxs[0]);
    //m_scene->addItem(m_p4Boxs[1]);
    //m_scene->addItem(m_p4Boxs[2]);
    //m_scene->addItem(m_p4Boxs[3]);
    //m_scene->removeItem(m_p4Boxs[3]);
    //m_p4Boxs[3] = new Box(4, 0);
    //m_p4Boxs[3]->SetColor(Qt::blue);
    //m_scene->addItem(m_p4Boxs[3]);

    //DisplayUiView();
    DisplayMovingBricks();

    //ʹ�÷�����֧�ּ��̲���
    //setFlags(QGraphicsItem::ItemIsFocusable);
    setFocus();
    //setFocusPolicy();

    // ��ʼ����Ա����
    

    // �󶨽���İ���
    connect(ui->m_startButton, SIGNAL(clicked()), this, SLOT(StartGame()));
    connect(ui->m_pauseButton, SIGNAL(clicked()), this, SLOT(PauseGame()));
    connect(ui->m_restartButton, SIGNAL(clicked()), this, SLOT(RestartGame()));
    connect(ui->m_overButton, SIGNAL(clicked()), this, SLOT(StopGame()));

    // �󶨰������źŴ���
    connect(m_pTetrisManager, &TetrisManager::UpdateBoxPosition, this, &TetrisMainWindow::UpdateUiBoxPosition);
    connect(m_pTetrisManager, &TetrisManager::ChangeBrickToBackground, this, &TetrisMainWindow::ChangeUiBoxToBackground);
    connect(m_pTetrisManager, &TetrisManager::UpdateBackground, this, &TetrisMainWindow::UpdateBackgroundBoxs);
}

TetrisMainWindow::~TetrisMainWindow()
{
    delete ui;     //Qt���ͷ��ڴ�ֻ���ͷŸ��ڵ㼴��

    if (m_pTetrisManager)
        delete m_pTetrisManager;
}

void TetrisMainWindow::keyPressEvent(QKeyEvent* e)
{
    m_pTetrisManager->ReactKeyEvent(e);
}

void TetrisMainWindow::initGraphicsViewWidget()
{
    //ʹ�ÿ������Ⱦ
    ui->m_graphicsView->setRenderHint(QPainter::Antialiasing);
    //���û��屳����������Ⱦ
    ui->m_graphicsView->setCacheMode(QGraphicsView::CacheBackground);

    m_scene = new QGraphicsScene(this);       // QGraphicsSceneΪ������QGraphicsViewΪ�ӿ� ������������Զ�ά��ͼ����
    m_scene->setSceneRect(30, 30, 310, 410);  // Ϊʲô�������������������߽���ҪС
    ui->m_graphicsView->setScene(m_scene);

    //������ƶ���������
    //������չ3���أ���������ʹ�����鵽��߽��ʱ�����ƶ��ͻᷢ����ײ
    // ��ʾ���ӿڷ�Χ��graphicView�ķ�Χ����setui���Ѿ����ú���
    m_topLine = m_scene->addLine(32, 32, 238, 32); //�൱�ں���35-235������35-435   
    m_leftLine = m_scene->addLine(32, 32, 32, 438);
    m_buttomLine = m_scene->addLine(32, 438, 238, 438);
    m_rightLine = m_scene->addLine(238, 32, 238, 438);
    // ���������ߵ���ɫ
    m_topLine->setPen(QPen(QColor(0, 0, 0)));
    m_leftLine->setPen(QPen(QColor(0, 0, 0)));
    m_buttomLine->setPen(QPen(QColor(0, 0, 0)));
    m_rightLine->setPen(QPen(QColor(0, 0, 0)));
}

void TetrisMainWindow::StartGame()
{
    m_pTetrisManager->StartGame();
}
void TetrisMainWindow::PauseGame()
{
    m_pTetrisManager->PauseGame();
}
void TetrisMainWindow::RestartGame()
{
    m_pTetrisManager->RestartGame();
}
void TetrisMainWindow::StopGame()
{
    m_pTetrisManager->StopGame();
}

void TetrisMainWindow::UpdateUiBoxPosition(Brick* pBrick, EnKeyAction keyAction)
{
    //for (size_t i = 0; i < 4; ++i)
    //{
    //    if(keyAction == EnKeyAction::DOWN)
    //        m_p4Boxs[i]->moveBy(0, 20);
    //    else if(keyAction == EnKeyAction::LEFT)
    //        m_p4Boxs[i]->moveBy(-20, 0);
    //    else if(keyAction == EnKeyAction::RIGHT)
    //        m_p4Boxs[i]->moveBy(20, 0);
    //}

    // ��ʾ��������������ǽ�DB���������ʾ����
    for (size_t i = 0; i < 4; ++i)
    {
        m_scene->removeItem(m_p4Boxs[i]);
        delete m_p4Boxs[i]; //�ͷ��ڴ�
        m_p4Boxs[i] = nullptr;
    }
    bool currentBrick[4][4];
    int num = 0;
    ParseBrick(currentBrick, pBrick);
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (currentBrick[i][j] == 1)
            {
                m_p4Boxs[num] = new Box((pBrick->GetBrickRow() -3 + i), (pBrick->GetBrickColumn() + j));
                m_scene->addItem(m_p4Boxs[num]);
                num++;
            }
        }
    }
}

void TetrisMainWindow::DisplayUiView()
{
    // ��ʾ����
    int** pMatrix = m_pTetrisManager->GetBackgroundMatrix();
    int num = 0;
    for (size_t i = 0; i < WINDOW_HEIGHT; ++i)
    {
        for (size_t j = 0; j < WINDOW_WIDTH; ++j)
        {
            if (pMatrix[i][j] == 1)
            {
                m_pBackgroundBoxs[i*WINDOW_WIDTH + j] = new Box(i, j);
                m_scene->addItem(m_pBackgroundBoxs[i*WINDOW_WIDTH + j]);
            }
        }
    }

    // ��ʾ���������Brick
    Brick* pBrick = m_pTetrisManager->GetBrick();
    bool currentBrick[4][4];
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;  //[0,0]�����Ͻǵĵ�
            if (currentBrick[i][j])
            {
                //ת��������λ������
                m_p4Boxs[num] = new Box(pBrick->GetBrickRow() - 3 + i, pBrick->GetBrickColumn() + j);
                m_scene->addItem(m_p4Boxs[num]);
                num++;
            }
        }
    }
}

void TetrisMainWindow::ClearUiView()
{
    // ��ձ������е�С����
    for (size_t i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; ++i)
    {
        if (m_pBackgroundBoxs[i])
        {
            m_scene->removeItem(m_pBackgroundBoxs[i]);
        }
    }
    // �����������ķ���
    for (size_t i = 0; i < 4; ++i)
    {
        if (m_p4Boxs[i])
        {
            m_scene->removeItem(m_p4Boxs[i]);
        }
    }

}

void TetrisMainWindow::UpdateBackgroundBoxs()
{
    int** pMatrix = m_pTetrisManager->GetBackgroundMatrix();
    for (size_t i = 0; i < WINDOW_HEIGHT; ++i)
    {
        for (size_t j = 0; j < WINDOW_WIDTH; ++j)
        {
            if (pMatrix[i][j] == 1)
            {
                if (!m_pBackgroundBoxs[i*WINDOW_WIDTH + j])
                {
                    m_pBackgroundBoxs[i*WINDOW_WIDTH + j] = new Box(i, j, Qt::blue);
                    m_scene->addItem(m_pBackgroundBoxs[i*WINDOW_WIDTH + j]);
                }
            }
            else if (pMatrix[i][j] == 0)
            {
                if (m_pBackgroundBoxs[i*WINDOW_WIDTH + j])
                {
                    Box* pBox = m_pBackgroundBoxs[i*WINDOW_WIDTH + j];
                    m_scene->removeItem(m_pBackgroundBoxs[i*WINDOW_WIDTH + j]);
                    //delete m_pBackgroundBoxs[i*WINDOW_WIDTH + j]; // �ͷ��ڴ棬��ָ���ÿ�
                    m_pBackgroundBoxs[i*WINDOW_WIDTH + j] = nullptr;
                }
            }
        }
    }
}

void TetrisMainWindow::DisplayMovingBricks()
{
    // ��ʾ���������Brick
    int num = 0;
    Brick* pBrick = m_pTetrisManager->GetBrick();
    bool currentBrick[4][4];
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;  //[0,0]�����Ͻǵĵ�
            if (currentBrick[i][j])
            {
                //ת��������λ������
                m_p4Boxs[num] = new Box(pBrick->GetBrickRow() - 3 + i, pBrick->GetBrickColumn() + j);
                m_scene->addItem(m_p4Boxs[num]);
                num++;
            }
        }
    }
}

void TetrisMainWindow::ChangeUiBoxToBackground(Brick* pBrick)
{

}
