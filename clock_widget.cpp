#include <clock_widget.h>

#include <QPainter>
#include <QTime>
#include <iostream>

Clock::Clock(QWidget *parent)
    : QWidget(parent)
    , _hours(0)
    , _minutes(0)
    , _seconds(0)
{
    setMinimumSize(100,100);
    startTimer(1000);
}

void Clock::timerEvent(QTimerEvent *)
{
    QTime t  = QTime::currentTime();
    _hours   = t.hour();
    _minutes = t.minute();
    _seconds = t.second();

    update();
    std::cout << "Tick: "
              << _hours
              << ":" << _minutes
              << ":" << _seconds
              << std::endl;
}


void drawArrow(QPainter &p)
{
    p.drawLine(0,0,  0,10);
}

void Clock::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPoint center(width()/2, height()/2);
    p.translate(center);


    //circle
    p.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    p.drawEllipse(-200, -200, 400, 400);
    for (int i = 0; i < 360; i+=6)
    {
        p.save();
        p.rotate(i);
        if (i % 5 == 0)
        {
            p.scale(2,1);
            p.drawLine(0,-200, 0, -185);
        }
        else
        {
            p.drawLine(0, -200, 0, -190);
        }
        p.restore();
    }

    //text clock
    QFont font("Times", 32, QFont::Bold);
    p.setFont(font);
    p.drawText(-70, 100, QString::number(_hours) +  ":" + QString::number(_minutes)+ ":" + QString::number(_seconds));

    //numbers
    p.drawText(150,  10,   "3");
    p.drawText(-10,  170, "6");
    p.drawText(-170, 10,   "9");
    p.drawText(-20,  -150, "12");

    // seconds
    p.save();
    p.rotate( 180 + _seconds * 6);
    p.scale(20,20);
    p.setPen(QPen(Qt::red,0.2,Qt::SolidLine,Qt::RoundCap));
    drawArrow(p);
    p.restore();

    // hours
    p.save();
    p.rotate( 180 + _minutes * 6);
    p.scale(7,7);
    p.setPen(QPen(Qt::black,1.3,Qt::SolidLine,Qt::RoundCap));
    drawArrow(p);
    p.restore();

    // minutes
    p.save();
    p.rotate( 180 + _hours * 30);
    p.scale(16,16);
    p.setPen(QPen(Qt::black,0.4,Qt::SolidLine,Qt::RoundCap));
    drawArrow(p);
    p.restore();
}

