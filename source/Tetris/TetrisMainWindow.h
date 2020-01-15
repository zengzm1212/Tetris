#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TetrisMainWindow.h"

class TetrisMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	TetrisMainWindow(QWidget *parent = Q_NULLPTR);
    ~TetrisMainWindow();

    void initGraphicsViewWidget();

    //void CreateBox();

protected:
    // handle key press event
    //virtual void keyPressEvent(QKeyEvent* e);

public slots:
    // ����ĸ������Ĳۺ���
    void StartGame();
    void PauseGame();
    void RestartGame();
    void StopGame();

private:
	Ui::TetrisMainWindowClass* ui;
    // ��¼��Ϸ״̬
    bool m_isGamePause;
    bool m_isGameOver;
    // ������ʾ�ĳ���
    QGraphicsScene* m_scene;
    // �����߽���
    QGraphicsLineItem* m_topLine;
    QGraphicsLineItem* m_leftLine;
    QGraphicsLineItem* m_buttomLine;
    QGraphicsLineItem* m_rightLine;
};
