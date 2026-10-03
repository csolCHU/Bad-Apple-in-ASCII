/*
A precautionary, this is a program written with other repository documentation and 
AI-assistance teaching me rudimentary logic for each syntax and function. 
Source code may not be polished or may look amateurish, please take note
this is for me to learn how to program. 
*/
#include <iostream>
#include <string>
#include <filesystem>
#include <algorithm> 

#include <windows.h>
#include <commdlg.h>

#include <chrono>
#include <thread>

#include <opencv2/opencv.hpp>

std::string selectMp4(){ //Function where it allows the user to select from file explorer video

    char selectedMp4[MAX_PATH] = ""; //Array holds Windows default max characters

    OPENFILENAMEA dialog{};
    dialog.lStructSize = sizeof(dialog); //Size of dialog structure
    dialog.lpstrFile = selectedMp4; //Tells the program where the file path is
    dialog.nMaxFile = MAX_PATH;  //Path storage array
    dialog.lpstrFilter = "MP4 videos (*.mp4)\0*.mp4\0"; //Describes file type or file name
    dialog.nFilterIndex = 1; //Optional but I put it anyways lol, program only chooses mp4 file
    dialog.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;  //Failsafe so user will only select an existing file

    if (GetOpenFileNameA(&dialog)){
        return selectedMp4;
    }

    return "";

}

std::string convertFrametoAscii(
    const cv::Mat& sourceFrame,
    int displayWidth,
    int displayHeight,
    const std::string& asciiChar)
    {
        cv::Mat resizedFrame;
        cv::Mat grayscaleFrame; 

        cv::resize(sourceFrame,resizedFrame, cv::Size(displayWidth,displayHeight));
        cv::cvtColor(resizedFrame, grayscaleFrame, cv::COLOR_BGR2GRAY);

        std::string asciiFrame;
        asciiFrame.reserve((displayWidth + 1) * displayHeight);
        
        const int asciiCount = static_cast<int>(asciiChar.size());

        for (int row = 0; row < grayscaleFrame.rows; ++row){
            for(int column = 0; column < grayscaleFrame.cols; ++column){ 
                unsigned char brightness = grayscaleFrame.at<unsigned char>(row, column);
                int asciiIndex = brightness * (asciiCount - 1) / 255;
                char displayChar = asciiChar[asciiIndex];

                asciiFrame += displayChar;
            }
            asciiFrame += '\n';
        }

        return asciiFrame; 
    }

int main(){

    std::string videoPath = selectMp4(); 

    if (videoPath.empty()){//Ends program if no video was selected
            std::cout << "No video selected." << std::endl;
            return 0; 
    }

    /*
    videoPath is the retrieval of file path 
    - selectedPath allows the program to filter and see if selected file is an .mp4: 
    folder -> C:\Videos
    filename -> badapple.mp4
    fileType -> .mp4 
    */
    std::filesystem::path selectedPath(videoPath); 
    std::string fileType = selectedPath.extension().string();

    if (fileType != ".mp4"){
        std::cerr << "Error. Selected file is not an mp4." << std::endl; 
        return 1; 
    }

    cv::VideoCapture video(videoPath);

    if (!video.isOpened()){ //Error return if failed process. OpenCV opens video thingymajig
        std::cerr << "Error: OpenCV could not open the video" << std::endl; 
        return 1; 
    }

    const int displayWidth = 120;  //Fixed display width
    const int displayHeight = 45;  //Fixed display height
    const double displayFramerate = 30.0; //Fixed ASCII framerate

    const std::chrono::duration<double> frameDuration(1.0 / displayFramerate);

    cv::Mat frame; 
    const std::string asciiChar =  " .:-=+*#%@"; //ASCII assignment

    std::cout << "\x1B[2J\x1B[H";

    while(video.read(frame)){
        
        std::string asciiFrame = convertFrametoAscii(
            frame, displayWidth, displayHeight, asciiChar
        );

        std::cout << "\x1B[H" << asciiFrame << std::flush;
        std::this_thread::sleep_for(frameDuration);
    }

    return 0; 

}