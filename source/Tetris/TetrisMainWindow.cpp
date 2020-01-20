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

    //使得方块组支持键盘操作
    //setFlags(QGraphicsItem::ItemIsFocusable);
    setFocus();
    //setFocusPolicy();

    // 初始化成员变量
    

    // 绑定界面的按键
    connect(ui->m_startButton, SIGNAL(clicked()), this, SLOT(StartGame()));
    connect(ui->m_pauseButton, SIGNAL(clicked()), this, SLOT(PauseGame()));
    connect(ui->m_restartButton, SIGNAL(clicked()), this, SLOT(RestartGame()));
    connect(ui->m_overButton, SIGNAL(clicked()), this, SLOT(StopGame()));

    // 绑定按键的信号传递
    connect(m_pTetrisManager, &TetrisManager::UpdateBoxPosition, this, &TetrisMainWindow::UpdateUiBoxPosition);
    connect(m_pTetrisManager, &TetrisManager::ChangeBrickToBackground, this, &TetrisMainWindow::ChangeUiBoxToBackground);
    connect(m_pTetrisManager, &TetrisManager::UpdateBackground, this, &TetrisMainWindow::UpdateBackgroundBoxs);
}

TetrisMainWindow::~TetrisMainWindow()
{
    delete ui;     //Qt中释放内存只需释放根节点即可

    if (m_pTetrisManager)
        delete m_pTetrisManager;
}

void TetrisMainWindow::keyPressEvent(QKeyEvent* e)
{
    m_pTetrisManager->ReactKeyEvent(e);
}

void TetrisMainWindow::initGraphicsViewWidget()
{
    //使用抗锯齿渲染
    ui->m_graphicsView->setRenderHint(QPainter::Antialiasing);
    //设置缓冲背景，加速渲染
    ui->m_graphicsView->setCacheMode(QGraphicsView::CacheBackground);

    m_scene = new QGraphicsScene(this);       // QGraphicsScene为场景，QGraphicsView为视口 这两个都是针对二维视图而言
    m_scene->setSceneRect(30, 30, 310, 410);  // 为什么这个场景的纵向比四条边界线要小
    ui->m_graphicsView->setScene(m_scene);

    //方块可移动的四条线
    //向外扩展3像素，这样可以使方块组到达边界的时候再移动就会发生碰撞
    // 显示的视口范围是graphicView的范围，在setui中已经设置好了
    m_topLine = m_scene->addLine(32, 32, 238, 32); //相当于横向35-235，纵向35-435   
    m_leftLine = m_scene->addLine(32, 32, 32, 438);
    m_buttomLine = m_scene->addLine(32, 438, 238, 438);
    m_rightLine = m_scene->addLine(238, 32, 238, 438);
    // 设置四条线的颜色
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

    // 显示层所做的事情就是将DB层的数据显示出来
    for (size_t i = 0; i < 4; ++i)
    {
        m_scene->removeItem(m_p4Boxs[i]);
        delete m_p4Boxs[i]; //释放内存
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
    // 显示背景
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

    // 显示正在下落的Brick
    Brick* pBrick = m_pTetrisManager->GetBrick();
    bool currentBrick[4][4];
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;  //[0,0]是左上角的点
            if (currentBrick[i][j])
            {
                //转化成整体位置坐标
                m_p4Boxs[num] = new Box(pBrick->GetBrickRow() - 3 + i, pBrick->GetBrickColumn() + j);
                m_scene->addItem(m_p4Boxs[num]);
                num++;
            }
        }
    }
}

void TetrisMainWindow::ClearUiView()
{
    // 清空背景所有的小方块
    for (size_t i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; ++i)
    {
        if (m_pBackgroundBoxs[i])
        {
            m_scene->removeItem(m_pBackgroundBoxs[i]);
        }
    }
    // 清空正在下落的方块
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
                    //delete m_pBackgroundBoxs[i*WINDOW_WIDTH + j]; // 释放内存，将指针置空
                    m_pBackgroundBoxs[i*WINDOW_WIDTH + j] = nullptr;
                }
            }
        }
    }
}

void TetrisMainWindow::DisplayMovingBricks()
{
    // 显示正在下落的Brick
    int num = 0;
    Brick* pBrick = m_pTetrisManager->GetBrick();
    bool currentBrick[4][4];
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;  //[0,0]是左上角的点
            if (currentBrick[i][j])
            {
                //转化成整体位置坐标
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
