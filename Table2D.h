#ifndef TABLE2D_H
#define TABLE2D_H
#include <QtCore>

template <class ContentType>
class Table2D
{
public:
    Table2D(uint x, uint y)
        : x_(x)
    {
        table_ = new ContentType*[x];
        for(uint i = 0; i < x; ++i)
            table_[i] = new ContentType[y];
    }
    ~Table2D()
    {
        for(uint i = 0; i < x_; ++i)
            delete[] table_[i];
        delete[] table_;
    }

    ContentType*& operator[](uint x)
    {
        return table_[x];
    }

private:
    ContentType** table_;
    uint x_;
};

#endif // TABLE2D_H
