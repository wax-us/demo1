#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <cmath>
#include <string>


#ifndef IDF_H

cv::VideoCapture read_video(std::string video_path);
void show_video(cv::VideoCapture video);


std::vector<cv::Point2f> find_rect(cv::Mat& frame);

void pnp(std::vector<cv::Point2f> points2d, cv::Mat& frame);


#endif