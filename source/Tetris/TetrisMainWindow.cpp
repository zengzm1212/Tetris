#include "TetrisMainWindow.h"
#include <QGraphicsLineItem>

#include "Box.h"

TetrisMainWindow::TetrisMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    ui = new Ui::TetrisMainWindowClass();
	ui->setupUi(this);

    initGraphicsViewWidget();

    // 绑定界面的按键
    connect(ui->m_startButton, SIGNAL(clicked()), this, SLOT(StartGame()));
    connect(ui->m_pauseButton, SIGNAL(clicked()), this, SLOT(PauseGame()));
    connect(ui->m_restartButton, SIGNAL(clicked()), this, SLOT(RestartGame()));
    connect(ui->m_overButton, SIGNAL(clicked()), this, SLOT(StopGame()));
}

TetrisMainWindow::~TetrisMainWindow()
{
    delete ui;
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

    Box* b = new Box();
    b->setPos(10, 10);
    m_scene->addItem(b);
}

void TetrisMainWindow::StartGame()
{

}
void TetrisMainWindow::PauseGame()
{

}
void TetrisMainWindow::RestartGame()
{

}
void TetrisMainWindow::StopGame()
{

}