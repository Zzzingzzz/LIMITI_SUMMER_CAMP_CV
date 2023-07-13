#include "DNN.hpp"

//初始化网络
void DNN::Init_DNN(std::string classesFile, cv::String modelConfiguration, cv::String modelWeights)
{
    // Load names of classes
    std::ifstream classNamesFile(classesFile.c_str());
    if (classNamesFile.is_open())
    {
        std::string className = "";
        while (std::getline(classNamesFile, className))
            classes.push_back(className);
    }
    else{
        std::cout<<"can not open classNamesFile"<<std::endl;
    }

    // Load the network
    net = cv::dnn::readNetFromDarknet(modelConfiguration, modelWeights);
    std::cout<<"Read Darknet..."<<std::endl;
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

std::vector<DNN::DNN_infos> DNN::Get_DNN_infos(cv::Mat& frame)
{
    // Create a 4D blob from a frame.
    
    cv::Mat blob;
    cv::dnn::blobFromImage(frame, blob, 1/255.0, cv::Size(inpWidth, inpHeight), cv::Scalar(0,0,0), true, false);

    //Sets the input to the network
    net.setInput(blob);

    // Runs the forward pass to get output of the output layers
    std::vector<cv::Mat> outs;
    net.forward(outs, getOutputsNames(net));
    // Remove the bounding boxes with low confidence
    
    std::vector<DNN::DNN_infos> infos_To_retutn = postprocess(frame, outs);

    cv::Mat detectedFrame;
    frame.convertTo(detectedFrame, CV_8U);

    return infos_To_retutn;
}


// Get the names of the output layers
std::vector<cv::String> DNN::getOutputsNames(const cv::dnn::Net& net)
{
    static std::vector<cv::String> names;
    if (names.empty())
    {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        std::vector<int> outLayers = net.getUnconnectedOutLayers();
 
        //get the names of all the layers in the network
        std::vector<cv::String> layersNames = net.getLayerNames();
 
        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
            names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}
 
// Remove the bounding boxes with low confidence using non-maxima suppression
std::vector<DNN::DNN_infos> DNN::postprocess(cv::Mat& frame, std::vector<cv::Mat>& outs)
{
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
 
    for (size_t i = 0; i < outs.size(); ++i)
    {
        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class
        // with the highest score for the box.
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
        {
            cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point classIdPoint;
            double confidence;
            // Get the value and location of the maximum score
            cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
 
            if (confidence > confThreshold)
            {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;
 
                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }
 
    // Perform non maximum suppression to eliminate redundant overlapping boxes with
    // lower confidences
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);

    std::vector<DNN::DNN_infos> infos_To_return;

    for (size_t i = 0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        
        if(boxes[idx].x <= 0) boxes[idx].x=0;
        if(boxes[idx].y <= 0) boxes[idx].y=0;
        if(boxes[idx].x + boxes[idx].width >= frame.cols-1)  boxes[idx].width = frame.cols - boxes[idx].x - 1;
        if(boxes[idx].y + boxes[idx].height >= frame.rows-1) boxes[idx].height = frame.rows - boxes[idx].y - 1;
        cv::Rect box = boxes[idx];

        DNN::drawPred(classIds[idx], confidences[idx], box.x, box.y,
                 box.x + box.width, box.y + box.height, frame);

        DNN::DNN_infos res_info;
        res_info.roi = box;
        res_info.label = classes[classIds[idx]];

        infos_To_return.push_back(res_info);
    }

    return infos_To_return;
}
 
// Draw the predicted bounding box
void DNN::drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame)
{
    //Draw a rectangle displaying the bounding box
    cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(128, 0, 128));
 
    //Get the label for the class name and its confidence
    std::string label = cv::format("%.2f", conf);
    if (!classes.empty())
    {
        CV_Assert(classId < (int)classes.size());
        label = classes[classId] + ":" + label;
        // std::cout << classes[classId] << std::endl;
        // std::cout << label << std::endl;
    }
    else
    {
        std::cout<<"classes is empty..."<<std::endl;
    }
 
    //Display the label at the top of the bounding box
    int baseLine;
    cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 2, 2, &baseLine);
    top = std::max(top, labelSize.height);
    cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(128,0,128), 2);
}