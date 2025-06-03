cmake_minimum_required(VERSION 3.16)
project(dashboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Quick REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/cluster.cpp
    src/communication.cpp
)

set(HEADERS
    include/cluster.h
    include/communication.h
)

set(RESOURCES
    source/dashboard.qrc
)

add_executable(dashboard
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

target_link_libraries(dashboard
    Qt5::Quick
    pthread
    vsomeip3
    boost_system
    boost_thread
    boost_log
    boost_filesystem
)

set(JSON_CONFIG_FILE "config/vsomeip_client.json" CACHE FILEPATH "VSOMEIP JSON config file")
target_compile_definitions(dashboard PRIVATE JSON_CONFIG_FILE="${JSON_CONFIG_FILE}")

set(QML_FILES
    source/qml/dashboard.qml
    source/qml/DashboardGaugeStyle.qml
    source/qml/IconGaugeStyle.qml
    source/qml/TachometerStyle.qml
    source/qml/TurnIndicator.qml
    source/qml/ValueSource.qmlpijg
)
source_group("QML Files" FILES ${QML_FILES})