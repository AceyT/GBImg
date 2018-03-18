cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project("GBImg")

set (CMAKE_CXX_STANDARD 11)

set(EXE "GBImg")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/cxxopts")

set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")

set(INC_FILES
	"${INC_DIR}/Options.hpp"
	"${INC_DIR}/CodeExporter.hpp"
	"${INC_DIR}/ColorManip.hpp"
	"${INC_DIR}/ColorPalette.hpp"
	"${INC_DIR}/Colors.hpp"
	"${INC_DIR}/MetaImg.hpp"
	"${INC_DIR}/Image.hpp"
	"${INC_DIR}/ImageProgram.hpp"
	"${INC_DIR}/stb_image.h"
	)

include_directories(${INC_DIR})


set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")

set(SRC_FILES
	"${SRC_DIR}/Options.cpp"
	"${SRC_DIR}/CodeExporter.cpp"
	"${SRC_DIR}/ColorManip.cpp"
	"${SRC_DIR}/Colors.cpp"
	"${SRC_DIR}/MetaImg.cpp"
	"${SRC_DIR}/Image.cpp"
	"${SRC_DIR}/ImageProgram.cpp"
	"${SRC_DIR}/main.cpp"
	)

add_executable(${EXE} ${SRC_FILES} ${INC_FILES})
target_link_libraries(${EXE} cxxopts)
