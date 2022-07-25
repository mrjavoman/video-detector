#include <iostream>
#include <opencv2/opencv.hpp>

#include "detector/model.hpp"
#include "logger/logger.hpp"

int main() {

    // Matrix for holding the image data
    cv::Mat frame;
    // Declare object for capturing the video
    cv::VideoCapture cap(0);
    // Matix vector for AI detections
    std::vector<cv::Mat> detections;

    int frameCount = 0;
	//bool imageWritten = true;

    if(!cap.isOpened()) {
        std::cout << "No video stream detected" << std::endl;
        std::system("pause");
        return -1;
    }

    // Initialize the detection model
    Model *model = new Model();
    model->Initialize();

    // Infinite loop that processes video frames
    while(false) {

        cap >> frame;
        // Stop the loop if no video frame is detected
        if (frame.empty()) {
            std::cout << "No video frames detected, stoping stream." << std::endl;
            break;
        }

        // Check detection every 480 frames
        if (frameCount % 480 == 0) {
            detections = model->Detect(frame);

            // if a detection of intrest has been made send it via pushover
            //
        }

        // Wait 25 milliseconds for frame processing
        char c = (char)cv::waitKey(25);

        // Exit if 'Esc' button is pressed
        if(c == 27) {
            break;
        }

        frameCount++;
    }

    // Release memory
    cap.release();
    delete model;

    Logger::Log("Hellooo!");

    return 0;
}