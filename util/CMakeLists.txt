CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(util)

SET(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY(${PROJECT_NAME} SHARED
        src/random_wrapper.cc
        src/logger.cc
        src/validation.cc
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
        include)