#pragma once

// ���ַ���ͼ�εĻ���
class Brick
{
public:
    Brick();
    ~Brick();

    virtual void Rotate();  //��ʱ����ת
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
    int m_index;    //Ŀǰ��ʾͼ�εĵڼ���״̬����ת�������֣�
    int m_status;   //�洢Ŀǰ��ͼ����Ϣ
    int m_row;      // �кţ�ͼ�����½ǵ�λ��
    int m_column;   // �к�
};

