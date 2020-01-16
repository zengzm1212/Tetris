#include "TetrisMainWindow.h"
#include "Box.h"
#include "Brick.h"
#include "TetrisManager.h"
#include <QGraphicsLineItem>

TetrisMainWindow::TetrisMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    ui = new Ui::TetrisMainWindowClass();
	ui->setupUi(this);

    m_pTetrisManager = new TetrisManager;

    initGraphicsViewWidget();
    DisplayUiView();

    // 绑定界面的按键
    connect(ui->m_startButton, SIGNAL(clicked()), this, SLOT(StartGame()));
    connect(ui->m_pauseButton, SIGNAL(clicked()), this, SLOT(PauseGame()));
    connect(ui->m_restartButton, SIGNAL(clicked()), this, SLOT(RestartGame()));
    connect(ui->m_overButton, SIGNAL(clicked()), this, SLOT(StopGame()));

    // 绑定与Mgr的信号传递
    connect(m_pTetrisManager, SIGNAL(UpdateBoxPosition(EnKeyAction)), this, SLOT(UpdateUiBoxPosition(EnKeyAction)));
}

TetrisMainWindow::~TetrisMainWindow()
{
    delete ui;     //Qt中释放内存只需释放根节点即可

    if (m_pTetrisManager)
        delete m_pTetrisManager;
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

void TetrisMainWindow::UpdateUiBoxPosition(EnKeyAction keyAction)
{
    for (size_t i = 0; i < 4; ++i)
    {
        if(keyAction == EnKeyAction::DOWN)
            m_p4Boxs[i]->moveBy(0, 20);
        else if(keyAction == EnKeyAction::LEFT)
            m_p4Boxs[i]->moveBy(-20, 0);
        else if(keyAction == EnKeyAction::RIGHT)
            m_p4Boxs[i]->moveBy(0, 20);
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
                Box* pBox = new Box(i, j);
                m_scene->addItem(pBox);
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
            currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            if (currentBrick[i][j])
            {
                //转化成整体位置坐标
                m_p4Boxs[num] = new Box(pBrick->GetBrickRow() + i, pBrick->GetBrickColumn() + j);
                m_scene->addItem(m_p4Boxs[num]);
                num++;
            }
        }
    }
}

void TetrisMainWindow::ClearUiView()
{
    //清空视图中所有的小方块
    foreach(QGraphicsItem *pItem, m_scene->items(34, 34, 236, 436, Qt::ContainsItemShape, Qt::AscendingOrder)) {
        // 先从场景中移除小方块，因为使用deleteLater()是在返回主事件循环后才销毁
        // 小方块的，为了在出现新的方块组时不发生碰撞，所以需要先从场景中移除小方块
        m_scene->removeItem(pItem);
        //Box *pBox = (Box*) pItem;
        //pBox->deleteLater();
    }

}

