#include <iostream>
#include "widget.h"
#include "captureVgaThread.h"
#include "yuv2rgb/yuv2rgb.h"

captureVgaThread::captureVgaThread(QObject *parent) :
    QThread(parent)
{
    m_pCaptureVGAHandle = new CaptureVGA();
    m_membuf = new MemBufUtils();
    if(m_membuf->open() && m_pCaptureVGAHandle->init()){
        m_pCaptureVGAHandle->start();
    }

    m_pRgb = (unsigned char *)malloc(WIDTH*HEIGHT*sizeof(char)*3);

    m_frame = new QImage(m_pRgb,WIDTH,HEIGHT,QImage::Format_RGB888);
}

captureVgaThread::~captureVgaThread()
{
    if (NULL != m_pCaptureVGAHandle) {
        delete m_pCaptureVGAHandle;
        m_pCaptureVGAHandle = NULL;
    }

    if(m_pRgb)
    {
        free(m_pRgb);
        m_pRgb = NULL;
    }

    if(m_frame)
    {
        delete(m_frame);
        m_frame = NULL;
    }

    m_membuf->close();

    qDebug("after delete capture vga\n");
}

static bool YV12ToBGR24_Pinknoise(unsigned char* pYUV,unsigned char* pBGR24,int width,int height)
{
    if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
        return false;
    unsigned char *yData = pYUV;
    unsigned char *vData = &pYUV[width * height];
    unsigned char *uData = &vData[width * height >> 2];
    yuv420_2_rgb888(pBGR24,yData,uData,vData,width,height,width,width>>1,width*3,yuv2rgb565_table,0);
    return true;
}

void captureVgaThread::run()
{
    forever
    {
        m_pCaptureVGAHandle->dCaptureFrame((void **)&m_pYuv);
        qDebug("after dCaptureFrame");

        YV12ToBGR24_Pinknoise(m_pYuv,m_pRgb,WIDTH,HEIGHT);
        qDebug("after YV12ToBGR24_Pinknoise");

        m_pCaptureVGAHandle->qCaptureFrame();
        qDebug("after qCaptureFrame");

        m_frame->loadFromData(m_pRgb,WIDTH*HEIGHT*3*sizeof(char));

        emit captureVgaImage(*m_frame);

        msleep(20);
    }
}
