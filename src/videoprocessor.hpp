#pragma once

#include <QObject>
#include <QCamera>
#include <QVideoSink>
#include <QMediaCaptureSession>
#include <QVideoFrame>
#include <QImage>

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

    void handleFrame(const QVideoFrame &frame);
};

