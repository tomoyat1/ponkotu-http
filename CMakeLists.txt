cmake_minimum_required (VERSION 2.6)
project (ponkotu-http)
set (ponkotu_VERSION_MAJOR 0)
set (ponkotu_VERSION_MINOR 1)
configure_file (
	"${PROJECT_SOURCE_DIR}/ponkotu_config.h.in"
	"${PROJECT_BINARY_DIR}/ponkotu_config.h"
	)

include_directories("${PROJECT_BINARY_DIR}")
add_executable(ponkotu-http main.c)
