#ifndef DNN_HPP
#define DNN_HPP

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class DNN
{
    public:
        struct DNN_infos
        {
            cv::Rect roi; // 识别到的物体的框
            std::string label; // 识别到的物体的label
        };

        //初始化网络
        void Init_DNN(std::string classesFile, cv::String modelConfiguration, cv::String modelWeights);
        
        std::vector<DNN::DNN_infos> Get_DNN_infos(cv::Mat& frame);

    private:
        // Initialize the parameters
        float confThreshold = 0.7; // Confidence threshold
        float nmsThreshold = 0.4;  // Non-maximum suppression threshold
        int inpWidth = 416;        // Width of network's input image
        int inpHeight = 416;       // Height of network's input image

        // Remove the bounding boxes with low confidence using non-maxima suppression
        std::vector<DNN::DNN_infos> postprocess(cv::Mat& frame, std::vector<cv::Mat>& outs);
        
        // Get the names of the output layers
        std::vector<cv::String> getOutputsNames(const cv::dnn::Net& net);
        
        // Draw the predicted bounding box
        void drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame);

        std::vector<std::string> classes;

        cv::dnn::Net net;
};

#endif