cmake_minimum_required(VERSION 3.5)
project(t1_resize_img01_test CXX)

find_package(OpenCV REQUIRED)
set(OpenCV_DIr "/usr/local/include/opencv2")
include_directories(${OpenCV_INCLUDE_DIRS})
LINK_DIRECTORIES(${OpenCV_LIB_DIR})


#include(CheckIncludeFileCXX)
#check_include_file_cxx(any_HAS_ANY)
#check_include_file_cxx(string_view_HAS_STRING_VIEW)
#if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
#elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_CORROUTINE)
#    set(CMAKE_CXX_STANDARD 20)
#elseif (HAS_ANY AND HAS_STRING_VIEW)
#    set(CMAKE_CXX_STANDARD 17)
#else ()
#    set(CMAKE_CXX_STANDARD 14)
#endif ()
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} test_main.cc "../controllers/TaskController.cc" "../controllers/image_converter.cpp")

find_package(Drogon REQUIRED)
# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# target_link_libraries(${PROJECT_NAME}_test PRIVATE drogon)
#
# and comment out the following lines
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon ${OpenCV_LIBS})

ParseAndAddDrogonTests(${PROJECT_NAME})
