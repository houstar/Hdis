#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include "capture/captureVgaThread.h"

/*包含C库文件*/
extern "C"{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
	#include <sys/time.h>
}



namespace Ui {
class Widget;
}

class Widget : public QWidget/*,public ICaptureVGAListener*/
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    captureVgaThread m_captureVgaThread;

    Ui::Widget *ui;

private slots:
    void updateVGAScreen(const QImage &image);
   };
#endif // WIDGET_H
