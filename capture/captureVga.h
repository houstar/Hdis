/*
 * CaptureVga.h
 * this file define a class CaptureVGA which use V4L2
 */

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <linux/videodev2.h>
#include <linux/fb.h>
#include <linux/ti81xxfb.h>
#include <linux/ti81xxhdmi.h>
#include <linux/ti81xxvin.h>
#include <vector>
#include <pthread.h>
#include "../com/semp.h"

#include "../com/membufUtils.h"

#include "captureVideoDefines.h"

using namespace std;

class CaptureVGA;

/**
 * 监听VGA获得的接口
 */
class ICaptureVGAListener {
public:
	virtual ~ICaptureVGAListener() {

	}

	/*在获取VGA缓冲*/
	virtual void onCaptureVGABuffer(CaptureVGA* pHandle, unsigned char* pNV12Buffer, int width, int height) = 0;

	/*在通知VGA格式*/
    //virtual void onNotifyVGAFMT(CaptureVGA* pHandle, int width, int height) = 0;
};

/**
 * 获取VGA视频类
 */
class CaptureVGA {
public:

	/*拍摄任务*/
    /*static void* CaptureVGATask(void *pParam);*/
public:
	CaptureVGA();
	~CaptureVGA();

public:

	
	/* 添加监听*/
	bool addListener(ICaptureVGAListener* pListener);

	/*删除监听*/
	bool removeListener(ICaptureVGAListener* pListener);

    ///*friend*/ void savetofile(char * ptr);


	bool init();

	bool uninit();

	bool start();

	bool stop();

    /*正在拍摄任务*/
   // bool onCaptureTask();
   bool dCaptureFrame(void **frame);

   bool qCaptureFrame();
private:



	/*设置拍摄参数*/
	bool setupCapture();

	/*停止拍摄*/
	bool stopCapture();

	/*开始拍摄*/
	bool startCapture();

	/*从视频区取数据到队列*/
	bool queueCaptureBuffers();

private:

	pthread_t	m_threadID;
	pthread_attr_t m_threadAttr;

	/*监听者列表*/
	vector<ICaptureVGAListener*> m_vecListeners;

	bool 	m_bExit;

	semp_t 	m_exitSem;

	/* 是否init设备*/
	bool 	m_bInited;
	struct capt_obj capt;
};


