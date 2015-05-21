cmake_minimum_required(VERSION 3.2)
project(kreskiprojekt)
INCLUDE(FindPkgConfig)

#http://stackoverflow.com/questions/21070517/i-cant-run-a-program-that-uses-allegro5-with-cmake

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lallegro")

    set(plikikresek kreskiprojekt.cpp)

    #Executable
    add_executable(kreski  ${plikikresek})

    #include Allegro
    include_directories(./include)
    link_directories(./lib/allegro5)
    #connect all the libraries

    set(allegro5_LIBS ${CMAKE_SOURCE_DIR}/lib/allegro5/liballegro.so ${CMAKE_SOURCE_DIR}/lib/allegro5/liballegro_primitives.so)
    target_link_libraries(kreski ${allegro5_LIBS})