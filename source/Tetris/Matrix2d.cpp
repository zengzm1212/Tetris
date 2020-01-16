#include "Matrix2d.h"


Matrix2d::Matrix2d(int r, int c) : m_row(r), m_column(c)
{
    m_pData = new int[m_row * m_column];
}

Matrix2d::Matrix2d(const Matrix2d& other)
{
    m_row = other.m_row;
    m_column = other.m_column;
}

Matrix2d::~Matrix2d()
{
    delete[] m_pData;
}

Matrix2d& Matrix2d::operator=(const Matrix2d& other)
{
    Matrix2d res(other.GetRowNum(), other.GetColumnNum());
    m_row = other.m_row;
    m_column = other.m_column;
    return res;
}

int* Matrix2d::operator[](int r)
{
    return &m_pData[r * m_column];
}

const int* Matrix2d::operator[](int r) const
{
    return &m_pData[r * m_column];
}
