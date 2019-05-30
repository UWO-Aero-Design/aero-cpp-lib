cmake_minimum_required( VERSION 3.5.0 )

# SWIG
find_package( SWIG REQUIRED )
include( ${SWIG_USE_FILE} )

# PYTHON
find_package( PythonLibs REQUIRED )
include_directories( ${PYTHON_INCLUDE_DIR} )

# PROJECT
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include)
#file( GLOB AERO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp" )

# PROPERTIES
set_source_files_properties(aero.i PROPERTIES CPLUSPLUS ON )
set_source_files_properties(aero.i PROPERTIES SWIG_FLAGS "-includeall" )

# ADD/LINK 
#swig_add_library(aero LANGUAGE python OUTPUT_DIR aero-py-lib/ SOURCES aero.i ${AERO_SOURCES} )
swig_add_library(aero LANGUAGE python OUTPUT_DIR aero-py-lib/ SOURCES aero.i )
swig_link_libraries(aero ${PYTHON_INCLUDE_DIR} )
