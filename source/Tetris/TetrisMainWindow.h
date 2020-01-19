#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TetrisMainWindow.h"
#include "MacroDefines.h"

class TetrisManager;
class Box;
class Brick;

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
    virtual void keyPressEvent(QKeyEvent* e);

public slots:
    // ����ĸ������Ĳۺ���
    void StartGame();
    void PauseGame();
    void RestartGame();
    void StopGame();
    
    void DisplayUiView();
    void ClearUiView();

public:
    void UpdateUiBoxPosition(EnKeyAction keyAction, Brick* pBrick);    // �¡������ƺ����λ��
    void UpdateRotatedBoxPosition(Brick* pBrick);      // ��ת�����λ��
    void UpdateBackgroundBoxs();    // ���±���

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

    TetrisManager* m_pTetrisManager;
    // �洢������������Ҫ��ʾ��Box�ڵ�   �� pBackgroundBoxs[i*row+j]��־[i,j]λ�ô��Ľڵ�
    Box* m_pBackgroundBoxs[WINDOW_HEIGHT * WINDOW_WIDTH];
    // �洢����������״��4������
    Box* m_p4Boxs[4];
};
