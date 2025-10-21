#include "idf.h"


cv::Mat rotateVector(cv::Mat c,cv::Mat v){
    double angle = cv::norm(v);
    cv::Mat u = v/angle;
    cv::Mat uxc = u.cross(c);
    double upc = u.dot(c);
    return c*std::cos(angle)+uxc*std::sin(angle)+u*upc*(1-std::cos(angle));
}




void pnp(std::vector<cv::Point2f> points2d,cv::Mat& frame){
    std::vector<cv::Point3f> points3d;//h:130mm/0.13m w:50mm/0.05m
    float h = 0.13;
    float w = 0.05;

    points3d.push_back(cv::Point3f(-w/2, h/2, 0));//左上 
    points3d.push_back(cv::Point3f(w/2, h/2, 0));//右上
    points3d.push_back(cv::Point3f(w/2, -h/2, 0));//右下
    points3d.push_back(cv::Point3f(-w/2, -h/2, 0));//左下
    
    
    cv::Mat rvec,tvec;

    cv::Mat cameraMat = (cv::Mat_<double>(3, 3) << 
        9.28130989e+02, 0,     3.77572945e+02,
        0,     9.30138391e+02, 2.83892859e+02,
        0,     0,     1.0); //内参

    cv::Mat distCoeffs = (cv::Mat_<double>(5, 1) << 
        -2.54433647e-01, 5.69431382e-01,
        3.65405229e-03, -1.09433818e-03, -1.33846840);//畸变

    cv::solvePnP(points3d,points2d,cameraMat,distCoeffs,rvec,tvec,false, cv::SOLVEPNP_IPPE);
    //std::cout << rvec.at<double>(0)<<std::endl<< rvec.at<double>(1)<<std::endl<< rvec.at<double>(2)<<std::endl;            
    //std::cout << tvec<<std::endl;

    //x(1,0,0) y(0,1,0) z(0,0,1)
    
    double fx = cameraMat.at<double>(0, 0);
    double fy = cameraMat.at<double>(1, 1);
    double cx = cameraMat.at<double>(0, 2);
    double cy = cameraMat.at<double>(1, 2);

    double u = (fx * tvec.at<double>(0)) / tvec.at<double>(2) + cx;
    double v = (fy * tvec.at<double>(1)) / tvec.at<double>(2) + cy;
    
    cv::Mat x = (cv::Mat_<double>(3,1) << 1.0 ,0.0 ,0.0);
    cv::Mat y = (cv::Mat_<double>(3,1) << 0.0 ,1.0 ,0.0);
    cv::Mat z = (cv::Mat_<double>(3,1) << 0.0 ,0.0 ,1.0);

    cv::Mat rx,ry,rz;
    rx = rotateVector(x,rvec);
    ry = rotateVector(y,rvec);
    rz = rotateVector(z,rvec);
    //std::cout << cv::norm(rx)<<std::endl;
    //std::cout << fabs(rx.at<double>(0)) <<' '<< fabs(ry.at<double>(1)) <<' '<< fabs(rz.at<double>(2)) <<std::endl;
    int width = frame.cols;
    int height = frame.rows;

    

    double l = cv::norm(tvec);
    double px = tvec.at<double>(0)+width/2;
    double py = tvec.at<double>(1)+height/2;

    cv::line(frame, cv::Point(u,v), cv::Point(u+rx.at<double>(0)*50,v+rx.at<double>(1)*50), cv::Scalar(0,255,0));
    cv::line(frame, cv::Point(u,v), cv::Point(u+ry.at<double>(0)*50,v+ry.at<double>(1)*50), cv::Scalar(255,0,0));
    cv::line(frame, cv::Point(u,v), cv::Point(u+rz.at<double>(0)*50,v+rz.at<double>(1)*50), cv::Scalar(0,0,255));






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


