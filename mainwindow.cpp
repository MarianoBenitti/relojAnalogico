#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    TimerGen->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimerGen1(){

    QPainter QpainterReloj(QpaintReloj->getCanvas());
    QPen pen;
    QBrush brush;
    QPoint trapecio[4];
    trapecio[0].setX(-50);
    trapecio[0].setY(-225);
    trapecio[1].setX(50);
    trapecio[1].setY(-225);
    trapecio[2].setX(30);
    trapecio[2].setY(-180);
    trapecio[3].setX(-30);
    trapecio[3].setY(-180);


    QPoint centro;
    centro.setX(0);
    centro.setY(-200);
    int i;
    //se dibuja el circulo central del reloj
    pen.setColor(CELESTEBASE);
    pen.setWidth(7);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    brush.setColor(GRISBASE);
    QpainterReloj.setPen(pen);
    QpainterReloj.setBrush(brush);
    QpainterReloj.drawEllipse(10,10,480,480);
    //dibujamos los circulos donde se encontraran las horas
    QpainterReloj.translate(250,250);
    brush.setColor(Qt::darkMagenta);
    brush.setStyle(Qt::Dense3Pattern);
    for(i=1;i<=12;i++){
        QpainterReloj.rotate(30);
        if(i%3){
            QpainterReloj.setBrush(Qt::NoBrush);
            QpainterReloj.drawEllipse(centro,28,28);
        }else{
            QpainterReloj.setBrush(brush);
            QpainterReloj.drawPolygon(trapecio,4);
        }
    }

    QpaintReloj->update();   
}
