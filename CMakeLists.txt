#==PROJECT (PRJ_NAME [C][CXX][JAVA])
#::define project name & type; define _BINARY_DIR & _SOURCE_DIR implicit meanwhile
PROJECT (TEST) 

#==SET（VAR[VALUE] [CACHE TYPE DOCSTRING [FORCE]]）
#::define variate explicit
SET(SRC_LIST test.c)

#==MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ...)
#::SEND_ERROR，产生错误，生成过程被跳过。
#::SATUS,输出前缀为-的信息。
#::FATAL_ERROR，立即终止所有cmake过程
MESSAGE(STATUS "This is BINARY dir " ${TEST_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${TEST_SOURCE_DIR})

#::
ADD_EXECUTABLE(test.bin ${SRC_LIST})

#::
# ADD_SUBDIRECTORY(src)
