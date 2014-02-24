/*************************************************************************************************
Copyright 2014 Nicolas AUBRY

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*************************************************************************************************/

#include "util_render.h"
#include "util_pipeline.h"

#include <QElapsedTimer>
#include <QSize>
#include <QObject>
#include <QTimer>
#include <QPixmap>


class GestureHandler : public QObject
{
    Q_OBJECT
public:
    GestureHandler();
    ~GestureHandler();

    bool start();
    void stop();
    QSize image_size();

signals:
    void notify_gesture(PXCGesture::Gesture gesture_evt);
    void notify_image(QPixmap pixmap);

private slots:
    void _stream();

private:
    bool _streaming;
    bool _init_error;
    QTimer _fps_timer;
    UtilPipeline _pipeline;
    QElapsedTimer _elapsed_timer;
    PXCGesture::Gesture::Label _last_gesture;
};
