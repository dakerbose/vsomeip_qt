TEMPLATE = app
TARGET = dashboard
INCLUDEPATH += .
QT += quick

SOURCES += \
    main.cpp \
    cluster.cpp \
    communication.cpp \

RESOURCES += \
    dashboard.qrc

OTHER_FILES += \
    qml/dashboard.qml \
    qml/DashboardGaugeStyle.qml \
    qml/IconGaugeStyle.qml \
    qml/TachometerStyle.qml \
    qml/TurnIndicator.qml \
    qml/ValueSource.qmlpijg

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols/extras/dashboard
INSTALLS += target

HEADERS += \
    cluster.h \
    communication.h
LIBS += -pthread
LIBS += -lvsomeip3  -lboost_system -lboost_thread -lboost_log -lboost_filesystem

QMAKE_LFLAGS += -lvsomeip3
QMAKE_CXXFLAGS += -std=c++11
CONFIG(release,debug): {
    JSON_CONFIG_FILE = /home/dakerbose/vsomeip_qt/1_hello_world/vsomeip_client.json
}
