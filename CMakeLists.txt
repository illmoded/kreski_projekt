cmake_minimum_required(VERSION 3.2)
project(kreski)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lallegro")
find_package(PkgConfig)

pkg_check_modules(ALLEGRO Allegro-5.0)

link_directories(${ALLEGRO_LIBRARY_DIRS}  )
include_directories(${ALLEGRO_INCLUDE_DIRS}  )

set(SOURCE_FILES kreskiprojekt.cpp)
add_executable(kreskiprojekt ${SOURCE_FILES})
target_link_libraries(kreskiprojekt ${ALLEGRO_LIBRARIES})

