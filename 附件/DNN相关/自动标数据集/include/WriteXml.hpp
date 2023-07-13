#ifndef WRITEXML_HPP
#define WRITEXML_HPP

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "DNN.hpp"

class WriteXml
{

public:

/**
 * @brief 生成xml文件
 * @param image_path 图片的路径
 * @param frame 图片
 * @param infos 图片中识别出的物体信息
 */
    void Write(std::string image_path, cv::Mat frame, std::vector<DNN::DNN_infos> infos);

private:

/**
 * @brief 获取生成的xml的文件的路径
 * @param image_path 图片的路径
 * @return std::vector<std::string> 生成的xml的文件的路径
 */
    std::vector<std::string> xml_paths(std::string image_path);

};

#endif