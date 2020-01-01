#pragma once
#include "opencv2/opencv.hpp"

class preprocessor {
public:
	preprocessor() {};
	void transfer_to_frame(cv::VideoCapture cap);
	cv::Mat apply_sobel();

private:
	cv::Mat frame;
};