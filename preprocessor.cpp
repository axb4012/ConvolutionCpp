#include "preprocessor.h"
#include<vector>

preprocessor::preprocessor() {}

void preprocessor::transfer_to_frame(cv::VideoCapture cap) {
	cap >> frame;
}

cv::Mat preprocessor::apply_sobel() {
	std::vector<std::vector<int>> filter;

}