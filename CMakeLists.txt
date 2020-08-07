
cmake_minimum_required(VERSION 3.14)


set(PROJECT_NAME k_mer)
project(${PROJECT_NAME}
        VERSION 0.1.0
        LANGUAGES CXX
        )


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(WARNING_FLAGS -Wall -Wextra)


message("Project root: " ${CMAKE_SOURCE_DIR})


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


add_subdirectory(src)
