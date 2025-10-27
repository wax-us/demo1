#include "idf.h"


//识别红色 返回红色为255其他颜色为0的矩阵
cv::Mat idf_red(cv::Mat& frame){
    //rgb识别
    cv::Mat th;
    std::vector<cv::Mat> result;
    //灰度化效果不好 所以用分通道
    cv::split(frame,result);
    //二值化图像 result[2]是红色通道
    cv::threshold(255-result[2],th,90,255,cv::THRESH_BINARY);
    return th;

    //hsv识别
    // cv::Mat hsv, mask,mask1, mask2;
    // cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
    // // 红色在HSV色环的两端
    // inRange(hsv, cv::Scalar(0, 30, 30), cv::Scalar(40, 255, 255), mask1);
    // inRange(hsv, cv::Scalar(110, 30, 30), cv::Scalar(180, 255, 255), mask2);
    // mask = mask1 | mask2;
    // cv::threshold(mask,mask,250,255,cv::THRESH_BINARY_INV);
    // cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    // cv::dilate(mask,mask,kernel,cv::Point(-1,-1),2);
    // return mask.clone();
}



//寻找最小外接矩形 并返回其四个顶点
std::vector<cv::Point2f> find_rect(cv::Mat& frame){
    
    std::vector<std::vector<cv::Point>> con1,con2;
    std::vector<cv::Vec4i> h;
    cv::Point2f p[4];//端点数组
    cv::Mat temp = idf_red(frame);

    cv::findContours(temp,con1,h,3,cv::CHAIN_APPROX_SIMPLE);
    
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
    return p_out;


}
