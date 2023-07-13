#include <iostream>
#include "DNN.hpp"
#include "WriteXml.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 图片路径
string ImagesPath="/home/pc/7_14_cloud/*.jpg";

//获取文件夹中所有图片
vector<String> GetImage();

int main()
{
    DNN dnn;
    dnn.Init_DNN("/home/pc/桌面/自动标数据集/DNN_Folder/点云/yolo-fastest.names",
                "/home/pc/桌面/自动标数据集/DNN_Folder/点云/yolo-fastest-xl.cfg",
                "/home/pc/桌面/自动标数据集/DNN_Folder/点云/yolo-fastest-xl_70000.weights");

    //获取文件名称和图片
    vector<String> image_files=GetImage();
    vector<Mat> images;
    for(size_t i=0; i<image_files.size(); i++)
    {
        Mat image=imread(image_files[i]);
        images.push_back(image);
        cout << "Find Image " << image_files[i] << endl;
    }

    // 用DNN识别出物体
    WriteXml writexml;
    for(size_t i=0; i<images.size(); i++)
    {
        Mat frame=images[i];

        // DNN识别
        std::vector<DNN::DNN_infos> infos=dnn.Get_DNN_infos(frame);

        // 写xml
        writexml.Write(image_files[i], frame, infos);

        // 显示图片
        imshow("frame",frame);
        waitKey(1);
    }

    return 0;
}

//获取文件夹中所有图片
vector<String> GetImage()
{
    vector<String> image_files;
    glob(ImagesPath,image_files);

    return image_files;
}

