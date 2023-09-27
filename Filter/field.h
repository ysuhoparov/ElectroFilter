
#ifndef FIELD_H
#define FIELD_H

#include "channel.h"
#include "diagram.h"

#include <QMainWindow>

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>

class Field : public QMainWindow
{
    Q_OBJECT
    // объявление дружественного класса
   friend class Model;
public:
    explicit Field(QWidget *parent, int numberField=0, int zones =4);
    ~Field();

    void refresh(const NetInfo& data);
    void setPower(float);
    QFrame* frame;
    NetInfo data;

public slots:
    void on_start_clicked();
    void on_stop_clicked();

private:
    int number;
    float power;
    Diagram* diagram;

    QProgressBar* indicatorU,* indicatorI;
    QLabel* valueI, *valueU, *mode, *shaking, *vibrator;
    QPushButton *start, *stop;

    const char powerOn = 1;
    const char powerOff = 2;
    const char* fieldMode[2]{"Авто", "Искра"};


//sizes
    int width = 192;        // Ширина панели поля фильтра
    int height = 440;       // Высота -//-
    int left = 250;         // Левый край панели поля фильтра
    int next = width + 3;   // Шаг для следующей панели
    int top = 60;           // верх панели поля фильтра

    int pleft = 32;         // Левый край линейного индикатора
    int pwidth = 128;       // Длина линейного индикатора
    int pheight = 8;        // Ширина линейного индикатора
    int putop = 220;        // Верх линейного индикатора U
    int pitop = 260;        // Верх линейного индикатора I
    int uleft = 60;         // координата X вывода значения U, I
    int utop = 232;         // координата Y вывода значения U
    int itop = 272;         // координата Y вывода значения I

    int mleft = 70;         // координаты вывода режима
    int mtop = 300;

    int sleft = 58;         // координаты и размеры кнопок Пуск, Стоп
    int sttop = 340;
    int swidth = 80;
    int sheight = 28;
    int sptop = 369;

    int shleft = 40;        // координаты вывода состояния регенерации
    int shtop = 410;
    int vleft = 50;         // координаты вывода состояния вибраторов бункеров
    int vtop = 460;

};

#endif // FIELD_H
