#ifndef COLOR_H
#define COLOR_H

#include <QString>

class Color
{
    friend class Diagram;

    static const int I = 0x20C0A0;
    static const int U = 0x9098f0;
    static const int GRID = 0xe0e0e0;

public:

    static QString getI()
    {
        return "QProgressBar::chunk{background-color: #20C0A0; width: 1px;}";
    }

    static QString getU()
    {
        return "QProgressBar::chunk{background-color: #9098f0; width: 1px;}";
    }

};


#endif // COLOR_H
