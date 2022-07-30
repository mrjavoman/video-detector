# ifndef DETECTIONDATA_H
# define DETECTIONDATA_H

#include <vector>
#include <opencv2/opencv.hpp>

struct DetectionData
{
    DetectionData(int num) {

        NUM_CLASSES = num;
    }

    int NUM_CLASSES;
    std::vector<int> indices[80];
    std::vector<cv::Rect> boxes[80];
    std::vector<float> scores[80];
    std::unordered_map<std::string, bool> classDetection;

};

# endif