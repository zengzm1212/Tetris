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

    // �󶨽���İ���
    connect(ui->m_startButton, SIGNAL(clicked()), this, SLOT(StartGame()));
    connect(ui->m_pauseButton, SIGNAL(clicked()), this, SLOT(PauseGame()));
    connect(ui->m_restartButton, SIGNAL(clicked()), this, SLOT(RestartGame()));
    connect(ui->m_overButton, SIGNAL(clicked()), this, SLOT(StopGame()));

    // ����Mgr���źŴ���
    connect(m_pTetrisManager, SIGNAL(UpdateBoxPosition(EnKeyAction)), this, SLOT(UpdateUiBoxPosition(EnKeyAction)));
}

TetrisMainWindow::~TetrisMainWindow()
{
    delete ui;     //Qt���ͷ��ڴ�ֻ���ͷŸ��ڵ㼴��

    if (m_pTetrisManager)
        delete m_pTetrisManager;
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
    // ��ʾ����
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

    // ��ʾ���������Brick
    Brick* pBrick = m_pTetrisManager->GetBrick();
    bool currentBrick[4][4];
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            if (currentBrick[i][j])
            {
                //ת��������λ������
                m_p4Boxs[num] = new Box(pBrick->GetBrickRow() + i, pBrick->GetBrickColumn() + j);
                m_scene->addItem(m_p4Boxs[num]);
                num++;
            }
        }
    }
}

void TetrisMainWindow::ClearUiView()
{
    //�����ͼ�����е�С����
    foreach(QGraphicsItem *pItem, m_scene->items(34, 34, 236, 436, Qt::ContainsItemShape, Qt::AscendingOrder)) {
        // �ȴӳ������Ƴ�С���飬��Ϊʹ��deleteLater()���ڷ������¼�ѭ���������
        // С����ģ�Ϊ���ڳ����µķ�����ʱ��������ײ��������Ҫ�ȴӳ������Ƴ�С����
        m_scene->removeItem(pItem);
        //Box *pBox = (Box*) pItem;
        //pBox->deleteLater();
    }

}

