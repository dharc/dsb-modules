cmake_minimum_required (VERSION 2.8)
project (dsbmodules)

set(dsbmodules_VERSION_MAJOR "0")
set(dsbmodules_VERSION_MINOR "1")
set(dsbmodules_VERSION_PATCH "1")

option(WITH_NO_THREADS "Disable multi-threading" OFF)

set(CMAKE_C_FLAGS "-Wall -D_REENTRANT -D_GNU_SOURCE=1 -L/usr/lib/x86_64-linux-gnu")
set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG -g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(DISPLAYSOURCE display/display.c)

add_library(dsbdisplay SHARED ${DISPLAYSOURCE})
target_link_libraries(dsbdisplay dsbcommon dl SDL SDL_gfx)


