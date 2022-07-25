#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>

#include "boxdraw.hpp"

cv::Mat BoxDraw::Draw(std::vector<cv::Mat> &detections, cv::Mat &frame) {

    std::vector<int> indices[NUM_CLASSES];
    std::vector<cv::Rect> boxes[NUM_CLASSES];
    std::vector<float> scores[NUM_CLASSES];

    // Process detections and assign the boxes and the confidence number on the detection 
    for (auto& output : detections)
    {
        const auto num_boxes = output.rows;
        for (int i = 0; i < num_boxes; i++)
        {
            auto x = output.at<float>(i, 0) * frame.cols;
            auto y = output.at<float>(i, 1) * frame.rows;
            auto width = output.at<float>(i, 2) * frame.cols;
            auto height = output.at<float>(i, 3) * frame.rows;
            cv::Rect rect(x - width/2, y - height/2, width, height);

            for (int c = 0; c < NUM_CLASSES; c++)
            {
                auto confidence = *output.ptr<float>(i, 5 + c);
                if (confidence >= CONFIDENCE_THRESHOLD)
                {
                    boxes[c].push_back(rect);
                    scores[c].push_back(confidence);
                }
            }
        }
    }

    // Perform non maximum suppression to eliminate redundant overlapping boxes with lower confidences.
    // https://learnopencv.com/deep-learning-based-object-detection-using-yolov3-with-opencv-python-c/
    for (int c = 0; c < NUM_CLASSES; c++)
        cv::dnn::NMSBoxes(boxes[c], scores[c], 0.0, NMS_THRESHOLD, indices[c]);
    

    // Show how many detections 
    // Todo, put detection in hash map to allow for easier handling.
    std::cout << "Number of detections" << std::endl;
    for (int c= 0; c < NUM_CLASSES; c++)
    {
        if(indices[c].size())
            std::cout << "class " << c << " has " << indices[c].size() << std::endl;
    }

    return frame;
}