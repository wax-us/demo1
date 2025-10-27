#include "idf.h"

//计算位姿 并返回物体坐标轴原点与x,y,z三轴在单位长度处的点的二维投影
std::vector<cv::Point2f> pnp(cv::Mat& frame, std::vector<cv::Point2f> points2d){

    
    //h:130mm/0.13m w:50mm/0.05m
    float w = 0.13;
    float h = 0.05;


    //3d点
    std::vector<cv::Point3f> points3d;
    points3d.push_back(cv::Point3f(-w/2, h/2, 0));//左上 
    points3d.push_back(cv::Point3f(w/2, h/2, 0));//右上
    points3d.push_back(cv::Point3f(w/2, -h/2, 0));//右下
    points3d.push_back(cv::Point3f(-w/2, -h/2, 0));//左下
    
    
    //相机参数
    cv::Mat cameraMat = (cv::Mat_<double>(3, 3) << 
        9.28130989e+02, 0,     3.77572945e+02,
        0,     9.30138391e+02, 2.83892859e+02,
        0,     0,     1.0); //内参

    cv::Mat distCoeffs = (cv::Mat_<double>(5, 1) << 
        -2.54433647e-01, 5.69431382e-01,
        3.65405229e-03, -1.09433818e-03, -1.33846840);//畸变

    double fx = cameraMat.at<double>(0, 0);
    double fy = cameraMat.at<double>(1, 1);
    double cx = cameraMat.at<double>(0, 2);
    double cy = cameraMat.at<double>(1, 2);

    cv::Mat tvec,rvec;

    //pnp解算
    cv::solvePnP(points3d,points2d,cameraMat,distCoeffs,rvec,tvec,false, cv::SOLVEPNP_IPPE);
    
    //获取视频大小
    int width = frame.cols;
    int height = frame.rows;

    //投影
    //坐标轴上原点与xyz正方向上的单位长度点构成的点集
    std::vector<cv::Point3f> center3D;
    center3D.push_back(cv::Point3f(0,0,0));
    center3D.push_back(cv::Point3f(0.1,0,0));
    center3D.push_back(cv::Point3f(0,0.1,0));
    center3D.push_back(cv::Point3f(0,0,0.1));

    //投影后的点集
    std::vector<cv::Point2f> projectedPoints;
    //投影
    cv::projectPoints(center3D, rvec, tvec, cameraMat, distCoeffs, projectedPoints);
    
    return projectedPoints;
    
    
    
    // f1:
    // rvec 长度是旋转弧度, 向量方向是旋转轴
    // rvec[2.018209159662734;    rx
    // -2.005200000827757;        ry
    // 0.3425194222357701]        rz
    // tvec[0.07218972958040154;  x
    // -0.3256612778486115;       y
    // 2.728861933492724]         z
    // x右为正, y下为正, z前为正

}


