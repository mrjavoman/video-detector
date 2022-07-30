#ifndef MODEL
#define MODEL

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>

#include "boxdraw.hpp"
#include "../pushover/pushoverapi.hpp"

class Model 
{
    private:
        // const float CONFIDENCE_THRESHOLD = 0;
        // const float NMS_THRESHOLD = 0.4;
        // const int NUM_CLASSES = 80;

        std::vector<std::string> class_names;

        // Matrix for holding the image data
        cv::Mat frame;
        // Matrix for holding the image blob that will be used in the AI model
        cv::Mat blob;    
        // Declare object for capturing the video
        //cv::VideoCapture cap(0);

        // The neural net output names
        std::vector<std::string> output_names;
        // Matix vector for AI detections
        std::vector<cv::Mat> detections;
        // Model object
        cv::dnn::Net net;

    public:
        void Initialize();
        DetectionData Detect(cv::Mat &frame, BoxDraw *boxDraw);

};

#endif
