cmake_minimum_required(VERSION 3.16)
project(VehicleSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include /usr/local/include)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/communication.cpp
)

set(HEADERS
    include/mainwindow.h
    include/communication.h
)

set(FORMS
    ui/mainwindow.ui
)

qt5_wrap_ui(FORMS_HEADERS ${FORMS})

add_executable(VehicleSimulator
    ${SOURCES}
    ${HEADERS}
    ${FORMS_HEADERS}
)

target_link_libraries(VehicleSimulator
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    pthread
    vsomeip3
    boost_system
    boost_thread
    boost_log
    boost_filesystem
)
