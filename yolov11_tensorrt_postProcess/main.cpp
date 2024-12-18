#include "YOLO.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>

int main()
{
    std::string OnnxFile = "../model/yolov11_official.onnx";
    std::string SaveTrtFilePath = "../model/yolov11_official.engine";
    cv::Mat SrcImage = cv::imread("../images/bus.jpg");

    int img_width = SrcImage.cols;
    int img_height = SrcImage.rows;
    std::cout << "img_width: " << img_width << " img_height: " << img_height << std::endl;

    YOLO YOLO(OnnxFile, SaveTrtFilePath, 1, 3, 640, 640);

    auto t_start = std::chrono::high_resolution_clock::now();
    int Temp = 2000;

    int SleepTimes = 0;
    for (int i = 0; i < Temp; i++)
    {
        YOLO.Inference(SrcImage);
        //std::this_thread::sleep_for(std::chrono::milliseconds(SleepTimes));
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    float total_inf = std::chrono::duration<float, std::milli>(t_end - t_start).count();
    std::cout << "Info: " << Temp << " times infer and postprocess ave cost: " << total_inf / float(Temp) - SleepTimes << " ms." << std::endl;


    for (int i = 0; i < YOLO.DetectiontRects_.size(); i += 6)
    {
        int classId = int(YOLO.DetectiontRects_[i + 0]);
        float conf = YOLO.DetectiontRects_[i + 1];
        int xmin = int(YOLO.DetectiontRects_[i + 2] * float(img_width) + 0.5);
        int ymin = int(YOLO.DetectiontRects_[i + 3] * float(img_height) + 0.5);
        int xmax = int(YOLO.DetectiontRects_[i + 4] * float(img_width) + 0.5);
        int ymax = int(YOLO.DetectiontRects_[i + 5] * float(img_height) + 0.5);

        char text1[256];
        sprintf_s(text1, "%d:%.2f", classId, conf);
        rectangle(SrcImage, cv::Point(xmin, ymin), cv::Point(xmax, ymax), cv::Scalar(255, 0, 0), 2);
        putText(SrcImage, text1, cv::Point(xmin, ymin + 15), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 255), 2);
    }
    //imwrite("../images/result.jpg", SrcImage);
    cv::imshow("infer", SrcImage);
    

    printf_s("== obj: %d \n", int(float(YOLO.DetectiontRects_.size()) / 6.0));
    cv::waitKey(0);

    return 0;
}
