#include <bits/stdc++.h>
#include "idf.h"

int main(){
    cv::VideoCapture video;
    video = read_video("/home/krmms/demo1/assets/input.avi");
    show_video(video);
    
    return 0;
}


