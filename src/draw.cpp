#include "idf.h"

//画识别框 识别框应有四个顶点 即p应该只有四个点元素s
void draw_IDFcontours(cv::Mat& frame, std::vector<cv::Point2f> p){
    cv::RotatedRect rect = minAreaRect(p);
    for(int i=0;i<4;i++){
        cv::line(frame, p[i], p[(i+1)%4], cv::Scalar(0,255,255), 2, cv::LINE_AA);
        cv::line(frame, p[i], rect.center, cv::Scalar(0,255,255), 2, cv::LINE_AA);
    }
}

//画坐标轴然后标注坐标轴 p有四个点元素 p[0]是原点 p[1-3]分别是x,y,z轴单位长度的点
void draw_axis(cv::Mat& frame,std::vector<cv::Point2f> p){

    cv::Point2f endx = p[1];
    cv::Point2f endy = p[2];
    cv::Point2f endz = p[3];


    //绘制坐标轴 绿色x轴 蓝色y轴 红色z轴
    // for(int i=0;i<4;i++){
    //     std::cout << endx<<' '<<endy<<' '<<endz<<std::endl;
    // }
    cv::line(frame, p[0], p[1], cv::Scalar(0,255,0), 2.5, cv::LINE_AA);
    cv::line(frame, p[0], p[2], cv::Scalar(255,0,0), 2.5, cv::LINE_AA);
    cv::line(frame, p[0], p[3], cv::Scalar(0,0,255), 2.5, cv::LINE_AA);

    //标注坐标轴
    cv::Point2f textEndx(endx.x, endx.y+5);
    cv::Point2f textEndy(endy.x, endy.y+5);
    cv::Point2f textEndz(endz.x, endz.y+5);
    cv::putText(frame, "X", textEndx, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(50,255,50),2);
    cv::putText(frame, "Y", textEndy, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,50,50),2);
    cv::putText(frame, "Z", textEndz, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(50,50,255),2);
}   