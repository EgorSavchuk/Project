cmake_minimum_required(VERSION 3.17.0)

project(Homework CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_17)

set (CMAKE_PREFIX_PATH "/Users/egorsavcuk/Qt/6.1.1/clang_64")
set(Boost_USE_STATIC_LIBS ON)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

find_package(Boost REQUIRED COMPONENTS system random)
enable_testing()
add_subdirectory(doctest)
include(doctest/doctest.cmake)

add_executable(proj_test tests.cpp Keygen.cpp)
add_executable(proj main.cpp
        decodewindow.cpp
        encodewindow.cpp
        generatewindow.cpp
        Keygen.cpp
        mainwindow.cpp
        showkeys.cpp
        decodewindow.ui
        encodewindow.ui
        form.ui
        generatewindow.ui
        mainwindow.ui
        showkeys.ui
        resource.qrc
        random.hpp
        )
target_link_libraries(proj_test PUBLIC doctest::doctest default Boost::system Boost::random)
target_link_libraries(proj PUBLIC doctest::doctest default Boost::system Boost::random Qt6::Widgets)
doctest_discover_tests(proj_test)
