QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

#INCLUDEPATH += Users/egorsavcuk/Desktop/cpp_int.hpp
#LIBS += "Users/egorsavcuk/Desktop/cpp_int.hpp"
#INCLUDEPATH += Users/egorsavcuk/Desktop/random.hpp
#LIBS += "Users/egorsavcuk/Desktop/random.hpp"



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Keygen.cpp \
    decodewindow.cpp \
    encodewindow.cpp \
    generatewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    showkeys.cpp


HEADERS += \
    Keygen.h \
    decodewindow.h \
    encodewindow.h \
    generatewindow.h \
    mainwindow.h \
    showkeys.h
    cpp_int.hpp
    random.hpp

FORMS += \
    decodewindow.ui \
    encodewindow.ui \
    form.ui \
    generatewindow.ui \
    mainwindow.ui \
    showkeys.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
