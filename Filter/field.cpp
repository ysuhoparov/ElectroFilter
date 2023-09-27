#include "field.h"
#include "color.h"

Field::Field(QWidget *parent, int numberField, int zones) : QMainWindow(parent)
{
    number = numberField;

    frame = new QFrame(parent);
    frame->setFrameShape(QFrame::Panel);   
    frame->resize(width,height);
    if(zones > 4) left -= 100;
    frame->move(left + next*number, top);

    diagram = new Diagram(frame);

    QFont font( "Tahoma", 12);

    indicatorU = new QProgressBar(frame);
        indicatorU->setGeometry(QRect(QPoint(pleft, putop), QSize(pwidth, pheight)));
        indicatorU->setTextVisible(false);
        indicatorU->setStyleSheet(Color::getU());

    valueU = new QLabel(" U = 001 kV", frame);
        valueU->setFont(font);
        valueU->move(uleft, utop);

    indicatorI = new QProgressBar(frame);
        indicatorI->setGeometry(QRect(QPoint(pleft, pitop), QSize(pwidth, pheight)));
        indicatorI->setTextVisible(false);
        indicatorI->setStyleSheet(Color::getI());

    valueI = new QLabel(" I = 0000 mA", frame);
        valueI->setFont(font);
        valueI->move(uleft, itop);

    mode = new QLabel("Авто          ", frame);
        mode->setFont(font);
        mode->move(mleft, mtop);


    start = new QPushButton("Пуск",frame);
        start->setGeometry(QRect(QPoint(sleft,sttop), QSize(swidth, sheight)));
        start->setFont(font);

    stop = new QPushButton("Стоп",frame);
        stop->setGeometry(QRect(QPoint(sleft,sptop), QSize(swidth, sheight)));
        stop->setFont(font);

    shaking = new QLabel("Встряхивание",frame);
        shaking->setFont(font);
        shaking->move(shleft,shtop);

    vibrator = new QLabel("~~~~",parent);
        font.setPointSize(20);
        vibrator->setFont(font);
        vibrator->move(left + vleft + next*number, top + vtop);

    connect(start, &QPushButton::released, this, &Field::on_start_clicked);
    connect(stop, &QPushButton::released, this, &Field::on_stop_clicked);

}

Field::~Field()
{
    delete valueI;
    delete valueU;
    delete indicatorI;
    delete indicatorU;
    delete mode;
    delete start;
    delete stop;
    delete shaking;
    delete vibrator;

    delete frame;
}

void Field::refresh(const NetInfo& newdata)
{
    data = newdata;
    indicatorU->setValue(data.u);
    valueU->setText("U" + QString::number(number+1) +" = " + QString::number(data.u) + "kV");

    indicatorI->setValue(data.i);
    valueI->setText("I" + QString::number(number+1) +" = " + QString::number(data.i*power) + "mA");


    if(data.flags & 0x80) {
        mode->setText("Стоп");
    } else {
        mode->setText(fieldMode[data.flags & 1]);
    }

    if(data.shake){
        shaking->setText("Встряхивание");
        vibrator->setText("~~~~");
    }
    else {
        shaking->setText("");
        vibrator->setText("");
    }

   diagram->refresh(data);
}


void Field::setPower(float power)
{
    this->power = power/100;
}

void Field::on_start_clicked()
{
    //Channel::status |= 1 << number;
    Channel::queueCommand.enqueue(number << 4 | powerOn);
    mode->setText(QString::number(number<<4 | powerOn) );
}

void Field::on_stop_clicked()
{
    //Channel::status &= 0xf ^ 1 << number;
    Channel::queueCommand.enqueue(number << 4 | powerOff);
    mode->setText(QString::number(number << 4 | powerOff) );
}


