#ifndef BOX_DRAW
#define BOX_DRAW

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>

#include "../pushover/pushoverapi.hpp"

class BoxDraw 
{
    private:
        const float CONFIDENCE_THRESHOLD = 0;
        const float NMS_THRESHOLD = 0.4;
        const int NUM_CLASSES = 80;        

        std::vector<std::string> class_names;

        // Colors for bounding boxes
        const cv::Scalar colors[4] = {
            {0, 255, 255},
            {255, 255, 0},
            {0, 255, 0},
            {255, 0, 0}
        };
        static const auto NUM_COLORS = sizeof(colors)/sizeof(colors[0]);        

    public:
        cv::Mat Draw(std::vector<cv::Mat> &detections, cv::Mat &frame);
        int LoadClassNames();

};

#endif