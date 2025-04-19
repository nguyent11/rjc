#include <opencv2/opencv.hpp>
#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("Using OpenCV to convert an image to greyscale.\n");
    printf("Usage: ./a.out <image file path>\n");

    cv::Mat colorImg = cv::imread(argv[1]);

    cv::Mat greyImg;
    cv::cvtColor(colorImg, greyImg, cv::COLOR_BGR2GRAY);
    
    
    bool res = cv::imwrite("grey_result.jpg", greyImg);

    //cv::imshow("Original Image", colorImg);
    //cv::imshow("Grayscale Image", greyImg);
    //cv::waitKey(0);
    //cv::destroyAllWindows();

    return 0;
}
