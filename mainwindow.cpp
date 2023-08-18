#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTime"
#include <QDateTime>
//paleta de colores
#define GRISBASE 0x3C414F
#define CELESTEBASE 0x05B2A3



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QpaintReloj = new QPaintBox(0,0,ui->widget);//instancio la pantalla de dibujo con el tamaño original del widget
    TimerGen = new QTimer(this);

    connect(TimerGen, &QTimer::timeout,this,&MainWindow::TimerGen1);
    TimerGen->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimerGen1(){

    QPainter QpainterReloj(QpaintReloj->getCanvas());
    QFont fuente("EuroRoman",20);
    fuente.setUnderline(1);
    fuente.setBold(1);
    //para medir el tiempo
    QTime tiempo;
    QDateTime fecha;
    float angulo;//angulo de la aguja
    QPen pen;
    QBrush brush;
    QPoint trapecio[4];//trapecio horas
    trapecio[0].setX(-50);
    trapecio[0].setY(-225);
    trapecio[1].setX(50);
    trapecio[1].setY(-225);
    trapecio[2].setX(30);
    trapecio[2].setY(-180);
    trapecio[3].setX(-30);
    trapecio[3].setY(-180);
    QPoint centro;//centro de las horas
    centro.setX(0);
    centro.setY(-200);

    int i;

    //se dibuja el circulo central del reloj
        //se prepara la pen
    pen.setColor(QColor(163, 90, 213));
    pen.setWidth(4);
        //se prepara el brush
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(30, 43, 109));
        //se prepara el painter
    QpainterReloj.setPen(pen);
    QpainterReloj.setBrush(brush);
    QpainterReloj.drawEllipse(10,10,480,480);
    //dibujamos los circulos donde se encontraran las horas

    QpainterReloj.translate(250,250);//trasladamos el origen de coordenadas al centro
    pen.setJoinStyle(Qt::RoundJoin);
    QpainterReloj.setFont(fuente);//seteamos la fuente para el reloj
    QpainterReloj.save();
    for(i=1;i<=12;i++){
        QpainterReloj.rotate(30);
        pen.setColor(QColor(0, 158, 255 ));//cambiamos el color para los trapecios y circulos pequeños
        QpainterReloj.setPen(pen);
        if(i%3){
            brush.setColor(QColor(0, 158, 150 ));//cambiamos el color de relleno de los circulos
            QpainterReloj.setBrush(brush);
            QpainterReloj.drawEllipse(centro,28,28);
            pen.setColor(QColor(0,0,101));//cambiamos el color para los numeros
            QpainterReloj.setPen(pen);
            QpainterReloj.drawText(-14,-220,28,28,Qt::AlignCenter,QString::number(i,10),nullptr);

        }else{
            brush.setColor(QColor(225, 206, 226));//cambiamos el color de relleno de los trapecios
            QpainterReloj.setBrush(brush);
            QpainterReloj.drawPolygon(trapecio,4);
            pen.setColor(QColor(0,0,101));//cambiamos el color para los numeros
            QpainterReloj.setPen(pen);
            QpainterReloj.drawText(-14,-220,28,28,Qt::AlignCenter,QString::number(i,10),nullptr);
        }
    }

    //TOMAMOS EL TIEMPO
    tiempo=QTime::currentTime();
    fecha=QDateTime::currentDateTime();
    //imprimimos la Fecha
    QpainterReloj.restore();
    QpainterReloj.save();
    //dibujamos el rectangulo de la fecha
    brush.setColor(Qt::black);
    QpainterReloj.setBrush(brush);
    QpainterReloj.drawRect(-100,50,200,50);
    //escribimos la fecha
    fuente=QFont("Digital-7");
    fuente.setPointSize(30);
    QpainterReloj.setFont(fuente);
    QpainterReloj.drawText(-100,50,200,50,Qt::AlignCenter,fecha.toString("dd/MM/yyyy"));


    QpainterReloj.restore();
    QpainterReloj.save();
    //armamos el horero
    if(tiempo.hour()<=12){
        angulo=tiempo.hour()*30+tiempo.minute()/20*10;
    }else{
        angulo=(tiempo.hour()-12)*30+tiempo.minute()/20*10;
    }
    QpainterReloj.rotate(angulo);
    //dibujamos la aguja de las horas
    QpainterReloj.drawLine(0,0,0,-50);

    QpainterReloj.restore();
    QpainterReloj.save();
    //armamos el minutero

    if(tiempo.msec()>=900 && tiempo.second()==59){
        TimerGen->start(5);
        angulo=tiempo.minute()*6+(tiempo.msec()-900)/20*1.2;
    }else{
        angulo=tiempo.minute()*6;
        TimerGen->start(50);
    }
    QpainterReloj.rotate(angulo);
    //dibujamos la aguja de los minutos
    QpainterReloj.drawLine(0,0,0,-75);

    QpainterReloj.restore();
    QpainterReloj.save();
    //armamos el segundero

    //calculamos el angulo de los segundos
    angulo=(tiempo.second()*6+tiempo.msec()/100*0.6);
    QpainterReloj.rotate(angulo);
    //dibujamos la aguja de los segundos
    QpainterReloj.drawLine(0,0,0,-100);




    QpaintReloj->update();   
}
