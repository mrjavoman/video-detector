#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>

#include "boxdraw.hpp"
#include "../structs/detectdata.h"

int BoxDraw::LoadClassNames() {
      
    std::ifstream class_file("./classes.txt");
    if (!class_file)
    {
        std::cerr << "failed to open classes.txt\n";
        return 1;
    }

    std::string line;
    while (std::getline(class_file, line)) {
        class_names.push_back(line);
    }

    return 0;    
}

DetectionData BoxDraw::DetectBox(std::vector<cv::Mat> &detections, cv::Mat &frame) {

    DetectionData data = DetectionData(NUM_CLASSES);

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
                    data.boxes[c].push_back(rect);  
                    data.scores[c].push_back(confidence);
                }
            }
        }
    }

    // Perform non maximum suppression to eliminate redundant overlapping boxes with lower confidences.
    // https://learnopencv.com/deep-learning-based-object-detection-using-yolov3-with-opencv-python-c/
    for (int c = 0; c < NUM_CLASSES; c++)
        cv::dnn::NMSBoxes(data.boxes[c], data.scores[c], 0.0, NMS_THRESHOLD, data.indices[c]);
    

    // Build a hash map with the detection status for all classes       
    for (int c= 0; c < NUM_CLASSES; c++)
    {        
        data.classDetection[class_names[c]] = data.indices[c].size();
    }

    return data;
}

cv::Mat BoxDraw::Draw(DetectionData data, cv::Mat &frame) {

    // Draw the rectangle with label and output the results to the console
    // passes the frame by reference?            
    for (int c= 0; c < NUM_CLASSES; c++)
    {
        for (size_t i = 0; i < data.indices[c].size(); ++i)
        {
            const auto color = colors[c % NUM_COLORS];

            auto idx = data.indices[c][i];
            const auto& rect = data.boxes[c][idx];
            cv::rectangle(frame, cv::Point(rect.x, rect.y), cv::Point(rect.x + rect.width, rect.y + rect.height), color, 3);

            // std::cout << c << " and " << i << std::endl;
            // std::cout << class_names.size() << std::endl;
            std::ostringstream label_ss;
            label_ss << class_names[c] << ": " << std::fixed << std::setprecision(2) << data.scores[c][idx];
            auto label = label_ss.str();

            std::cout << "class: " << class_names[c] << " score: " << data.scores[c][idx] << std::endl;
            
            int baseline;
            auto label_bg_sz = cv::getTextSize(label.c_str(), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, 1, &baseline);
            cv::rectangle(frame, cv::Point(rect.x, rect.y - label_bg_sz.height - baseline - 10), cv::Point(rect.x + label_bg_sz.width, rect.y), color, cv::FILLED);
            cv::putText(frame, label.c_str(), cv::Point(rect.x, rect.y - baseline - 5), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0, 0, 0));
        }
    }

    return frame;
}