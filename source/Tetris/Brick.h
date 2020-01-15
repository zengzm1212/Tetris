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

protected:
    virtual void UpdateStatus() = 0;

private:
    int m_status; //存储目前的图像信息
    int m_index;  //目前表示图形的第几种状态（旋转会有四种）
};

