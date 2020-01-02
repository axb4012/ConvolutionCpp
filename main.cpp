#include<iostream>
#include "opencv2/opencv.hpp"
#include "preprocessor.h"


const int time_limit = 10;

int main(int argc, char** argv) {
	int start_time, runtime = 0;
	clock_t start, end;
	cv::Mat frame;
	char keypress;
	cv::Mat test(500, 500, 19);
	bool keep_running = false;
	cv::VideoCapture cap;
	if (!cap.open(0))
		return 0;
	preprocessor preprocess;
	
	start = clock();

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
	while (runtime < time_limit || keep_running) {
		cap >> frame;
		preprocess.transfer_to_frame(cap);
		std::cout << frame.type()<<"\n";
		std::cout << preprocess.frame.type() << "\n";
		frame = preprocess.apply_sobel();

		std::cout << int(frame.at<char>(100, 100));

		if (frame.empty()) {
			std::cout << "Frame was empty\n";
			break;
		}

		cv::imshow("Display window", frame);
		keypress = (char)cv::waitKey(25);
		if (keypress == 27) {
			break;
		}

		end = clock();
		runtime = int(end - start)/int(CLOCKS_PER_SEC);
	}

	cap.release();
	cv::destroyAllWindows();

}
