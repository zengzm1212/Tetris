#pragma once

class Matrix2d
{
public:
    Matrix2d(int r, int c);

    Matrix2d(const Matrix2d& other);

    virtual ~Matrix2d();

    Matrix2d& operator=(const Matrix2d& other);

    int* operator[](int r);

    const int* operator[](int r) const;

public:
    const int GetRowNum() const { return m_row; }
    const int GetColumnNum() const { return m_column; }

private:
    int m_row;
    int m_column;
    int* m_pData;
};
