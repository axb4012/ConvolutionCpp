#include<iostream>
#include "opencv2/opencv.hpp"
#include "preprocessor.h"


const int time_limit = 10;

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
	preprocess.set_binarize_flag(90);
	preprocess.subsample_img(0.5);
	
	start = clock();

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
	while (runtime < time_limit || keep_running) {
		//cap >> frame;
		preprocess.transfer_to_frame(cap);
		frame = preprocess.apply_sobel();

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
