#pragma once

#include <QObject>
#include <QCamera>
#include <QVideoSink>
#include <QMediaCaptureSession>
#include <QVideoFrame>
#include <QImage>

#include <opencv2/opencv.hpp>

class VideoProcessor : public QObject{
    Q_OBJECT

public:
    explicit VideoProcessor(const QCameraDevice &cameraDevice, QObject *parent = nullptr);
    void stop();

signals:
    void frameReady(const QImage &frame);

private:
    QCamera *camera;
    QMediaCaptureSession videoCap;
    QVideoSink *videoSink;

    cv::Mat emblemOverlay;
    cv::Mat crosshairOverlay;

    void handleFrame(const QVideoFrame &frame);
    cv::Mat qimageToMat(const QImage &image);
    void addOverlay(cv::Mat &base, const cv::Mat &overlay);
};
