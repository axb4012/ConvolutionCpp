#include "preprocessor.h"
#include<vector>

preprocessor::preprocessor() {
	cv::Mat kern1 = cv::Mat::ones(filter_size, filter_size, CV_32F)/9;
	cv::Mat kern2 = cv::Mat::ones(filter_size, filter_size, CV_32F)/9;

	cv_filterx.create(filter_size, filter_size, CV_64FC1);
	cv_filtery.create(filter_size, filter_size, CV_64FC1);
	//cv_filterx = kern1;
	//cv_filtery = kern2;

	
	for (int i = 0; i < filter_size; i++) {
		for (int j = 0; j < filter_size; j++) {
			cv_filterx.at<double>(i, j) = filterx[i][j];
			cv_filtery.at<double>(i, j) = filtery[i][j];
		}
	}
}

void preprocessor::transfer_to_frame(cv::VideoCapture cap) {
	cap >> frame;
	cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);
	if(to_subsample)
		cv::resize(frame, frame, cv::Size(), fact, fact);

	height = frame.rows;
	width = frame.cols;
	dims = frame.dims;
	//frame.convertTo(frame, int(CV_8UC1));
}

cv::Mat preprocessor::apply_sobel(bool use_opencv) {
	if (use_opencv)
		return opencv_convolve_image();

	cv::Mat filtered_frame;

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
			if (to_binarize) {
				if(sum<threshold)
					convolved_img.at<uchar>(i, j) = 0;
				else
					convolved_img.at<uchar>(i, j) = 255;
			}
			else
				convolved_img.at<uchar>(i, j) = sum;
		}
	}

	return convolved_img;
}


void preprocessor::subsample_img(float sub_fact) {
	to_subsample = true;
	fact = sub_fact;
}

void preprocessor::set_binarize_flag(int thresh) {
	to_binarize = true;
	threshold = thresh;
	std::cout << "Output will be binarized\n";
}


//template <typename T>
cv::Mat preprocessor::pad_image(const int& filter_size) {
	pad_size = filter_size / 2;

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

cv::Mat preprocessor::opencv_convolve_image() {
	cv::Mat cv_filtered_img;

	filter2D(frame, cv_filtered_img, -1, cv_filterx);
	filter2D(cv_filtered_img, cv_filtered_img, -1, cv_filtery);
	if (to_binarize)
		cv::threshold(cv_filtered_img, cv_filtered_img, threshold, 255, cv::THRESH_BINARY);
	

	return cv_filtered_img;
}