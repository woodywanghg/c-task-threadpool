CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(PROJECTNAME taskthread)
SET(LIBRARY_OUTPUT_PATH ${ROOT_DIR}/libs)
FILE(GLOB_RECURSE SOURCES "${ROOT_DIR}/src/taskthread/*.c")
ADD_DEFINITIONS("-g -O3 -fPIC")
#PROJECT(${PROJECTNAME})

SET(HEADERFILES ${ROOT_DIR}/src/taskthread/task.h ${ROOT_DIR}/src/taskthread/task_thread_pool.h)
INSTALL(FILES ${HEADERFILES} DESTINATION  include)

ADD_LIBRARY(taskthread SHARED ${SOURCES})
ADD_LIBRARY(taskthread_static STATIC ${SOURCES})

SET_TARGET_PROPERTIES(taskthread_static PROPERTIES OUTPUT_NAME "taskthread")
SET_TARGET_PROPERTIES(taskthread PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(taskthread_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

SET_TARGET_PROPERTIES(taskthread PROPERTIES VERSION 1.0 SOVERSION 1)
