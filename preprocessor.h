#pragma once
#include "opencv2/opencv.hpp"

class preprocessor {
public:
	preprocessor();
	void transfer_to_frame(cv::VideoCapture cap);
	cv::Mat apply_sobel(bool use_opencv=false);
	void set_binarize_flag(int thresh);
	void subsample_img(float sub_fact);

private:
	bool to_binarize = false, to_subsample = false;
	int height = 0, width = 0;
	int dims = 0;
	int pad_size = 0, threshold = 0;
	float fact = 1;

	std::vector<std::vector<int>> filterx{ {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	std::vector<std::vector<int>> filtery{ {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };
	int filter_size = filtery.size();

	cv::Mat frame;
	cv::Mat cv_filterx, cv_filtery;
	cv::Mat opencv_convolve_image();
	cv::Mat pad_image(const int& filter_size);
	cv::Mat convolve_image(cv::Mat frame, const std::vector<std::vector<int>>& filter);
};
