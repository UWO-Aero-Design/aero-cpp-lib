cmake_minimum_required(VERSION 3.5.0)

project( Message )

include_directories( ${Message_SOURCE_DIR}/include )

file( GLOB SOURCES "${Message_SOURCE_DIR}/src/*.cpp" )

add_executable(main main.cpp ${SOURCES})