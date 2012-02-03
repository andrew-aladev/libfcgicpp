cmake_minimum_required (VERSION 2.8.2)
project (libfcgicpp)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(SEND_ERROR "In-source builds are not allowed! mkdir build, cd build, cmake ..")
endif()

set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set (CMAKE_CXX_FLAGS_RELEASE "-O2 -s")
if (CMAKE_BUILD_TYPE MATCHES Debug)
	set (CMAKE_VERBOSE_MAKEFILE on)
endif()
set (Boost_USE_MULTITHREADED on)

find_package (Threads)
find_package (Boost COMPONENTS system REQUIRED)

include_directories (
	${PROJECT_SOURCE_DIR}/include
	${Boost_INCLUDE_DIRS}
)

add_executable (
    ${PROJECT_NAME}
	${PROJECT_SOURCE_DIR}/test/index.cpp
	${PROJECT_SOURCE_DIR}/test/Client.cpp
	${PROJECT_SOURCE_DIR}/src/Connection.cpp
	${PROJECT_SOURCE_DIR}/src/Manager.cpp
	${PROJECT_SOURCE_DIR}/src/Head.cpp
	${PROJECT_SOURCE_DIR}/src/body/Padding.cpp
	${PROJECT_SOURCE_DIR}/src/body/BeginRequest.cpp
	${PROJECT_SOURCE_DIR}/src/body/EndRequest.cpp
	${PROJECT_SOURCE_DIR}/src/body/Unknown.cpp
	${PROJECT_SOURCE_DIR}/src/body/Params.cpp
	)
target_link_libraries (
	${PROJECT_NAME}
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)
install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

exec_program (dpkg ARGS --print-architecture OUTPUT_VARIABLE DPKG_ARCH)
set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${DPKG_ARCH})
set (CPACK_PACKAGE_NAME "${PROJECT_NAME}")

set (CPACK_PACKAGE_VERSION "0.1.2-0")

set (CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-system1.46.1 (>= 1.46.1-7)")

set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Andrew Aladev <aladjev.andrew@gmail.com>")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fastcgi realization in c++")
set (CPACK_DEBIAN_PACKAGE_SECTION "web")
set (CPACK_DEBIAN_PACKAGE_PRIORITY "standart")

set (CPACK_PACKAGE_FILE_NAME
	"${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}"
)
include (CPack)
