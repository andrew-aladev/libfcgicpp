cmake_minimum_required (VERSION 2.8.2)
project (libfcgipp)

SET(CMAKE_BUILD_TYPE Develop)
SET(CMAKE_CXX_FLAGS_DEVELOP "-O0 -g")

set(CMAKE_VERBOSE_MAKEFILE on)
set (Boost_USE_MULTITHREADED on)
#set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${libfcgipp_SOURCE_DIR})

find_package (Threads)
#find_package (ICU)
find_package (Boost COMPONENTS system REQUIRED)

include_directories (
	${libfcgipp_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

add_executable (
    libfcgipp
	src/test/index.cpp
	src/test/Client.cpp
	src/fcgi/Connection.cpp
	src/fcgi/Header.cpp
	)
target_link_libraries (
	libfcgipp
	${Boost_LIBRARIES}
)
