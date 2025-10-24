#include "idf.h"

//寻找最小外接矩形 并返回其四个顶点
std::vector<cv::Point2f> find_rect(cv::Mat& frame){
    cv::Mat grey,th;
    std::vector<std::vector<cv::Point>> con1,con2;
    std::vector<cv::Vec4i> h;
    cv::Point2f p[4];//端点数组
    
    //二值化图像
    cv::cvtColor(frame,grey,cv::COLOR_RGB2GRAY);
    cv::threshold(grey,th,75,255,cv::THRESH_BINARY_INV);
    cv::findContours(th,con1,h,3,cv::CHAIN_APPROX_SIMPLE);
    cv::cvtColor(th,th,cv::COLOR_GRAY2RGB);
    
    //判断荧光灯
    //应该有两个 但阈值化后会可能会出现三到四个识别轮廓 将其全都放到con2 然后再全放到con2[0]中
    for(int i=0;i<h.size();i++){
        if(h[i][2] == -1){
            con2.push_back(con1[i]);
        }
    }

    for(int i=0;i<con2.size();i++){
        con2[0].insert(con2[0].end(),con2[i].begin(),con2[i].end());
    }

    //对con2[0]中的所有点识别最小外接矩形 然后获取矩形的四个顶点与中心点并返回
    cv::RotatedRect rect = minAreaRect(con2[0]);
    rect.points(p);


    std::vector<cv::Point2f> p_out;
    p_out.insert(p_out.begin(),p,p+4);//四个顶点
    //绘制识别框
    for(int i=0;i<4;i++){
        cv::line(frame, p_out[i], p_out[(i+1)%4], cv::Scalar(0,255,255), 2, cv::LINE_AA);
        cv::line(frame, p_out[i], rect.center, cv::Scalar(0,255,255), 2, cv::LINE_AA);
        //std::cout << p_out[i]<<' ';
    }
    return p_out;


}
