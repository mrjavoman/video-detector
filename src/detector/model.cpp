#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>

#include "model.hpp"
#include "boxdraw.hpp"
#include "../pushover/pushoverapi.hpp"
#include "../structs/detectdata.h"

/* 
    Initialize the ML model used for detecting objects 
*/
void Model::Initialize() {
    // Initialize model.
	net = cv::dnn::readNetFromDarknet("./models/yolov4.cfg", "./models/yolov4.weights");	
	net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);    

    output_names = net.getUnconnectedOutLayersNames();
}

/*
    Predicts an object on a given frame
*/
std::vector<cv::Mat> Model::Detect(cv::Mat &frame, BoxDraw *boxDraw) {

    std::vector<cv::Mat> detections;

    // Setup image blob from the frame
    cv::dnn::blobFromImage(frame, blob, 0.00392, cv::Size(608, 608), cv::Scalar(), true, false, CV_32F);

    // Set the blob as the input for the neural net
    net.setInput(blob);

    // Start a forward pass and get the output detections.
    net.forward(detections, output_names);

    //DetectionData data = boxDraw->DetectBox(detections,frame);

    cv::Mat frameWithBoxes = boxDraw->Draw(detections, frame);

    cv::imwrite("./testingPic.jpg", frame);
    std::cout << "Image written to disk" << std::endl;
    
    return detections;
}