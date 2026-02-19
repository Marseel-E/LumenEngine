cmake_minimum_required(VERSION 3.20)
project(2D_SANDBOX_MMO_PROJECT)

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
	${SDL2_INCLUDE_DIRS}
	"/opt/homebrew/include"
)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "src/LumenEngine/*.cpp")
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "src/AetheriaEngine/*.cpp")

add_executable(2D_SANDBOX_SERVER
	src/EchoServer/server.cpp
)

target_link_libraries(2D_SANDBOX_SERVER
	PRIVATE
	${ENET_LIB}
)

add_executable(2D_SANDBOX_MMO
	${ENGINE_SOURCES}
	${GAME_SOURCES}
)

target_link_libraries(2D_SANDBOX_MMO 
	PRIVATE
	${SDL2_LIBRARIES}
	SDL2_ttf::SDL2_ttf
	${ENET_LIB}
	${COCOA_LIB}
	${METAL_LIB}
	${QUARTZ_LIB}
	${IOKIT_LIB}
)