#include "idf.h"

//使用罗德里格旋转公式‌旋转向量 c是要旋转的向量 v是旋转向量 v的长度为旋转角(弧度) 方向为旋转轴
cv::Mat rotateVector(cv::Mat c,cv::Mat v){
    double angle = cv::norm(v);
    cv::Mat u = v/angle;
    cv::Mat uxc = u.cross(c);
    double upc = u.dot(c);
    //公式:v′=vcosθ+(k×v)sinθ+k(k⋅v)(1−cosθ)
    return c*std::cos(angle)+uxc*std::sin(angle)+u*upc*(1-std::cos(angle));
}


//计算位姿
void pnp(std::vector<cv::Point2f> points2d, cv::Mat& frame){
    
    // static std::vector<cv::Point2f> last_points2d;
    // if (last_points2d.empty()) {
    //     last_points2d = points2d;
    // } else {
    //     // 检查点移动距离
    //     double max_move = 0;
    //     for (int i = 0; i < 4; i++) {
    //         double move = cv::norm(points2d[i] - last_points2d[i]);
    //         max_move = std::max(max_move, move);
    //     }
        
    //     std::cout << "最大点移动距离: " << max_move << " 像素" << std::endl;
        
    //     // 如果移动过大，可能检测错误
    //     if (max_move > 10.0) {
    //         std::cout << "检测到异常点移动，使用上一帧点" << std::endl;
    //         points2d = last_points2d;
    //     } else {
    //         last_points2d = points2d;
    //     }
    // }




    
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
    std::vector<cv::Point3f> center3D = {
        cv::Point3f(0,0,0),
        cv::Point3f(0.1,0,0),
        cv::Point3f(0,0.1,0),
        cv::Point3f(0,0,0.1)
    };
    //投影后的点集
    std::vector<cv::Point2f> projectedPoints;
    //投影
    cv::projectPoints(center3D, rvec, tvec, cameraMat, distCoeffs, projectedPoints);

    
    cv::Point2f endx = projectedPoints[1];
    cv::Point2f endy = projectedPoints[2];
    cv::Point2f endz = projectedPoints[3];

    //绘制坐标轴 绿色x轴 蓝色y轴 红色z轴
    // for(int i=0;i<4;i++){
    //     std::cout << endx<<' '<<endy<<' '<<endz<<std::endl;
    // }
    cv::line(frame, projectedPoints[0], projectedPoints[1], cv::Scalar(0,255,0), 2.5, cv::LINE_AA);
    cv::line(frame, projectedPoints[0], projectedPoints[2], cv::Scalar(255,0,0), 2.5, cv::LINE_AA);
    cv::line(frame, projectedPoints[0], projectedPoints[3], cv::Scalar(0,0,255), 2.5, cv::LINE_AA);

    //标注坐标轴
    cv::Point2f textEndx(endx.x, endx.y+5);
    cv::Point2f textEndy(endy.x, endy.y+5);
    cv::Point2f textEndz(endz.x, endz.y+5);
    cv::putText(frame, "X", textEndx, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(50,255,50),2);
    cv::putText(frame, "Y", textEndy, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,50,50),2);
    cv::putText(frame, "Z", textEndz, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(50,50,255),2);
    
    

    

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


