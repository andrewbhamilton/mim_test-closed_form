cmake_minimum_required(VERSION 3.24 FATAL_ERROR)


set(PROJECT_NAME mim_test-closed_form)
set_property(GLOBAL PROPERTY USE_FOLDERS ON) # put cmake 'automatic' targets in own IDE folder


project(${PROJECT_NAME} LANGUAGES C CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(cmake_scripts/Dependencies.cmake)

include (CTest)
add_subdirectory(${PROJECT_NAME})
