#pragma once

// 各种方块图形的基类
class Brick
{
public:
    Brick();
    ~Brick();

    virtual void Rotate();  //逆时针旋转
    Brick & operator=(Brick &);

    virtual int GetStatus() { return m_status; }
    virtual void SetStatus(int status) { m_status = status; }
    virtual int GetIndex() { return m_index; }
    virtual void SetIndex(int index) { m_index = index; }
    virtual int GetBrickRow() { return m_row; }
    virtual void SetBrickRow(int row) { m_row = row; }
    virtual int GetBrickColumn() { return m_column; }
    virtual void SetBrickColumn(int column) { m_column = column; }

protected:
    virtual void UpdateStatus() = 0;

private:
    int m_index;    //目前表示图形的第几种状态（旋转会有四种）
    int m_status;   //存储目前的图像信息
    int m_row;      // 行号，图形左下角的位置
    int m_column;   // 列号
    bool m_isFrozen;// 是否处于冻结状态(冻结后便不可再移动)
};

