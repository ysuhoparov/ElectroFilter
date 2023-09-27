#include "diagram.h"
#include "color.h"

Diagram::Diagram(QFrame* frame)
{
    graphicsView = new QGraphicsView(frame);
    graphicsView->resize(gsize, gsize);
    graphicsView->move(gleft, gtop);

    graphicsScene = new QGraphicsScene();
    graphicsView->setScene(graphicsScene);

    axisValues(frame);

    graphU = new int[256];
    graphI = new int[256];
    for(int index = 0; index < 256; index++) {
        graphI[index] = graphU[index] = 0;
    }

    first = next = 0;

}

Diagram::~Diagram()
{
    delete graphU;
    delete graphI;

    delete graphicsView;
    delete graphicsScene;
}


// Отрисовка диаграмм тока и напряжения электрофильтра
void Diagram::refresh(const NetInfo& data)
{
    graphU[next] = data.u < graphMax ? data.u : graphMax-1;  // Новые значения  graphMax = 99;
    graphI[next] = data.i < graphMax ? data.i : graphMax-1;  // -1 на толщину линии
    next++;
    next %= 256;

    // Прорисовка сетки
    graphicsScene->clear();
    QPen pen;
    pen.setColor(Color::GRID);
    pen.setWidth(1);
    for(int j=0; j <8; j++)
        graphicsScene->addLine(j*dt+gd, -dh, j*dt+gd, dh, pen);  //
    for(int j=1; j <10; j++)
        graphicsScene->addLine(1, -dh-1+dm*j, 179,-dh-1+dm*j, pen);

    // Построение графиков
    for(unsigned int j = gd*2; j<dsize-gd; j++ ) {
        pen.setWidth(1);
        pen.setColor(Color::I);
        graphicsScene->addLine((dsize -j), dh-dmi*graphI[(next-j)%256],
                               (dsize -j-1), dh-dmi*graphI[(next-j-1)%256],pen);
        pen.setWidth(2);
        pen.setColor(Color::U);
        graphicsScene->addLine((dsize -j), dmu*graphU[(next-j)%256]-dh,
                               (dsize -j-1), dmu*graphU[(next-j-1)%256]-dh,pen);

    }
}

void Diagram::axisValues(QFrame* frame)
{
    QFont font( "Tahoma", 8);

    diaglbl = new QLabel("-60   50    40    30    20   10 c", frame);
    diaglbl->setFont(font);
    diaglbl->move(glbleft, glbltop);

    du20 = new QLabel("20", frame);
    du20->setFont(font);
    du20->move(duleft, d20top);
    du50 = new QLabel("50", frame);
    du50->setFont(font);
    du50->move(duleft, d50top);
    du80 = new QLabel("80kV", frame);
    du80->setFont(font);
    du80->move(duleft, d80top);

    di80 = new QLabel("80%", frame);
    di80->setFont(font);
    di80->move(dileft-10, d20top);
    di50 = new QLabel("50", frame);
    di50->setFont(font);
    di50->move(dileft, d50top);
    di20 = new QLabel("20", frame);
    di20->setFont(font);
    di20->move(dileft, d80top);
}
