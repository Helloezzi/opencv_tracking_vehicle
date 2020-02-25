#include "stdafx.h"
#include "LoadImage.h"

#ifndef _HIGHGUI_HPP
#include "opencv2/highgui/highgui.hpp"
#endif // !_

//LoadImage::LoadImage(const std::tstring& filename)
//	: m_FileName(filename)
//{
//	cv::String temp((char*)&m_FileName);
//	m_Image = cv::imread(temp);
//}

LoadImage::LoadImage(const cv::String filename)
	: m_FileName(filename)
{
	m_Image = cv::imread(m_FileName);
}

LoadImage::~LoadImage()
{
	//cvReleaseImage(m_Image);
	m_Image.release();
}

void LoadImage::ShowWindow()
{
	if (!m_Image.empty())
	{
		cv::namedWindow("Test Image");
		cv::imshow("Test Image", m_Image);
		cv::waitKey(0);
	}
}