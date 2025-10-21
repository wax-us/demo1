#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>



#ifndef IDF_H

cv::VideoCapture read_video(std::string video_path);
void show_video(cv::VideoCapture video);
cv::Mat find_rect(cv::Mat& frame);




#endif