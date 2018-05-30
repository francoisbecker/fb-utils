cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -Wconversion")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10")

include_directories(BEFORE "../include")

project("fbu-tests" LANGUAGES "CXX")

file(GLOB SRC
    "./src/*.hpp"
    "./src/*.cpp"
)

add_executable(fbu-test ${SRC})

