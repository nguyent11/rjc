#include <QDebug>
#include <QMediaDevices>
#include <QTimer>

#include "videoprocessor.hpp"

VideoProcessor::VideoProcessor(const QCameraDevice &cameraDevice, QObject *parent) 
    : QObject(parent), camera(new QCamera(cameraDevice)), videoSink(new QVideoSink(this)) {

    qDebug() << "Creating video processor object.";

    // Read the file containing the overlay for emblems.
    // Ensure that the image data is in the correct color format of RGBA.
    emblemOverlay = cv::imread("./resources/verminator_emblem.png", cv::IMREAD_UNCHANGED);
    cv::cvtColor(emblemOverlay, emblemOverlay, cv::COLOR_BGRA2RGBA);

    // Read the file containing the overlay for crosshair.
    // Ensure the imagage data is in RGBA format.
    crosshairOverlay = cv::imread("./resources/crosshairgreen.png", cv::IMREAD_UNCHANGED);
    cv::cvtColor(crosshairOverlay, crosshairOverlay, cv::COLOR_BGRA2RGBA);
    cv::resize(crosshairOverlay, crosshairOverlay, cv::Size(64, 64));	

    qDebug() << "Creating capture session.";    
    videoCap.setCamera(camera);
    videoCap.setVideoOutput(videoSink);

    connect(videoSink, &QVideoSink::videoFrameChanged, this, &VideoProcessor::handleFrame);
    
    qDebug() << "Starting camera.";
    QTimer::singleShot(100, camera, &QCamera::start);
}

void VideoProcessor::handleFrame(const QVideoFrame &frame) {
    if (!frame.isValid()) {
        qDebug() << "Invalid frame received.";
        return;
    }

    QImage image = frame.toImage();
    if (image.isNull()) {
        qDebug() << "Failed to convert frame to image.";
        return;
    }

    QImage qimg = frame.toImage().convertToFormat(QImage::Format_RGBA8888);
    cv::Mat baseFrame = qimageToMat(qimg);

    //cv::Mat greyFrame;
    //cv::cvtColor(baseFrame, greyFrame, cv::COLOR_RGBA2GRAY);
    //cv::cvtColor(greyFrame, baseFrame, cv::COLOR_GRAY2RGBA);
    
    // Emblem is a watermark, so make it small and in the corner.
    cv::Mat resizedOverlay;
    cv::resize(emblemOverlay, resizedOverlay, cv::Size(100, 100));
    int x = baseFrame.cols - resizedOverlay.cols - 10;
    int y = baseFrame.rows - resizedOverlay.rows - 10;
    if (x >= 0 && y >= 0) {
        cv::Rect roi(x, y, resizedOverlay.cols, resizedOverlay.rows);
        cv::Mat targetROI = baseFrame(roi);
        addOverlay(targetROI, resizedOverlay);
    }
    
    x = (baseFrame.cols - crosshairOverlay.cols) / 2;
    y = (baseFrame.rows - crosshairOverlay.rows) / 2 + 128;
    if (x >= 0 && y >- 0) {
        cv::Rect roi(x, y, crosshairOverlay.cols, crosshairOverlay.rows);
        cv::Mat targetROI = baseFrame(roi);
        addOverlay(targetROI, crosshairOverlay);
    }

    //addOverlay(baseFrame, emblemOverlay);

    QImage processed((uchar*)baseFrame.data, baseFrame.cols, baseFrame.rows, baseFrame.step, QImage::Format_RGBA8888);

    emit frameReady(processed.copy());
}

void VideoProcessor::addOverlay(cv::Mat &baseFrame, const cv::Mat &overlay) {
    for (int y = 0; y < overlay.rows; ++y) {
        for (int x = 0; x < overlay.cols; ++x) {
            const cv::Vec4b &pixel = overlay.at<cv::Vec4b>(y, x);
            uchar alpha = pixel[3];
            if (alpha > 0) {
                for (int c = 0; c < 3; ++c) {
                    baseFrame.at<cv::Vec4b>(y, x)[c] =
                        (alpha * pixel[c] + (255 - alpha) * baseFrame.at<cv::Vec4b>(y, x)[c]) / 255;
                }
            }
        }
    }    

}

void VideoProcessor::stop() {
    if (camera != NULL) {
        camera->stop();
    }
}

cv::Mat VideoProcessor::qimageToMat(const QImage &image) {
    return cv::Mat(image.height(), image.width(), CV_8UC4,
        const_cast<uchar*>(image.bits()), image.bytesPerLine()).clone();
}
