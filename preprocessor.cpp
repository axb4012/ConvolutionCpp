#include "preprocessor.h"
#include<vector>

preprocessor::preprocessor() {}

void preprocessor::transfer_to_frame(cv::VideoCapture cap) {
	cap >> frame;
}

cv::Mat preprocessor::apply_sobel() {
	cv::Mat filtered_frame;
	std::vector<std::vector<int>> filterx{ {-1, 0, 1}, {-2, 0, -2}, {-1, 0, 1} };
	std::vector<std::vector<int>> filtery{ {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };
	int filter_size = filtery.size();

	filtered_frame = pad_image(filter_size);
	filtered_frame = convolve_image(filtered_frame, filterx);
	filtered_frame = convolve_image(filtered_frame, filtery);


}


template <typename T>
cv::Mat preprocessor::pad_image(int& filter_size) {
	int height = frame.rows;
	int width = frame.cols;
	int dims = frame.dims;

	int pad_size = filter_size / 2;

	cv::Mat padded_image((height+pad_size), (width+pad_size), frame.type(), 0);

	for (int i = pad_size; i < height; i++) {
		for (int j = pad_size; j < width; j++) {
			padded_image.at<T>(i, j) = frame.at<T>(i, j);
		}
	}

	return padded_image;
}