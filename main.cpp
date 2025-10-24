#include "idf.h"

int main(){
    std::cout <<"按空格下一帧, 按其他键退出"<<std::endl;
    cv::VideoCapture video;
    video = read_video("../assets/input.avi");
    show_video(video);
    return 0;
}



