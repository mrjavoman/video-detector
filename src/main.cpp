#include <iostream>
#include <opencv2/opencv.hpp>

#include "detector/model.hpp"
#include "detector/boxdraw.hpp"
#include "logger/logger.hpp"
#include "structs/detectdata.h"

int main(int argc, char ** argv) {

    // Read configration

    // Matrix for holding the image data
    cv::Mat frame;
    // Declare object for capturing the video
    cv::VideoCapture cap(0);
    // Matix vector for AI detections
    std::vector<cv::Mat> detections;

    int frameCount = 0;

    if(!cap.isOpened()) {
        std::cout << "No video stream detected" << std::endl;
        std::system("pause");
        return -1;
    }

    // Initialize the detection model
    Model *model = new Model();
    model->Initialize();

    // Initialize object for drawing boxes on detections
    BoxDraw *draw = new BoxDraw();
    draw->LoadClassNames();

    // Infinite loop that processes video frames
    while(true) {

        cap >> frame;
        // Stop the loop if no video frame is detected
        if (frame.empty()) {
            std::cout << "No video frames detected, stoping stream." << std::endl;
            break;
        }

        // Check detection every 480 frames
        if (frameCount % 480 == 0) {
            DetectionData data = model->Detect(frame, draw);

            // if a detection of intrest has been made send it via pushover
            if(data.classDetection["person"]){

                // Initialize Pushover API
                PushoverAPI *pushover = new PushoverAPI();

                // Draw box around detection
                cv::Mat frameWithBoxes = draw->Draw(data, frame);

                // Write file to disk
                cv::imwrite("./testingPic.jpg", frame);
                std::cout << "Image written to disk" << std::endl;        
                
                // Send the notification via Pushover
                pushover->SendNotification();
                delete pushover;
            }
        }

        // Wait 25 milliseconds for frame processing
        char c = (char)cv::waitKey(25);
        //Logger::Log("Hellooo!");
           
        // Exit if 'Esc' button is pressed
        if(c == 27) {
            break;
        }

        frameCount++;
    }

    // Release memory
    cap.release();
    delete model;
    delete draw;

    return 0;
}