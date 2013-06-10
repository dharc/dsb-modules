cmake_minimum_required (VERSION 2.8)
project (dsbmodules)

set(dsbmodules_VERSION_MAJOR "0")
set(dsbmodules_VERSION_MINOR "1")
set(dsbmodules_VERSION_PATCH "1")

option(WITH_NO_THREADS "Disable multi-threading" OFF)

find_package(SDL)
# find_package(SDL_gfx1.2 REQUIRED)

if ( NOT SDL_FOUND )
	set(SDL_LIBRARY SDL)
endif ( NOT SDL_FOUND )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -D_REENTRANT -D_GNU_SOURCE=1 ")
set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG -g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(DISPLAYSOURCE display/display.c display/line.c)

add_library(dsbdisplay SHARED ${DISPLAYSOURCE})
target_link_libraries(dsbdisplay dsbcommon dl ${SDL_LIBRARY} SDL_gfx)


