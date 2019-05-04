cmake_minimum_required( VERSION 3.5.1 )

project( MessageTest )

find_package( GTest REQUIRED )

include_directories( ${GTEST_INCLUDE_DIRS} )
include_directories( ${MessageTest}../include ) 

add_executable( tests tests.cpp )

target_link_libraries( tests ${GTEST_LIBRARIES} pthread )