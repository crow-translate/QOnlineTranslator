cmake_minimum_required(VERSION 3.7.0)

project(QOnlineTranslator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(AUTOMOC ON)

find_package(Qt5 COMPONENTS Multimedia Network REQUIRED)

add_library(${PROJECT_NAME} STATIC
    src/qonlinetranslator.cpp
    src/qonlinetts.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Network)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Multimedia)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
