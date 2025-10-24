#include "idf.h"

int main(){
    cv::VideoCapture video;
    video = read_video("../assets/input.avi");
    show_video(video);
    return 0;
}



