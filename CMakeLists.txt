cmake_minimum_required (VERSION 2.8.2)
project (libfcgicpp)

set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "-O2 -s")
if (CMAKE_BUILD_TYPE MATCHES Debug)
	set (CMAKE_VERBOSE_MAKEFILE on)
endif()
set (Boost_USE_MULTITHREADED on)

find_package (Boost COMPONENTS system REQUIRED)

include_directories (
	${libfcgicpp_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

add_executable (
    libfcgicpp
	src/test/index.cpp
	src/test/Client.cpp
	src/fcgi/Connection.cpp
	src/fcgi/Header.cpp
	src/fcgi/body/BeginRequest.cpp
	src/fcgi/body/EndRequest.cpp
	src/fcgi/body/Unknown.cpp
	src/fcgi/body/Params.cpp
	)
target_link_libraries (
	libfcgicpp
	${Boost_LIBRARIES}
)
install (TARGETS libfcgicpp DESTINATION bin)

set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set (CPACK_PACKAGE_NAME "libfcgicpp")

set (CPACK_PACKAGE_VERSION "0.1.1-0")

set (CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-system1.46.1 (>= 1.46.1-7)")

set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Andrew Aladev <aladjev.andrew@gmail.com>")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fastcgi realization in c++")
set (CPACK_DEBIAN_PACKAGE_SECTION "web")
set (CPACK_DEBIAN_PACKAGE_PRIORITY "standart")

set (CPACK_PACKAGE_FILE_NAME 
	"${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}"
)

include (CPack)
