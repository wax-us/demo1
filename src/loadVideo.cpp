#include "idf.h"
#include <string>


cv::VideoCapture read_video(std::string video_path){
    cv::VideoCapture video(video_path,cv::CAP_FFMPEG);
    return video;
}



void show_video(cv::VideoCapture video){
    cv::Mat frame;
    int i=0;
    while(true){
        video >> frame;
        

        if (frame.empty()) {
            std::cout << "视频播放结束！" << std::endl;
            break;
        }
        
        frame = find_rect(frame);
        if(i==0){
            cv::imshow("视频展示", frame);
            i = 1;
        }else{
            if(cv::waitKey(0) == 32){
                cv::imshow("视频展示", frame);
            }
        }
        //cv::imshow("视频展示", frame);
        if (cv::waitKey(30) == 27) {
            break;
        }
    }
    cv::destroyAllWindows();
}





