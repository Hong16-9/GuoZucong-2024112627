#include <opencv2/core.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;
int main()
{
    int ji = 0;//统计帧
    string inputVideoPath = "/home/h16/1class/yong/no7/output_0.avi";//嘻嘻
    // 打开视频文件
    cv::VideoCapture cap(inputVideoPath);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video." << std::endl;
        return -1;
    }
    // 原始图像
    cv::Mat frame;
    // 裁剪后的图像
    cv::Mat croppedImage;
    //灰度图像
    cv::Mat grayImg;
    //二值化图像
    cv::Mat binaryImage;
    //轮廓图像
    cv::Mat contourImage;

    // 获取视频的一些基本信息
    double fps = cap.get(cv::CAP_PROP_FPS); // 帧率
    int frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)); // 帧宽
    int frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)); // 帧高
    while (true) {
        // 逐帧读取视频
        cap >> frame; 
        if (frame.empty()) {
            break; // 如果没有更多帧，则退出循环
        }
        //彩色图转灰度图
        cv::cvtColor(frame, grayImg, cv::COLOR_BGR2GRAY); 

        // 设置二值化阈值，使用灰度图进行二值化操作
        int thresholdValue = 128;
        cv::threshold(grayImg, binaryImage, thresholdValue, 255, cv::THRESH_BINARY);

        // 应用高斯模糊，减少噪声
        cv::GaussianBlur(binaryImage, binaryImage, cv::Size(5, 5), 0);

        // 边缘检测（Canny算法）
        cv::Mat edges;
        cv::Canny(binaryImage, edges, 100, 200);

        // 查找轮廓
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // 去除小轮廓  
        std::vector<std::vector<cv::Point>> contours_filtered;  
        for (int i = 0; i < contours.size(); i++) 
        {  
            double area = cv::contourArea(contours[i]);  
            if (area > 70) 
            { 
                contours_filtered.push_back(contours[i]);  
            }  
        }  

        contourImage = cv::Mat::zeros(frame.size(), CV_8UC3);
        //求轮廓的中心点
        vector<Moments> mom (contours_filtered.size());
        vector<Point> center (contours_filtered.size());
        for(int i = 0; i < contours_filtered.size();i++)
        {
            mom[i] = moments(contours_filtered[i]);
        }
        for(int i = 0; i < contours_filtered.size();i++)
        {
            center[i] = Point(mom[i].m10 / mom[i].m00, mom[i].m01 / mom[i].m00); 
        }
        for (int i = 0; i < contours_filtered.size(); i++) 
        {
            for (int j = i+1; j < contours_filtered.size(); j++) 
            {
                double distance = norm(center[i] - center[j]); 
                // 计算线段i与线段j的向量  
                Point vec_ij = center[j] - center[i];  

                // 计算线段i与水平线的参考向量  
                Point ref_vec(1, 0); // 水平线的参考向量  

                // 计算线段i与线段j的夹角的余弦值  
                double cos_angle = vec_ij.dot(ref_vec) / (norm(vec_ij) * norm(ref_vec));  

                // 计算夹角的弧度值  
                double angle = acos(cos_angle);  

                // 将弧度转换为角度  
                double angle_deg = angle * 180 / CV_PI;  

                int a = 10;
                if (distance < 60 && angle_deg <= 10) 
                {
                    line(contourImage, center[i] + Point(0,a), center[j] + Point(0,a), cv::Scalar(255, 0, 0), 2);
                    line(contourImage, center[i] - Point(0,a), center[j] - Point(0,a), cv::Scalar(255, 0, 0), 2);    
                }
            }
        }

        //求角速度
        if (contours_filtered.size() == 4) 
        {
            if(CV_PI/ji/60 > 0.05)
            {
                cout << CV_PI/ji/60<<" ";
            }
            ji = 0;
        }
        ji++;

        // 绘制查找到的轮廓
        cv::drawContours(contourImage, contours_filtered, -1, cv::Scalar(255, 0, 0), 2);

        // 显示结果
        cv::imshow("Original Image", frame);
        cv::imshow("Contour Image", contourImage);
        if (cv::waitKey(10) >= 0) break; //调整显示速度
        
    }
    return 0;
}
