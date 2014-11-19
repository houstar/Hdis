/*
 * captureVgaThread.h
 * this file define a class CaptureVGA which use V4L2
 */
#ifndef CAPTUREVGATHREAD_H
#define CAPTUREVGATHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include "captureVga.h"

QT_BEGIN_NAMESPACE
class QImage;
QT_END_NAMESPACE

#define WIDTH (1024)
#define HEIGHT (768)

class captureVgaThread : public QThread
{
    Q_OBJECT
public:
    explicit captureVgaThread(QObject *parent = 0);
    ~captureVgaThread();

signals:
     void captureVgaImage(const QImage &image);

protected:
     void run();

private:

    CaptureVGA *m_pCaptureVGAHandle;
    MemBufUtils *m_membuf;

    QMutex m_mutex;
    QWaitCondition m_condition;

    unsigned char *m_pRgb;
    unsigned char *m_pYuv;

    QImage *m_frame;  //一帧图片
};

#endif // CAPTUREVGATHREAD_H
