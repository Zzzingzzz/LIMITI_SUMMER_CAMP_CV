#include <iostream>
#include "DNN.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
    // dnn需要的三个文件的路径
    std::string classesFile = "../DNN_Folder/点云/yolo-fastest.names";
    cv::String modelConfiguration = "../DNN_Folder/点云/yolo-fastest-xl.cfg";
    cv::String modelWeights = "../DNN_Folder/点云/yolo-fastest-xl_70000.weights";

    // 初始化dnn神经网络
    DNN dnn;
    dnn.Init_DNN(classesFile, modelConfiguration, modelWeights);

    // 加载要识别的图片
    Mat image = imread("...");

    imshow("before_dnn", image);

    // dnn识别，并返回识别信息
    std::vector<DNN::DNN_infos> infos = dnn.Get_DNN_infos(image);

    imshow("after_dnn", image);
    waitKey(0);

    return 0;
}

