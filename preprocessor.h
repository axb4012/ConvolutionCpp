#pragma once
#include "opencv2/opencv.hpp"

class preprocessor {
public:
	preprocessor() {};
	void transfer_to_frame(cv::VideoCapture cap);
	cv::Mat apply_sobel();

private:
	cv::Mat frame;

	template <typename T>
	cv::Mat pad_image(int& filter_size);
};