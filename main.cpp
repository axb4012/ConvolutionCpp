#include<iostream>
#include "opencv2/opencv.hpp"
#include "preprocessor.h"


const int time_limit = 10;

const bool to_binarize = false;
const int binarize_threshold = 90;

const bool to_subsample = false;
const int subsample_fact = 1;

int main(int argc, char** argv) {
	int runtime = 0;
	cv::Mat frame;
	clock_t start, end;
	char keypress;
	bool keep_running = false;
	cv::VideoCapture cap;
	if (!cap.open(0))
		return 0;
	preprocessor preprocess;

	if(to_binarize)
		preprocess.set_binarize_flag(binarize_threshold);
	if(to_subsample)
		preprocess.subsample_img(subsample_fact);
	
	start = clock();

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
	while (runtime < time_limit || keep_running) {
		
		preprocess.transfer_to_frame(cap);
		frame = preprocess.apply_sobel(true);

		if (frame.empty()) {
			std::cout << "Frame was empty\n";
			break;
		}

		cv::imshow("Display window", frame);
		keypress = (char)cv::waitKey(10);
		if (keypress == 27) {
			break;
		}

		end = clock();
		runtime = int(end - start)/int(CLOCKS_PER_SEC);
	}

	cap.release();
	cv::destroyAllWindows();

}
