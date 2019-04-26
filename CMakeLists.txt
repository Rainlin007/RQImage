cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME RQImage)
project(PROJECT_NAME)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH /Users/rainlin/Documents/Softwares/Qt/Qt5.12.1/5.12.1/clang_64/lib/cmake)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)


find_package(OpenCV)
include_directories( /usr/local/include )
include_directories( /usr/local/include/opencv4 )
include_directories( /usr/local/include/opencv4/opencv2 )

add_executable(PROJECT_NAME main.cpp
        mainwindow.cpp
        ralgorithm.cpp
        rcontroller.cpp
        rdialog_threshold.cpp
        rmodel.cpp
        rutils.cpp
        rview.cpp
        rdialog_rename.cpp)

target_link_libraries(PROJECT_NAME Qt5::Core)
target_link_libraries(PROJECT_NAME Qt5::Widgets)
target_link_libraries(PROJECT_NAME ${OpenCV_LIBS} )
