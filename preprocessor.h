#pragma once
#include "opencv2/opencv.hpp"

class preprocessor {
public:
	preprocessor();
	void transfer_to_frame(cv::VideoCapture cap);
	cv::Mat apply_sobel();
	cv::Mat frame;
	void set_binarize_flag(int thresh);
	void subsample_img(float sub_fact);

private:

	int height = 0;
	int width = 0;
	int dims = 0;
	int pad_size = 0;
	bool to_binarize = false, to_subsample = false;
	float fact = 1;
	int threshold = 0;
	//template <typename T>
	cv::Mat pad_image(const int& filter_size);
	cv::Mat convolve_image(cv::Mat frame, const std::vector<std::vector<int>>& filter);
};
