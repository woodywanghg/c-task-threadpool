CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(PROJECTNAME taskthread)
SET(LIBRARY_OUTPUT_PATH ${ROOT_DIR}/libs)
FILE(GLOB_RECURSE SOURCES "${ROOT_DIR}/src/taskthread/*.c")
ADD_DEFINITIONS("-g -O3 -fPIC")
#PROJECT(${PROJECTNAME})

ADD_LIBRARY(taskthread_shared SHARED ${SOURCES})
ADD_LIBRARY(taskthread_static STATIC ${SOURCES})

set_target_properties(taskthread_static PROPERTIES OUTPUT_NAME "person")
set_target_properties(taskthread_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(taskthread_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

set_target_properties(taskthread_shared PROPERTIES VERSION 1.0 SOVERSION 1)
