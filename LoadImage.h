#ifndef _LOADIMAGE_H
#define _LOADIMAGE_H

#ifndef _STRING_H
	#include "string.h"
#endif // !_STRING_H

#ifndef _CORE_H
#include "opencv\cxcore.h"
#endif // !_CORE_H

class LoadImage
{
public:
	//LoadImage(const std::tstring& filename);
	LoadImage(const cv::String filename);
	~LoadImage();

	cv::Mat GetImage() { return m_Image; }
	void ShowWindow();

private:
	cv::Mat m_Image;
	//const std::tstring& m_FileName;
	const cv::String m_FileName;
};

#endif // !_LOADIMAGE_H

