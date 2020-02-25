 //OpenCVTest.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"

#ifndef _CORE_HPP
#include "opencv2/core/core.hpp"
#endif // !_OPENCVCORE_H

#ifndef _HIGHGUI_HPP
#include "opencv2/highgui/highgui.hpp"
#endif // !_

#include "opencv2\opencv.hpp"
#include "LoadImage.h"
#include <opencv2\video\tracking.hpp>
//#include <opencv2/tracking.hpp>

using namespace std;
using namespace cv;

CvHaarClassifierCascade *cascade;
CvMemStorage            *storage;

void detect(IplImage *img)
{
	CvSize img_size = cvGetSize(img);
	//img_size.height = img_size.height / 2;
	CvSeq *object = cvHaarDetectObjects(
		img,
		cascade,
		storage,
		1.3, //1.1,//1.5, //-------------------SCALE FACTOR
		2, //2        //------------------MIN NEIGHBOURS
		0, //CV_HAAR_DO_CANNY_PRUNING
		cvSize(0, 0),//cvSize( 30,30), // ------MINSIZE
		img_size //cvSize(70,70)//cvSize(640,480)  //---------MAXSIZE
	);

	//std::cout << "Total: " << object->total << " cars detected." << std::endl;
	for (int i = 0; i < (object ? object->total : 0); i++)
	{
		CvRect *r = (CvRect*)cvGetSeqElem(object, i);
		cvRectangle(img,
			cvPoint(r->x, r->y),
			cvPoint(r->x + r->width, r->y + r->height),
			CV_RGB(255, 0, 0), 2, 8, 0);
	}
	//cvShowImage("video", img);
	//return img;
}

int main()
{
	//LoadImage img("IMG_05031.jpg");
	//img.ShowWindow();

	cascade = (CvHaarClassifierCascade*)cvLoad("cars3.xml", 0, 0, 0);
	storage = cvCreateMemStorage(0);
	
	cvNamedWindow("Driving", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture("test2.mp4");
	IplImage* frame;
	char c;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	cv::Mat src, src_gray;
	cv::Mat sobelEdge;

	int playType = 1;
	bool detectMode = false;

	int iFontFace = 2;
	double dFontSacle = 0.5;
	cv::Point myPos[6];
	cv::String myText[6];	
	// Declares all required variables
	cv::Rect2d roi;
	//cv::Ptr<Tracker>

	while (true)
	{
		frame = cvQueryFrame(capture);
		src = cv::cvarrToMat(frame);

		// 글자 입력
		myText[0] = cv::format("Width : %d Height : %d", frame->width, frame->height);
		myPos[0].x = frame->width - 250;
		myPos[0].y = 30;
		myText[1] = cv::format("1 - Normal");
		myPos[1].x = frame->width - 250;
		myPos[1].y = 50;
		myText[2] = cv::format("2 - GrayScale");
		myPos[2].x = frame->width - 250;
		myPos[2].y = 70;
		myText[3] = cv::format("3 - Sobel Edge");
		myPos[3].x = frame->width - 250;
		myPos[3].y = 90;
		myText[4] = cv::format("esc - exit");
		myPos[4].x = frame->width - 250;
		myPos[4].y = 110;
		myText[5] = cv::format("5 - Vehicle Tracking");
		myPos[5].x = frame->width - 250;
		myPos[5].y = 130;

		//cv::GaussianBlur(src, src, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
		cv::cvtColor(src, src_gray, CV_RGB2GRAY);
		//cv::imshow("Driving", src_gray);

		/// Generate grad_x and grad_y
		cv::Mat grad_x, grad_y;
		cv::Mat abs_grad_x, abs_grad_y;

		/// Gradient X
		cv::Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
		cv::convertScaleAbs(grad_x, abs_grad_x);

		/// Gradient Y
		cv::Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
		cv::convertScaleAbs(grad_y, abs_grad_y);

		/// Total Gradient (approximate)
		cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, sobelEdge);		

		/// Create window & show it
		//cv::namedWindow("Sobel Edge Detector", CV_WINDOW_AUTOSIZE);
		//cv::imshow("Sobel Edge Detector", grad);
		if (playType == 1)
		{
			cv::putText(src, myText[0], myPos[0], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src, myText[1], myPos[1], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src, myText[2], myPos[2], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src, myText[3], myPos[3], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src, myText[4], myPos[4], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src, myText[5], myPos[5], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));

			if (detectMode == true)
			{
				detect(&IplImage(src));
				cvShowImage("Driving", &IplImage(src));
			}
			else
			{
				cvShowImage("Driving", &IplImage(src));
			}
		}
		else if (playType == 2)
		{	
			cv::putText(src_gray, myText[0], myPos[0], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src_gray, myText[1], myPos[1], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src_gray, myText[2], myPos[2], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src_gray, myText[3], myPos[3], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src_gray, myText[4], myPos[4], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(src_gray, myText[5], myPos[5], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			//cv::putText(src_gray, myText, myPos, iFontFace, dFontSacle, cv::Scalar(255, 255, 255));			
			cvShowImage("Driving", &IplImage(src_gray));
			//cv::imshow("Play Gray", src_gray);
		}			
		else if (playType == 3)
		{
			cv::putText(sobelEdge, myText[0], myPos[0], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(sobelEdge, myText[1], myPos[1], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(sobelEdge, myText[2], myPos[2], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(sobelEdge, myText[3], myPos[3], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(sobelEdge, myText[4], myPos[4], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));
			cv::putText(sobelEdge, myText[5], myPos[5], iFontFace, dFontSacle, cv::Scalar(255, 255, 255));

			if (detectMode == true)
			{
				detect(&IplImage(sobelEdge));
				cvShowImage("Driving", &IplImage(sobelEdge));
			}
			else
			{
				cvShowImage("Driving", &IplImage(sobelEdge));
			}
			
			//cvShowImage("Driving", &IplImage(sobelEdge));
			
		}
		//cvShowImage("Driving", src);
		c = cvWaitKey(33) & 0xff;
		if (c == 27)
			break;
		else if (c == 49)
			playType = 1;
		else if (c == 50)		
			playType = 2;
		else if (c == 51)
			playType = 3;
		else if (c == 53)
		{
			if (detectMode == false)
				detectMode = true;
			else
				detectMode = false;
		}
			
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Driving");
    return 0;
}
