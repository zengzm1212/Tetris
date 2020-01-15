#include "TetrisMainWindow.h"
#include <QGraphicsLineItem>

#include "Box.h"

TetrisMainWindow::TetrisMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    ui = new Ui::TetrisMainWindowClass();
	ui->setupUi(this);

    initGraphicsViewWidget();

    // �󶨽���İ���
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