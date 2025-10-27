#include "idf.h"


//获取视频并返回视频
cv::VideoCapture read_video(std::string video_path){
    cv::VideoCapture video(video_path,cv::CAP_FFMPEG);//cv::CAP_V4L2
    double fps = video.get(cv::CAP_PROP_FPS); 
    return video;
}


//展示视频并计算位姿
void show_video(cv::VideoCapture video){
    cv::Mat frame;
    int i=0;

    int startFrame = 1;
    video.set(cv::CAP_PROP_POS_FRAMES, startFrame);


    while(true){
        video >> frame;
        if (frame.empty()) {
            std::cout << "视频播放结束！" << std::endl;
            break;
        }

        //阈值化测试 分离通道测试
        // cv::Mat th;
        // cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        // std::vector<cv::Mat> result;
        // cv::split(frame,result);
        // cv::threshold(255-result[2],th,30,255,cv::THRESH_BINARY);
        // cv::dilate(th,frame,kernel);
        //frame = th.clone();

        
        
        // frame = idf_red(frame);
        std::vector<cv::Point2f> vertex = find_rect(frame);
        std::vector<cv::Point2f> projectedPoints = pnp(frame,vertex);
        //画识别框
        draw_IDFcontours(frame,vertex);
        //画坐标轴然后标注坐标轴
        draw_axis(frame, projectedPoints);
        

        
        double currentFrame = video.get(cv::CAP_PROP_POS_FRAMES);
        int key = cv::waitKey(0);
        if(i==0){
            //展示第一帧
            cv::imshow("视频展示", frame);
            std::cout << "视频播放第"<<currentFrame<<"帧"<<std::endl;
            i++;
        }else{
            //展示后面的帧
            if(key == 32){
                cv::imshow("视频展示", frame);
                std::cout << "视频播放第"<<currentFrame<<"帧"<<std::endl;
                
            }else if(key == 27 || cv::getWindowProperty("视频展示", cv::WND_PROP_VISIBLE) < 1){
                std::cout << "视频播放中断" << std::endl;
                break;
            } 
        }
    }
    cv::destroyAllWindows();
}





