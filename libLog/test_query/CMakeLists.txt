

AUX_SOURCE_DIRECTORY(. _SRCS)

ADD_EXECUTABLE(exclog_query.bin ${_SRCS})
ADD_DEPENDENCIES(exclog_query.bin ${LIB_LOCAL})

TARGET_LINK_LIBRARIES(exclog_query.bin ${LIB_LOCAL} pthread)
