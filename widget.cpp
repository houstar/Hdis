#include "widget.h"
#include "ui_widget.h"
#include <QThread>
#include "capture/captureVgaThread.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(1024,768);
    ui->label->setGeometry(0,0,1024,768);

    connect(&m_captureVgaThread, SIGNAL(captureVgaImage(QImage)), this, SLOT(updateVGAScreen(QImage)));
    m_captureVgaThread.start();
}

Widget::~Widget()
{
    //membuf->close();
    if(ui)
    {
        delete ui;
        ui = NULL;
    }
}

void Widget::updateVGAScreen(const QImage &image)
{
    ui->label->setPixmap(QPixmap::fromImage(image,Qt::AutoColor));

    update();
}
