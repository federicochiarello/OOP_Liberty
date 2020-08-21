QT += widgets

CONFIG += c++11 console
CONFIG -= app_bundle

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
        controller/controller.cpp \
        main.cpp \
        view/projectpreview.cpp \
        view/projectview.cpp \
        view/taskcontainerwidget.cpp \
        view/taskholder.cpp \
        view/taskpreview.cpp \
        view/taskprioritywidget.cpp \
        view/taskslist.cpp \
        view/taskslistwidget.cpp \
        view/taskwidget.cpp \
        view/textholder.cpp \
        view/view.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    controller/controller.h \
    view/projectpreview.h \
    view/projectview.h \
    view/taskcontainerwidget.h \
    view/taskholder.h \
    view/taskpreview.h \
    view/taskprioritywidget.h \
    view/taskslist.h \
    view/taskslistwidget.h \
    view/taskwidget.h \
    view/textholder.h \
    view/view.h
