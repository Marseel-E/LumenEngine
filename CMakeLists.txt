cmake_minimum_required(VERSION 3.20)
project(PROJECT_AETHERIA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_library(COCOA_LIB Cocoa)
find_library(METAL_LIB Metal)
find_library(QUARTZ_LIB QuartzCore)
find_library(IOKIT_LIB IOKit)

find_library(ENET_LIB enet)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
	"src"
	"vendor"
	"vendor/metal-cpp"
	${SDL2_INCLUDE_DIRS}
	"/opt/homebrew/include"
)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "src/LumenEngine/*.cpp")
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "src/AetheriaEngine/*.cpp")

# add_executable(EchoServer
# 	src/EchoServer/server.cpp
# )

# target_link_libraries(EchoServer
# 	PRIVATE
# 	${ENET_LIB}
# )

add_executable(ProjectAetheria
	${ENGINE_SOURCES}
	${GAME_SOURCES}
)

target_link_libraries(ProjectAetheria 
	PRIVATE
	${SDL2_LIBRARIES}
	SDL2_ttf::SDL2_ttf
	${ENET_LIB}
	${COCOA_LIB}
	${METAL_LIB}
	${QUARTZ_LIB}
	${IOKIT_LIB}
)