#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <cmath>
#include <string>


#ifndef IDF_H
//loadVideo.cpp
cv::VideoCapture read_video(std::string video_path);
void show_video(cv::VideoCapture video);

//findRect.cpp
std::vector<cv::Point2f> find_rect(cv::Mat& frame);
cv::Mat idf_red(cv::Mat& frame);

//pnp.cpp
std::vector<cv::Point2f> pnp(cv::Mat& frame, std::vector<cv::Point2f> points2d);

//draw.cpp
void draw_IDFcontours(cv::Mat& frame, std::vector<cv::Point2f> p);
void draw_axis(cv::Mat& frame,std::vector<cv::Point2f> p);





#endif