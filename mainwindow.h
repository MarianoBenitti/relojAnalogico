#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <qpaintbox.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void TimerGen1();//metodo enlazado con el timer
    void qPaintBoxMouseDoubleClick(QMouseEvent *event);


private:
    Ui::MainWindow *ui;

    void mouseDoubleClick(QMouseEvent *event);

    QPaintBox *QpaintReloj; //pantalla dibujo del rejol
    QTimer *TimerGen; //Timer general
};
#endif // MAINWINDOW_H
