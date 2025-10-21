#include "idf.h"


std::vector<cv::Point2f> find_rect(cv::Mat& frame){
    cv::Mat grey,th;
    std::vector<std::vector<cv::Point>> con1,con2;
    std::vector<cv::Vec4i> h;
    cv::Point2f p[4];//端点数组
    
    cv::cvtColor(frame,grey,cv::COLOR_RGB2GRAY);
    cv::threshold(grey,th,75,255,cv::THRESH_BINARY_INV);
    cv::findContours(th,con1,h,3,2);
    cv::cvtColor(th,th,cv::COLOR_GRAY2RGB);

    for(int i=0;i<h.size();i++){
        if(h[i][2] == -1){
            con2.push_back(con1[i]);
        }
    }

    for(int i=0;i<con2.size();i++){
        con2[0].insert(con2[0].end(),con2[i].begin(),con2[i].end());
    }

    cv::RotatedRect rect = minAreaRect(con2[0]);

    rect.points(p);
    
    std::vector<cv::Point2f> p_out;
    p_out.insert(p_out.begin(),p,p+4);

    // for(int i=0;i<4;i++){
    //     std::cout << p_out[i]<<' ';
    // }
    // std::cout << std::endl;




    return p_out;



}
