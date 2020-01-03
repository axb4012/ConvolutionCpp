#include "preprocessor.h"
#include<vector>

preprocessor::preprocessor() {}

void preprocessor::transfer_to_frame(cv::VideoCapture cap) {
	cap >> frame;
	height = frame.rows;
	width = frame.cols;
	dims = frame.dims;


	cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);
	//frame.convertTo(frame, int(CV_8UC1));
}

cv::Mat preprocessor::apply_sobel() {
	cv::Mat filtered_frame;
	std::vector<std::vector<int>> filterx{ {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	std::vector<std::vector<int>> filtery{ {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };
	int filter_size = filtery.size();

	filtered_frame = pad_image(filter_size);
	filtered_frame = convolve_image(filtered_frame, filterx);
	filtered_frame = convolve_image(filtered_frame, filtery);

	return filtered_frame;
}

cv::Mat preprocessor::convolve_image(cv::Mat filtered_frame, const std::vector<std::vector<int>>& filter) {
	int sum;
	cv::Mat convolved_img = filtered_frame;
	for (int i = pad_size; i < height-1; i++) {
		for (int j = pad_size; j < width-1; j++) {
			sum = 0;
			for (int k = (i - pad_size); k <= (i + pad_size); k++) {
				for (int m = (j - pad_size); m <= (j + pad_size); m++) {
					sum = sum + (int(frame.at<uchar>(k, m)) * filter[k - (i-pad_size)][m - (j-pad_size)]);
				}
			}
			//if(sum<200)
			//	convolved_img.at<uchar>(i, j) = 0;
			//else
			//	convolved_img.at<uchar>(i, j) = 255;

			convolved_img.at<uchar>(i, j) = sum;
		}
	}

	return convolved_img;
}


//template <typename T>
cv::Mat preprocessor::pad_image(const int& filter_size) {
	//std::cout << "\nFilter size is " << filter_size << "\n";
	pad_size = filter_size / 2;
	//std::cout << "\nPad size is " << pad_size << "\n";

	int padx, pady = pad_size;

	cv::Mat padded_image((height+(2*pad_size)), (width+(2*pad_size)), frame.type(), 10);


	for (int i = 0; i < height; i++) {
		padx = pad_size;
		for (int j = 0; j < width; j++) {
			padded_image.at<uchar>(pady, padx) = frame.at<uchar>(i, j);
			padx++;
		}
		pady++;
	}

	return padded_image;
}