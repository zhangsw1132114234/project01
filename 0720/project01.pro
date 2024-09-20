QT       += core gui network multimedia multimediawidgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

#x86
#libopencv_calib3d.so           libopencv_imgcodecs.so         libopencv_stitching.so
#libopencv_calib3d.so.3.4       libopencv_imgcodecs.so.3.4     libopencv_stitching.so.3.4
#libopencv_calib3d.so.3.4.1     libopencv_imgcodecs.so.3.4.1   libopencv_stitching.so.3.4.1
#libopencv_core.so              libopencv_imgproc.so           libopencv_superres.so
#libopencv_core.so.3.4          libopencv_imgproc.so.3.4       libopencv_superres.so.3.4
#libopencv_core.so.3.4.1        libopencv_imgproc.so.3.4.1     libopencv_superres.so.3.4.1
#libopencv_dnn.so               libopencv_ml.so                libopencv_videoio.so
#libopencv_dnn.so.3.4           libopencv_ml.so.3.4            libopencv_videoio.so.3.4
#libopencv_dnn.so.3.4.1         libopencv_ml.so.3.4.1          libopencv_videoio.so.3.4.1
#libopencv_features2d.so        libopencv_objdetect.so         libopencv_video.so
#libopencv_features2d.so.3.4    libopencv_objdetect.so.3.4     libopencv_video.so.3.4
#libopencv_features2d.so.3.4.1  libopencv_objdetect.so.3.4.1   libopencv_video.so.3.4.1
#libopencv_flann.so             libopencv_photo.so             libopencv_videostab.so
#libopencv_flann.so.3.4         libopencv_photo.so.3.4         libopencv_videostab.so.3.4
#libopencv_flann.so.3.4.1       libopencv_photo.so.3.4.1       libopencv_videostab.so.3.4.1
#libopencv_highgui.so           libopencv_shape.so             pkgconfig/
#libopencv_highgui.so.3.4       libopencv_shape.so.3.4         python2.7/
#libopencv_highgui.so.3.4.1     libopencv_shape.so.3.4.1       python3.6/

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/lib/.
LIBS += /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_videoio.so \
        /usr/local/lib/libopencv_imgcodecs.so \
        /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_calib3d.so \
        /usr/local/lib/libopencv_features2d.so \
        /usr/local/lib/libopencv_video.so \
        /usr/local/lib/libopencv_video.so.3.4 \
        /usr/local/lib/libopencv_ml.so \
        /usr/local/lib/libopencv_objdetect.so \
        /usr/local/lib/libopencv_flann.so \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

include(./form/form.pri)
include(./hardware/hardware.pri)

INCLUDEPATH += $$PWD/form
INCLUDEPATH += $$PWD/hardware

RESOURCES += \
    res.qrc
