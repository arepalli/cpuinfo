TEMPLATE = app
TARGET = cpuinfo
QT += quick

HEADERS += \
    src/cpuinfomodel.h

SOURCES += \
    src/cpuinfomodel.cpp \
    src/main.cpp

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = $$PWD/designer

OTHER_FILES +=

RESOURCES += \
    resource.qrc
