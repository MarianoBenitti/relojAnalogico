#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    pen.setColor(Qt::cyan);
    pen.setWidth(3);
    brush.setColor(Qt::darkGray);

    brush.setStyle(Qt::SolidPattern);
    brush.gradient();
    QpainterReloj.setPen(pen);
    QpainterReloj.setBrush(brush);
    QpainterReloj.drawEllipse(10,10,480,480);

    QpaintReloj->update();

}
