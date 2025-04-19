#include <QDebug>
#include <QMediaDevices>
#include <QTimer>

#include "videoprocessor.hpp"

VideoProcessor::VideoProcessor(const QCameraDevice &cameraDevice, QObject *parent) 
    : QObject(parent), camera(new QCamera(cameraDevice)), videoSink(new QVideoSink(this)) {

    qDebug() << "Creating video processor object.";

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

    emit frameReady(image);
}

void VideoProcessor::stop() {
    if (camera != NULL) {
        camera->stop();
    }
}

