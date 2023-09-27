#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "netinfo.h"


#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QGraphicsView>
#include <QGraphicsScene>

// Отрисовка диаграмм тока и напряжения электрофильтра
class Diagram
{   

public:
    Diagram(QFrame* frame);
    ~Diagram();

    void refresh(const NetInfo &);
    void axisValues(QFrame* frame);


private:
    QGraphicsView* graphicsView;
    QGraphicsScene* graphicsScene;
    QLabel* diaglbl, *du20, *du50, *du80, *di20, *di50, *di80; // Оцифровка диаграмм;
    int* graphU, * graphI;
    unsigned int first, next; // точки диаграмм

    const unsigned char graphMax = 99;


    int gsize = 182;        // размеры области диаграмм
    int gleft = 5;          // отступы области диаграмм
    int gtop = 4;
    int glbleft = 24;       // Левый край подписи оси времени диаграмм
    int glbltop = 186;      // положение от верха подписи оси времени диаграмм
    int gd = 2;             // отступы графика по горизонтали

    int duleft = 4;         // отступы графика по горизонтали
    int dileft = 172;       // отступы графика по горизонтали
    int d20top = 32;
    int d50top = 86;
    int d80top = 140;

    unsigned int dsize = gsize-2; // 180;  // количество точек диаграммы, -1 border
    int dh = 89;   // смещение графика по высоте
    int dm = 18;   // масштаб Y - 1 клетка (10 ед.) = 18 точек экрана  (вся диаграмма - 180 точек)
    int dt = 25;   // масштаб X - 1 клетка (10 c) = 25 точек экрана  (вся диаграмма - 175 точек)
    float dmu = 1.8;   // к-т масштабирования напряжения,  0-100кV
    float dmi = 1.8;   // к-т масштабирования тока,  диапазон 0-100%


};

#endif // DIAGRAM_H
