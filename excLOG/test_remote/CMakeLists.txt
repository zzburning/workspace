

AUX_SOURCE_DIRECTORY(. _SRCS)

ADD_EXECUTABLE(exclog_remote.bin ${_SRCS})
ADD_DEPENDENCIES(exclog_remote.bin ${LIB_REMOTE})

TARGET_LINK_LIBRARIES(exclog_remote.bin ${LIB_REMOTE} pthread)
