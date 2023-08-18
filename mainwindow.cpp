#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTime"
#include <QDateTime>
//paleta de colores
#define GRISBASE 0x3C414F
#define CELESTEBASE 0x05B2A3



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent,Qt::FramelessWindowHint)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
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
    QPoint agujaS[9];//aguja segundero
    agujaS[0].setX(-5);
    agujaS[0].setY(50);
    agujaS[1].setX(-5);
    agujaS[1].setY(-105);
    agujaS[2].setX(-2);
    agujaS[2].setY(-110);
    agujaS[3].setX(-2);
    agujaS[3].setY(-160);
    agujaS[4].setX(0);
    agujaS[4].setY(-170);
    agujaS[5].setX(2);
    agujaS[5].setY(-160);
    agujaS[6].setX(2);
    agujaS[6].setY(-110);
    agujaS[7].setX(5);
    agujaS[7].setY(-105);
    agujaS[8].setX(5);
    agujaS[8].setY(50);
    QPoint agujaM[9];//aguja minutero
    agujaM[0].setX(-10);
    agujaM[0].setY(30);
    agujaM[1].setX(-10);
    agujaM[1].setY(-75);
    agujaM[2].setX(-5);
    agujaM[2].setY(-80);
    agujaM[3].setX(-5);
    agujaM[3].setY(-110);
    agujaM[4].setX(0);
    agujaM[4].setY(-120);
    agujaM[5].setX(5);
    agujaM[5].setY(-110);
    agujaM[6].setX(5);
    agujaM[6].setY(-80);
    agujaM[7].setX(10);
    agujaM[7].setY(-75);
    agujaM[8].setX(10);
    agujaM[8].setY(30);
    QPoint agujaH[9];//aguja horero
    agujaH[0].setX(-10);
    agujaH[0].setY(20);
    agujaH[1].setX(-10);
    agujaH[1].setY(-45);
    agujaH[2].setX(-5);
    agujaH[2].setY(-50);
    agujaH[3].setX(-5);
    agujaH[3].setY(-70);
    agujaH[4].setX(0);
    agujaH[4].setY(-80);
    agujaH[5].setX(5);
    agujaH[5].setY(-70);
    agujaH[6].setX(5);
    agujaH[6].setY(-50);
    agujaH[7].setX(10);
    agujaH[7].setY(-45);
    agujaH[8].setX(10);
    agujaH[8].setY(20);
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
            brush.setColor(Qt::white);//cambiamos el color de relleno de los circulos
            QpainterReloj.setBrush(brush);
            QpainterReloj.drawEllipse(centro,28,28);
            pen.setColor(Qt::black);//cambiamos el color para los numeros
            QpainterReloj.setPen(pen);
            QpainterReloj.drawText(-14,-215,28,28,Qt::AlignCenter,QString::number(i,10),nullptr);

        }else{
            brush.setColor(Qt::black);//cambiamos el color de relleno de los trapecios
            QpainterReloj.setBrush(brush);
            QpainterReloj.drawPolygon(trapecio,4);
            pen.setColor(QColor(225, 206, 226));//cambiamos el color para los numeros
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
    //cambiamos los colores para las agujas antes de guardar
    brush.setColor(QColor(0,0,101));
    pen.setColor(QColor(0, 158, 150));
    pen.setWidth(2);
    QpainterReloj.setBrush(brush);
    QpainterReloj.setPen(pen);
    QpainterReloj.save();
    //armamos el horero
    if(tiempo.hour()<=12){
        angulo=tiempo.hour()*30+tiempo.minute()/20*10;
    }else{
        angulo=(tiempo.hour()-12)*30+tiempo.minute()/20*10;
    }
    QpainterReloj.rotate(angulo);

    //dibujamos la aguja de las horas
    QpainterReloj.drawPolygon(agujaH,9);
    QpainterReloj.restore();
    QpainterReloj.save();
    //armamos el minutero

    if(tiempo.msec()>=900 && tiempo.second()==59){
        TimerGen->start(10);
        angulo=tiempo.minute()*6+(tiempo.msec()-900)/20*1.2;
    }else{
        angulo=tiempo.minute()*6;
        TimerGen->start(50);
    }
    QpainterReloj.rotate(angulo);
    //dibujamos la aguja de los minutos
    QpainterReloj.drawPolygon(agujaM,9);

    QpainterReloj.restore();
    QpainterReloj.save();
    //armamos el segundero

    //calculamos el angulo de los segundos
    angulo=(tiempo.second()*6+tiempo.msec()/100*0.6);
    QpainterReloj.rotate(angulo);
    //dibujamos la aguja de los segundos

    QpainterReloj.drawPolygon(agujaS,9);
    QpainterReloj.drawEllipse(QPoint(0,0),20,20);


    QpaintReloj->update();   
}
