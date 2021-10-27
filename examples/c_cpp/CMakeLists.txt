cmake_minimum_required (VERSION 2.8)

project ("texsmart_examples")
message("CMAKE SYSTEM: ${CMAKE_SYSTEM_NAME}")
message("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(build_type "debug")
else()
	#set(build_type ${CMAKE_BUILD_TYPE})
	string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
endif()

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("../../include/")
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../../lib/)

#set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
SET(CMAKE_INSTALL_RPATH "$ORIGIN")

if(CYGWIN)
	add_definitions(-DCYGWIN_PLATFORM)
	set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/../../bin/cygwin_${build_type})
elseif(WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/../../bin/win_${build_type})
	set(export_files ../../lib/tencent_ai_texsmart.dll)
	set(CMAKE_C_FLAGS_DEBUG "-W4") 
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
	set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/../../bin/${build_type}/)
	set(export_files ../../lib/libtencent_ai_texsmart.so)
	set(CMAKE_C_FLAGS_DEBUG "-g -Wall") 
endif()

add_subdirectory(src)

install(FILES ${export_files} DESTINATION ${CMAKE_INSTALL_PREFIX} COMPONENT texsmart_examples)
